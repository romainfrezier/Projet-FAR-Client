/**
 * @file main.c
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Main function of client program
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdlib.h>

#include "lib/headers/client.h"
#include "lib/headers/colors.h"

/**
 * @brief
 */
int defaultPort = 4000;

/**
 * @brief Main function of client program
 * @param argc number of arguments given by the user
 * @param argv arguments given by the user
 * @return 0
 */
int main(int argc, char *argv[])
{
    // args check
    if (argc != 2)
    {
        redErrorMessage("Usage : ./exe IP");
    }

    launchClient(argv[1], defaultPort);
    return 0;
}