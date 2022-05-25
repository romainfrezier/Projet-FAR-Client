#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "../headers/client.h"
#include "../headers/colors.h"
#include "../headers/commandClient.h"
#include "../headers/list.h"
#include "../headers/fileClient.h"
#include "../headers/tools.h"

// Sending a specific message to the server
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

// Disconnects the user
void quitForUser(int socket)
{
    char *m = "/quit";
    u_long size = strlen(m);

    if (send(socket, &size, sizeof(u_long), 0) == -1) // Send message size
    {
        redErrorMessage("Error sending size\n");
    }

    if (send(socket, m, size, 0) == -1) // Send message
    {
        redErrorMessage("Error sending message\n");
    }
    exit(0); // Exit process whatever happens
}

// Display the command manual
void displayManual()
{
    FILE *manual;
    char c;
    manual = fopen("./lib/command.txt", "rt"); // open the manual file (command.txt)
    printf("\033[0;34m");                      // make the color blue to print char (can't use blueMessage, the function wants a char*)
    while ((c = fgetc(manual)) != EOF)
    {
        printf("%c", c); // print every character of the manual file
    }
    reset(); // reset the print color
    fclose(manual);
    printf("\n\n");
}

// check user given command
void checkCommand(char *m, char *ipAddress, int portSendingFile, int socket)
{
    int resRegexSFile = regex(m, "^/sfile *$");
    int resRegexDFile = regex(m, "^/dfile +([^ ]*) *$");

    if (strcmp(m, "/man") == 0)
    {
        displayManual();
    }
    else if (resRegexSFile == 0)
    {
        // make a choice menu for sending file
        List *list = createList();
        fillListFile("userStorage/", list);
        displayFileList(list);
        char *selected = (char *)malloc(12 * sizeof(char));
        int entryAccepted = 1;
        int quitMenu = 1;
        int id;
        do
        {
            blueMessage("\nEnter the number of the file you want to send : ");
            fgets(selected, 12, stdin);


            int resRegexSelectFile = regex(selected, "[0-9]");
            int resRegexQuitSelectFile = regex(selected, "q");
            

            if (resRegexSelectFile == 0)
            {
                id = atoi(selected);
                if (fileIdInList(list, id) == 0)
                {
                    entryAccepted = 0;
                }
                else
                {
                    redMessage("\nPlease enter a valid number");
                    displayFileList(list);
                }
            }
            else if (resRegexQuitSelectFile == 0)
            {
                entryAccepted = 0;
                quitMenu = 0;
            }
            else
            {
                redMessage("\nPlease enter a number");
                displayFileList(list);
            }
        } while (entryAccepted != 0);
        if (quitMenu != 0)
        {
            // send file to the server if the user don't quit the menu
            char *filename = getFilenameById(list, id);
            free(list);

            // send socket data to the server
            sendFileStruct data;
            data.socketServer = socket;
            data.filename = filename;
            connectSocketFileSend(&data, portSendingFile, ipAddress);
        }
    }
    else if (resRegexDFile == 0)
    {
        // send socket data to the server
        getFileStruct data;
        data.socketServer = socket;
        data.cmd = m;
        connectSocketFileGet(&data, portSendingFile + 1, ipAddress);
    }
    else
    {
        // send a classic message
        sendSpecificMessage(socket, m);
    }
}