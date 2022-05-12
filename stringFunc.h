#ifndef STRING_FUNC_H_ /* Include guard */
#define STRING_FUNC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** str_split(char* msg, int n);

int verifCommand(char* cmd, int nbSpace);

#endif // STRING_FUNC_H_