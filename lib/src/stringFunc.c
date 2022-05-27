/**
 * @file stringFunc.c
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief String functions implementation
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../headers/stringFunc.h"

char** str_split(char *msg, int n)
{
    int i = 0;
    char* p = strtok(msg, " ");
    char** array =(char**)malloc(n*sizeof(char*));
    array[i] = (char*)malloc(strlen(p) + 1);
    strcpy(array[i], p);
    i+= 1;
    if (n > 2){
        while (i < n - 1){
            p = strtok(NULL, " ");
            array[i] = (char*)malloc(strlen(p) + 1);
            strcpy(array[i], p);
            i+= 1;
        }
    }
    p = strtok(NULL, "\0");
    array[i] = (char*)malloc(strlen(p) + 1);
    strcpy(array[i], p);
    return array;
}

int countSpaceCommand(char* cmd, int nbSpace){
    int spaceFound = 0;
    for(int i = 0; i <= strlen(cmd); i++)
    {
        if(cmd[i] == ' ')
        {
            spaceFound += 1;
        }
    }
    if (spaceFound >= nbSpace){
        return 1;
    }
    else {
        return -1;
    }
}

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}