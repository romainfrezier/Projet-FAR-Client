#include "stringFunc.h"

// char** str_split(char *msg)
// {
//     printf("Message : %s\n", msg);
//     int i = 0;
//     char* p = strtok(msg, " ");
//     char** array =(char**)malloc(3*sizeof(char*));
//     array[0] = (char*)malloc(strlen(p) + 1);
//     strcpy(array[0], p);
//     p = strtok(NULL, " ");
//     array[1] = (char*)malloc(strlen(p) + 1);
//     strcpy(array[1], p);
//     p = strtok(NULL, "\0");
//     array[2] = (char*)malloc(strlen(p) + 1);
//     strcpy(array[2], p);
//     return array;
// }

//Amélioration de la commande split, avec boucle et argument n pour généralisation

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
    int spaceFounded = 0;
    for(int i = 0; i <= strlen(cmd); i++)
  	{
        if(cmd[i] == ' ')  
        {
            spaceFounded += 1;
        }
	}
    if (spaceFounded >= nbSpace){
        return 1;
    }
    else {
        return -1;
    }
}