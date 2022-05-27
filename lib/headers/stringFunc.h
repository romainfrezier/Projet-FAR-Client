/**
 * @file stringFunc.h
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief String functions
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef STRING_FUNC_H_ /* Include guard */
#define STRING_FUNC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Split command, split a string at space
 *
 * @param msg : string to split
 * @param n : number of space in the string
 * @return table of string
 */
char **str_split(char *msg, int n);

/**
 * @brief Check the number of space in a command
 *
 * @param cmd : command to check
 * @param nbSpace : number of space that the server expects
 * @return 1 -> number of space in the command >= nbSpace
 * @return -1 -> number of space in the command < nbSpace
 */
int countSpaceCommand(char *cmd, int nbSpace);

/**
 * @brief Remove a substring of the string
 *
 * @param str : string to analyze
 * @param sub : sub-string to find and remove
 * @return the string without the sub-string
 */
char *strremove(char *str, const char *sub);

#endif // STRING_FUNC_H_