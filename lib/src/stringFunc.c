#include "../headers/stringFunc.h"

// Split command, with loop and argument n for generalization

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

int verifCommand(char* cmd, int nbSpace){
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