#ifndef CLIENT_H_   /* Include guard */
#define CLIENT_H_

typedef struct sendFileStruct sendFileStruct;

struct sendFileStruct
{
    int socketServer;
    char* cmd;
};

typedef struct fileStruct fileStruct;

struct fileStruct
{
    size_t filenameSize;
    long fileSize;
};

void receiveMessage(int socket);  // Reception of a server message
void sendMessage(int socket); // Sending a message to the server
void sendSpecificMessage(int client, char *message); // Sending a specific message to the server
void displayManuel(); // Display the commands manual
void quitForUser(int n); // Allows User n to leave the server
int receivePort(int socket); // receive a port from the server
void sendFile(void* sendFileData); // send a file to the server in a different socket
void sendNumber(int socket, int number); // send an int to the socket
void fileTransfer(int socket, fileStruct *file, char *filename); // transfer the file to the socket
void connectSocketFile(sendFileStruct* data); // connect socket for send file

#endif // CLIENT_H_
