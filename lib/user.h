#ifndef CLIENT_H_   /* Include guard */
#define CLIENT_H_

void receiveMessage(int socket);                        // Reception of a server message
void sendMessage(int socket);                           // Sending a message to the server
void sendSpecificMessage(int client, char *message);    // Sending a specific message to the server
void signalHandler(int n);                              // Handler for ^C

#endif // CLIENT_H_
