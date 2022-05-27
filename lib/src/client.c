/**
 * @file client.c
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Client functions implementation
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <regex.h>

#include "../headers/client.h"
#include "../headers/colors.h"
#include "../headers/commandClient.h"
#include "../headers/stringFunc.h"
#include "../headers/tools.h"

/**
 * @brief Maximum size of a message
 */
#define MAX 100

/**
 * @brief socket descriptor for the connexion between client and server
 */
int dS;

/**
 * @brief Ip address of the server
 */
char *ipAddress;

/**
 * @brief Port for sending file
 */
int portSendingFile;

/**
 * @brief Thread for send messages
 */
pthread_t sendThread;

/**
 * @brief Thread for receive messages
 */
pthread_t receiveThread;

void launchClient(char *ip, int port)
{
  greenMessage("Start program\n");

  ipAddress = ip;
  dS = socketConnection(port);

  // check the ^C
  signal(SIGINT, signalHandler);

  // Checking username
  int check;
  do
  {
    // Connection message size reception
    u_long sizeCoMsg;
    int receive = recv(dS, &sizeCoMsg, sizeof(u_long), 0);
    if (receive == -1)
    {
      redErrorMessage("Error message size received\n");
    }
    else if (receive == 0)
    {
      redErrorMessage("Server shutdown now !\n");
    }
    // Message reception
    char *isConnected = (char *)malloc(sizeCoMsg * sizeof(char));
    if (recv(dS, isConnected, sizeCoMsg * sizeof(char), 0) == -1)
    {
      redErrorMessage("An error appeared during connection to the server...\n");
    }

    check = strcmp(isConnected, "Connected !");

    if (check != 0)
    {
      printf("%s\n", isConnected);
      char *username = (char *)malloc(sizeof(char) * 50);
      fgets(username, 50, stdin);
      username[strcspn(username, "\n")] = 0;
      printf("\nMy username : ");
      blueMessage(username);
      printf("\n\n");
      sendSpecificMessage(dS, username);
    }
    else
    {
      greenMessage(isConnected);
      printf("\n\n");
    }
  } while (check != 0);

  while(1){
    // Create message threads
    pthread_create(&sendThread, NULL, sendMessage, (void *)dS);
    pthread_create(&receiveThread, NULL, receiveMessage, (void *)dS);
    pthread_join(receiveThread, 0);
    pthread_cancel(sendThread);
  }

  // Waiting for the end of threads
  pthread_join(sendThread, 0);

  // Shutdown of socket
  shutdown(dS, 2);
  printf("End program\n");
}

// Sending a message to the server
void *sendMessage(void *socket)
{
  char *m = (char *)malloc(MAX * sizeof(char));

  while (strcmp(m, "/quit") != 0)
  {
    // Client input
    printf("Enter your message (100 max) : \033[0;32m");
    fgets(m, 100, stdin);
    m[strcspn(m, "\n")] = 0;
    u_long size = strlen(m) + 1;
    reset();
    // check user given command
    checkCommand(m, ipAddress, portSendingFile, (int)socket);
  }
  shutdown((int)socket, 2);
  free(m);
  exit(0);
}

// Reception of a server message
void *receiveMessage(void *socket)
{
  char *m = (char *)malloc(MAX * sizeof(char));
  while (1)
  {
    // Size reception
    u_long sizeMessage;
    int receive = recv((int)socket, &sizeMessage, sizeof(u_long), 0);
    if (receive == -1)
    {
      redErrorMessage("Error message size received\n");
    }
    else if (receive == 0)
    {
      redErrorMessage("Server shutdown now !\n");
    }

    // Message reception
    char *messageReceive = (char *)malloc(sizeMessage * sizeof(char));
    if (recv((int)socket, messageReceive, sizeMessage * sizeof(char), 0) == -1)
    {
      redErrorMessage("Error message received\n");
    }

    // check if the client need to quit the chat server
    if (strcmp(messageReceive, "/quit") == 0)
    {
      printf("/quit server received \n");
      quitForUser(dS);
    }

    // check if the message received is a pm
    int resRegexPm = regex(messageReceive, "(pm).*");

    int resRegexAll = regex(messageReceive, "(ALL).*");


    regex_t regexJChannel;
    int resRegexJChannel = regcomp(&regexJChannel, "^/jchannel [0-9]*", REG_EXTENDED);
    resRegexJChannel = regexec(&regexJChannel, messageReceive, 0, NULL, 0);
    regfree(&regexJChannel);

    if (resRegexPm == 0)
    {
      printf("\n");
      purpleMessage(messageReceive);
      printf("\n");
    }
    else if (resRegexAll == 0){
      printf("\n");
      redMessage(messageReceive);
      printf("\n");
    }
    else if (resRegexJChannel == 0)
    {
      char **msg = str_split(messageReceive, 1);
      int port = atoi(msg[1]);
      shutdown(socket, 2);
      redMessage("\nYou left the channel \n");
      dS = socketConnection(port);
      break;
    }
    else
    {
      printf("\n");
      blueMessage(messageReceive);
      printf("\n");
    }
    printf("Enter your message (100 max) : \033[0;32m\n");
  }
  free(m);
  return NULL;
}

// Handler for ^C
void signalHandler(int n)
{
  quitForUser(dS);
}

int socketConnection(int port)
{
  int newdS = socket(PF_INET, SOCK_STREAM, 0);
  int enable = 1;
  if (newdS < 0)
  {
    redErrorMessage("ERROR opening socket for sending file");
  }
  if (setsockopt(newdS, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
  {
    redErrorMessage("setsockopt(SO_REUSEADDR) failed");
  }

  // info for sending file socket
  portSendingFile = port + 1;

  // fill info for socket dS
  struct sockaddr_in aS;
  aS.sin_family = AF_INET;
  inet_pton(AF_INET, ipAddress, &(aS.sin_addr));
  aS.sin_port = htons(port);
  socklen_t lgA = sizeof(struct sockaddr_in);

  // connection to socket newdS
  connect(newdS, (struct sockaddr *)&aS, lgA);
  return newdS;
}