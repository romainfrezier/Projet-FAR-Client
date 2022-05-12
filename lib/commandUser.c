#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "commandUser.h"

// Disconnects the user
void quitForUser(int socket)
{
    char *m = "/quit";
    u_long size = strlen(m);

    if (send(socket, &size, sizeof(u_long), 0) == -1)   // Send message size
    {
        redErrorMessage("Error sending size\n");
    }

    if (send(socket, m, size, 0) == -1)                 // Send message
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
    manual = fopen("./lib/command.txt", "rt");  // open the manual file (command.txt)
    printf("\033[0;34m");                       // make the color blue to print char (can't use blueMessage, the function wants a char*)
    while ((c = fgetc(manual)) != EOF)
    {
        printf("%c",c);                         // print every character of the manual file
        
    }
    reset();                                    // reset the print color
    fclose(manual);
    printf("\n\n");
}