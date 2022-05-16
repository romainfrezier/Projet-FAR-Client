#ifndef COMMANDCLIENT_H_ /* Include guard */
#define COMMANDCLIENT_H_

void quitForUser(int socket);                                               // Disconnects the user
void displayManual();                                                       // Display the command manual
void checkCommand(char *m, int ipAddress, int portSendingFile, int socket); // check user given command

#endif // COMMANDCLIENT_H_