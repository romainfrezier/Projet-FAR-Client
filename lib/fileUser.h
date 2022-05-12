#ifndef FILEUSER_H_ /* Include guard */
#define FILEUSER_H_

typedef struct sendFileStruct sendFileStruct;

struct sendFileStruct
{
    int socketServer;
    char *cmd;
};

typedef struct fileStruct fileStruct;

struct fileStruct
{
    size_t filenameSize;
    long fileSize;
};

void connectSocketFile(sendFileStruct *data, int port, char *ip); // connect socket for send file
void prepareTransfer(void *sendFileData);                         // prepare the sending of the file
void fileTransfer(int socket, fileStruct *file, char *name);      // transfer the file to the socket

#endif // FILEUSER_H_