#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../headers/fileClient.h"
#include "../headers/colors.h"
#include "../headers/stringFunc.h"
#include "../headers/commandClient.h"

#define SIZE 1024 // define the size of the block of bytes that are sent to the server

pthread_t fileSendThread;
pthread_t fileGetThread;

void connectSocketFileSend(sendFileStruct *data, int port, char *ip) // connect socket for send file
{
    FILE *fp;
    sendFileStruct *dataStruct = (sendFileStruct *)data;

    // get file path
    char *folder = "userStorage/";
    char *path = (char *)malloc((strlen(folder) + strlen(dataStruct->filename)) * sizeof(char));
    strcat(path, folder);
    strcat(path, dataStruct->filename);
    fp = fopen(path, "rb");
    if (fp == NULL)
    {
        redMessage("The file doesn't exist !\n");
    }
    else
    {
        fseek(fp, 0, SEEK_END);    // Jump to the end of the file
        long fileSize = ftell(fp); // Get the current byte offset in the file
        rewind(fp);                // Jump back to the beginning of the file
        fclose(fp);
    
        if (fileSize > 100000000)
        {
            redMessage("You cannot send a file over 100MB\n");
        }
        else
        {
            int enable = 1;
            int dSFileSend = socket(PF_INET, SOCK_STREAM, 0);
            if (dSFileSend < 0)
            {
                redErrorMessage("ERROR opening socket for sending file");
            }
            if (setsockopt(dSFileSend, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
            {
                redErrorMessage("setsockopt(SO_REUSEADDR) failed");
            }
            dataStruct->socketServer = dSFileSend;
            dataStruct->path = path;
            dataStruct->fileSize = fileSize;

            // value for connection to the socket
            struct sockaddr_in aSfile;
            aSfile.sin_family = AF_INET;
            inet_pton(AF_INET, ip, &(aSfile.sin_addr));
            aSfile.sin_port = htons(port);
            socklen_t lgFile = sizeof(struct sockaddr_in);

            int resCoFile = connect(dSFileSend, (struct sockaddr *)&aSfile, lgFile); // connection to the socket
            if (resCoFile == 0)
            {
                blueMessage("Begin of the file transfer...\n");
                pthread_create(&fileSendThread, NULL, prepareTransfer, dataStruct);
                pthread_join(fileSendThread, 0);
                shutdown(dSFileSend, 2);
            }
            else
            {
                redMessage("Error connexion server for sending file ! \n");
            }
        }
    }
}

void * prepareTransfer(void *sendFileData) // prepare the sending of the file
{
    FILE *fp;
    sendFileStruct *data = (sendFileStruct *)sendFileData;

    size_t filenameSize = strlen(data->filename);

    fp = fopen(data->path, "rb");
    if (fp == NULL)
    {
        redMessage("The file doesn't exist !\n");
    }
    else
    {
        // fill the struct
        fileStruct *file = (fileStruct *)malloc(sizeof(fileStruct));
        file->filenameSize = filenameSize;
        file->fileSize = data->fileSize;
        file->path = data->path;

        // Send fileStruct and filename
        int structSize = sizeof(*file);
        if (send(data->socketServer, &structSize, sizeof(int), 0) == -1) // send the size of the struct
        {
            redErrorMessage("Error in sending struct size\n");
        }
        if (send(data->socketServer, file, structSize, 0) == -1) // send the struct
        {
            redErrorMessage("Error in sending struct size\n");
        }
        if (send(data->socketServer, data->filename, file->filenameSize, 0) == -1) // send the filename
        {
            redErrorMessage("Error in sending filename\n");
        }
        fileTransfer(data->socketServer, file, data->filename);
    }
    return NULL;
}

void fileTransfer(int socket, fileStruct *file, char *name) // transfer the file to the socket
{
    FILE *fp;
    char buffer[SIZE];
    fileStruct *fileData = file;
    
    char *folder = "userStorage/";
    char *filename = name;
    long fileSize = fileData->fileSize;
    char *path = fileData->path;
    
    fp = fopen(path, "rb"); // Open the file in binary mode

    int count;
    for (int i = 0; i < fileSize; i += SIZE) // send file block by block until there are no more byts to send
    {
        if (i + SIZE < fileSize) // Calculate the size of the block to send
        {
            count = SIZE;
        }
        else
        {
            count = fileSize - i;
        }

        fread(buffer, count, 1, fp);                       // read the file
        if (send(socket, buffer, sizeof(buffer), 0) == -1) // send the block of bytes to the server
        {
            perror("Error in sending file.");
            exit(1);
        }
        bzero(buffer, SIZE); // Reset the buffer
    }
    fclose(fp); // Close the file
    greenMessage("File send succesfully\n");
}

void connectSocketFileGet(getFileStruct *data, int port, char *ip) // connect socket for send file
{
    int enable = 1;
    int dSFileGet = socket(PF_INET, SOCK_STREAM, 0);
    if (dSFileGet < 0)
    {
        redErrorMessage("ERROR opening socket for sending file");
    }
    if (setsockopt(dSFileGet, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        redErrorMessage("setsockopt(SO_REUSEADDR) failed");
    }

    getFileStruct *dataStruct = (getFileStruct *)data;
    dataStruct->socketServer = dSFileGet;

    // value for connection to the socket
    struct sockaddr_in aSfile;
    aSfile.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(aSfile.sin_addr));
    aSfile.sin_port = htons(port);
    socklen_t lgFile = sizeof(struct sockaddr_in);

    int resCoFile = connect(dSFileGet, (struct sockaddr *)&aSfile, lgFile); // connection to the socket
    if (resCoFile == 0)
    {
        blueMessage("Begin of the file transfer...\n");
        pthread_create(&fileGetThread, NULL, prepareGetFile, dataStruct);
        pthread_join(fileGetThread, 0);
        shutdown(dSFileGet, 2);
    }
    else
    {
        redMessage("Error connexion server for sending file ! \n");
    }
}

void * prepareGetFile(void *data)
{
    getFileStruct *dataGetFile = (getFileStruct *)data;
    char **mess = str_split(dataGetFile->cmd, 1);

    sendSpecificMessage(dataGetFile->socketServer, mess[1]);

    u_long sizeFileExist;
    if (recv(dataGetFile->socketServer, &sizeFileExist, sizeof(u_long), 0) == -1)
    {
        redErrorMessage("Error sizeFileExist received\n");
    }

    char *fileExist = (char*)malloc(sizeFileExist);
    if (recv(dataGetFile->socketServer, fileExist, sizeFileExist, 0) == -1)
    {
        redErrorMessage("Error fileExist received\n");
    }

    if (strcmp(fileExist, "The file doesn't exist !") == 0)
    {
        redMessage("The file doesn't exist !\n");
    }
    else
    {
        u_long sizeFilesizeGood;
        if (recv(dataGetFile->socketServer, &sizeFilesizeGood, sizeof(u_long), 0) == -1)
        {
            redErrorMessage("Error sizeFileGood received\n");
        }

        char *filesizeGood = (char *)malloc(sizeFilesizeGood);
        if (recv(dataGetFile->socketServer, filesizeGood, sizeFilesizeGood, 0) == -1)
        {
            redErrorMessage("Error filesizeGood received\n");
        }

        if (strcmp(filesizeGood, "You cannot send a file over 100MB") == 0)
        {
            redMessage("The file size is over 100MB, you cannot download it !\n");
        }
        else
        {
            // Size reception
            int size;
            if (recv(dataGetFile->socketServer, &size, sizeof(int), 0) == -1)
            {
                redErrorMessage("Error struct size received\n");
            }

            // Struct reception
            fileStruct *fileInfo = (fileStruct *)malloc(size);
            if (recv(dataGetFile->socketServer, fileInfo, size, 0) == -1)
            {
                redErrorMessage("Error struct received\n");
            }

            receiveFile(fileInfo, dataGetFile->socketServer, mess[1]);
        }
    }
    return NULL;
}

void receiveFile(fileStruct *fileInfo, int serverSocket, char *filename)
{
    FILE *fprecv;
    char buffer[SIZE];
    int recvBuffer;

    char *folder = "userStorage/";
    char *path = (char *)malloc((strlen(folder) + strlen(filename)) * sizeof(char));
    strcat(path, folder);
    strcat(path, filename);

    long fileSize = fileInfo->fileSize;

    fprecv = fopen(path, "w+"); // open the file in "path" to write inside. Overwrite it if it already exists, create it if not

    int count;
    for (int i = 0; i < fileSize; i += SIZE) // receive file block by block of SIZE byts until there are no more byts to receive
    {
        if (i + SIZE < fileSize) // Calculate the size of the block to receive
        {
            count = SIZE;
        }
        else
        {
            count = fileSize - i;
        }

        recvBuffer = recv(serverSocket, buffer, SIZE, 0); // receive the block of bytes from the user
        if (recvBuffer <= 0)
        {
            perror("Error in receiving buffer.");
            exit(1);
        }
        fwrite(buffer, sizeof(buffer), 1, fprecv); // write file
        bzero(buffer, SIZE);
    }
    greenMessage("File written as ");
    greenMessage(path);
    printf("\n");
    fclose(fprecv);
}