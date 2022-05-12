#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "fileUser.h"
#include "colors.h"
#include "stringFunc.h"

#define SIZE 1024   // define the size of the block of bytes that are sent to the server

pthread_t fileThread;

void connectSocketFile(sendFileStruct *data, int port, char *ip) // connect socket for send file
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
    sendFileStruct *dataStruct = (sendFileStruct *)data;
    dataStruct->socketServer = dSFileSend;

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
        pthread_create(&fileThread, NULL, prepareTransfer, dataStruct);
        pthread_join(fileThread, 0);
        shutdown(dSFileSend, 2);
    }
    else
    {
        redMessage("Error connexion server for sending file ! \n");
    }
}

void prepareTransfer(void *sendFileData) // prepare the sending of the file
{
    FILE *fp;
    sendFileStruct *data = (sendFileStruct *)sendFileData;
    char **mess = str_split(data->cmd, 1);

    size_t filenameSize = strlen(mess[1]);

    // get file path
    char *folder = "userStorage/";
    char *path = (char *)malloc((strlen(folder) + filenameSize) * sizeof(char));
    strcat(path, folder);
    strcat(path, mess[1]);

    // get the file size
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

        // ------------------------ Send fileStruct and filename --------------------------

        char *filename = mess[1];
        // fill the struct
        fileStruct *file = (fileStruct *)malloc(sizeof(fileStruct));
        file->filenameSize = filenameSize;
        file->fileSize = fileSize;

        int structSize = sizeof(*file);
        if (send(data->socketServer, &structSize, sizeof(int), 0) == -1) // send the size of the struct
        {
            redErrorMessage("Error in sending struct size\n");
        }
        if (send(data->socketServer, file, structSize, 0) == -1) // send the struct
        {
            redErrorMessage("Error in sending struct size\n");
        }
        if (send(data->socketServer, filename, file->filenameSize, 0) == -1) // send the filename
        {
            redErrorMessage("Error in sending filename\n");
        }
        // --------------------------------------------------------------------------------
        fileTransfer(data->socketServer, file, filename);
    }
}

void fileTransfer(int socket, fileStruct *file, char *name) // transfer the file to the socket
{
    FILE *fp;
    char buffer[SIZE];
    fileStruct *fileData = file;

    char *folder = "userStorage/";
    char *filename = name;
    long fileSize = fileData->fileSize;
    char *path = (char *)malloc((strlen(folder) + fileData->filenameSize) * sizeof(char));
    strcat(path, folder);
    strcat(path, filename);
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