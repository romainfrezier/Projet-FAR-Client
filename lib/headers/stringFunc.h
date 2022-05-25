#ifndef STRING_FUNC_H_ /* Include guard */
#define STRING_FUNC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **str_split(char *msg, int n);         // Split command, with loop and argument n for generalization. Return a table of string
int countSpaceCommand(char *cmd, int nbSpace); // count the number of space in a command
char *strremove(char *str, const char *sub);

#endif // STRING_FUNC_H_