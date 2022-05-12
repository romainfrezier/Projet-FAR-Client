#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

// Functions to print in color
// Green for transmitting message
void greenMessage(char *message)
{
    printf("\033[0;32m");
    printf("%s", message);
    reset();
}
// Blue for receiving message
void blueMessage(char *message)
{
    printf("\033[0;34m");
    printf("%s", message);
    reset();
}
// Purple for receiving private message
void purpleMessage(char *message)
{
    printf("\033[0;35m");
    printf("%s", message);
    reset();
}

// Red for errors
void redMessage(char *message)
{
    printf("\033[0;31m");
    printf("%s", message);
    reset();
}

// Red for errors with exit
void redErrorMessage(char *message)
{
    redMessage(message);
    exit(0);
}

// Reset color to white
void reset()
{
    printf("\033[0m");
}