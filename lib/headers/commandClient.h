/**
 * @file commandClient.h
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Client actions
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef COMMANDCLIENT_H_ /* Include guard */
#define COMMANDCLIENT_H_

/**
 * @brief Sending a specific message to the server
 *
 * @param client socket descriptor, connexion between client and server
 * @param message message to send
 */
void sendSpecificMessage(int client, char *message);

/**
 * @brief Disconnects the user
 *
 * @param socket socket descriptor
 */
void quitForUser(int socket);

/**
 * @brief Display the command manual
 */
void displayManual();

/**
 * @brief Check user given command
 *
 * @param m message from the user
 * @param ipAddress ip address of the server
 * @param portSendingFile the port of socket for send file
 * @param socket socket descriptor
 */
void checkCommand(char *m, char* ipAddress, int portSendingFile, int socket); //

#endif // COMMANDCLIENT_H_