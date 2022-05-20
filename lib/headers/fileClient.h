#ifndef FILECLIENT_H_ /* Include guard */
#define FILECLIENT_H_

typedef struct sendFileStruct sendFileStruct;

struct sendFileStruct
{
    int socketServer;
    char *filename;
    char *path;
    long fileSize;
};

typedef struct getFileStruct getFileStruct;

struct getFileStruct
{
    int socketServer;
    char *cmd;
};

typedef struct fileStruct fileStruct;

struct fileStruct
{
    size_t filenameSize;
    long fileSize;
    char *path;
};

void connectSocketFileSend(sendFileStruct *data, int port, char *ip);       // connect socket for send file
void connectSocketFileGet(getFileStruct *data, int port, char *ip);         // connect socket for get file
void prepareTransfer(void *sendFileData);                                   // prepare the sending of the file
void fileTransfer(int socket, fileStruct *file, char *name);                // transfer the file to the server
void prepareGetFile(void *data);                                            // prepare the receiving of the file 
void receiveFile(fileStruct *fileInfo, int serverSocket, char *filename);   // receive the file from the server

#endif // FILECLIENT_H_