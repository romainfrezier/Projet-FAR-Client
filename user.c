#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <regex.h>

#include "lib/user.h"
#include "lib/colors.h"
#include "lib/stringFunc.h"
#include "lib/fileUser.h"
#include "lib/commandUser.h"

#define MAX 100

regex_t regex;
struct sockaddr_in aS;

int dS;
char *ipAddress;
int portSendingFile;

// We want a thread that manages the shipment and another who manages the receipt
int
main(int argc, char *argv[])
{
  // args check
  if (argc != 3){
    redErrorMessage("Usage : ./exe IP port");
  }
  if (atoi(argv[2]) <= 1024){
    redErrorMessage("Bad port: must be greater than 1024");
  }

  greenMessage("Start program\n");

  int enable = 1;

  dS = socket(PF_INET, SOCK_STREAM, 0);
  if (dS < 0)
  {
    redErrorMessage("ERROR opening socket for sending file");
  }
  if (setsockopt(dS, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
  {
    redErrorMessage("setsockopt(SO_REUSEADDR) failed");
  }

  // info for sending file socket
  ipAddress = argv[1];
  portSendingFile = atoi(argv[2]) + 1;

  // fill info for socket dS
  struct sockaddr_in aS;
  aS.sin_family = AF_INET;
  inet_pton(AF_INET, ipAddress, &(aS.sin_addr));
  aS.sin_port = htons(atoi(argv[2]));
  socklen_t lgA = sizeof(struct sockaddr_in);

  // connection to socket dS
  connect(dS, (struct sockaddr *)&aS, lgA);

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
    } else {
      greenMessage(isConnected);
      printf("\n\n");
    }
  } while (check != 0);

  // Execution of threads
  pthread_t send;
  pthread_t receive;
  pthread_create(&send, NULL, sendMessage, dS);
  pthread_create(&receive, NULL, receiveMessage, dS);

  // Waiting for the end of threads
  pthread_join(send, 0);
  pthread_join(receive, 0);

  // Shutdown of socket
  shutdown(dS, 2);
  printf("End program\n");
}

void sendMessage(int socket)
{
  char *m = (char *)malloc(MAX * sizeof(char));

  int resRegexSFile;
  while (strcmp(m, "/quit") != 0)
  {
    // User input
    printf("Enter your message (100 max) : \n");
    fgets(m, 100, stdin);
    m[strcspn(m, "\n")] = 0;
    greenMessage("My message : ");
    greenMessage(m);
    printf("\n");
    u_long size = strlen(m) + 1;

    resRegexSFile = regcomp(&regex, "^/sfile[:print:]*", 0);
    resRegexSFile = regexec(&regex, m, 0, NULL, 0);

    if (strcmp(m, "/man") == 0)
    {
      displayManual();
    }
    else if (resRegexSFile == 0)
    {
      // send socket data to the server
      sendFileStruct data;
      data.socketServer = socket;
      data.cmd = m;
      connectSocketFile(&data, portSendingFile, ipAddress);
    }
    else
    {
      sendSpecificMessage(socket, m);
    }
  }
  shutdown(socket, 2);
  free(m);
  exit(0);
}

void receiveMessage(int socket)
{
  char *m = (char *)malloc(MAX * sizeof(char));
  while (1)
  {
    // Size reception
    u_long sizeMessage;
    int receive = recv(socket, &sizeMessage, sizeof(u_long), 0);
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
    if (recv(socket, messageReceive, sizeMessage * sizeof(char), 0) == -1)
    {
      redErrorMessage("Error message received\n");
    }

    // check if the user need to quit the chat server
    if (strcmp(messageReceive, "/quit") == 0)
    {
      printf("/quit server received \n");
      quitForUser(dS);
    }

    // check if the message received is a pm
    int resRegexPm;
    resRegexPm = regcomp(&regex, "^(pm)[:print:]*", 0);
    resRegexPm = regexec(&regex, messageReceive, 0, NULL, 0);

    if (resRegexPm == 0)
    {
      purpleMessage(messageReceive);
    }
    else
    {
      blueMessage(messageReceive);
    }
    printf("\n");
    printf("Enter your message (100 max) : \n");
  }
  free(m);
}

void sendSpecificMessage(int client, char *message)
{
  u_long sizeMessage = strlen(message) + 1;
  // Send connection message size
  if (send(client, &sizeMessage, sizeof(u_long), 0) == -1)
  {
    redErrorMessage("Error sending size\n");
  }
  // Send connection message
  if (send(client, message, sizeMessage, 0) == -1)
  {
    redErrorMessage("Error sending connection message\n");
  }
}

void signalHandler(int n)
{
  quitForUser(dS);
}