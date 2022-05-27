/**
 * @file colors.c
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Color library implementation
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "../headers/colors.h"

void greenMessage(char *message)
{
    printf("\033[0;32m");
    printf("%s", message);
    reset();
}

void blueMessage(char *message)
{
    printf("\033[0;34m");
    printf("%s", message);
    reset();
}

void purpleMessage(char *message)
{
    printf("\033[0;35m");
    printf("%s", message);
    reset();
}

void redMessage(char *message)
{
    printf("\033[0;31m");
    printf("%s", message);
    reset();
}

void redErrorMessage(char *message)
{
    redMessage(message);
    exit(0);
}

void reset()
{
    printf("\033[0m");
}