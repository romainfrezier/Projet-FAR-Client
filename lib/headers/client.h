#ifndef CLIENT_H_   /* Include guard */
#define CLIENT_H_

void * receiveMessage(void *socket);                        // Reception of a server message
void * sendMessage(void *socket);                           // Sending a message to the server
void signalHandler(int n);                              // Handler for ^C
int socketConnection(int port);

#endif // CLIENT_H_