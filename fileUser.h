#ifndef FILEUSER_H_ /* Include guard */
#define FILEUSER_H_

typedef struct sendFileStruct sendFileStruct;

struct sendFileStruct
{
    int socketServer;
    char *cmd;
};

int receivePort(int socket);                   // receive a port from the server
void sendFile(void *sendFileData);             // send a file to the server in a different socket
void fileTransfer(int socket, char *filename); // transfer the file to the socket
void connectSocketFile(sendFileStruct data);   // connect socket for send file

#endif // FILEUSER_H_