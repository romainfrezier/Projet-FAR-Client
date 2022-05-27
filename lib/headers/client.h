/**
 * @file client.h
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Client functions
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CLIENT_H_   /* Include guard */
#define CLIENT_H_

/**
 * @brief Launch the client program
 * @param ipAddress ip address of the server
 * @param port port of the server
 */
void launchClient(char *ipAddress, int port);

/**
 * @brief Reception of a server message
 *
 * @param socket client id
 * @return NULL
 */
void * receiveMessage(void *socket);

/**
 * @brief Sending a message to the server
 *
 * @param socket client id
 * @return NULL
 */
void * sendMessage(void *socket);

/**
 * @brief Handler for ^C
 *
 * @param n number of the signal
 */
void signalHandler(int n);

/**
 * @brief Connect a new socket
 *
 * @param port new socket's port
 * @return socket descriptor (dS)
 */
int socketConnection(int port);

#endif // CLIENT_H_