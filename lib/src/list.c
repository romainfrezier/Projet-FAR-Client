#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "../headers/list.h"
#include "../headers/colors.h"

// Boolean : 0 = true ; 1 = false

// create an empty list
List *createList()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->last = NULL;
    return list;
}

// check if the list is empty. Return 0 if the list is empty
int listIsEmpty(List *list)
{
    if (list->head == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// add a file to the last position of the list
void addLast(List *list, Link* fileList)
{
    Link *link = (Link *)malloc(sizeof(Link));
    link->id = fileList->id;
    link->filename = fileList->filename;
    if (list->head == NULL)
    {
        list->head = link;
        list->last = link;
        link->next = NULL;
    }
    else
    {
        list->last->next = link;
        list->last = link;
        list->last->next = NULL;
    }
}

// go to the next Link of the list
Link *next(Link *link)
{
    if (link->next == NULL)
    {
        return NULL;
    }
    else
    {
        return link->next;
    }
}

// delete the first element of the list
void delFirst(List *list)
{
    if (list->head != NULL)
    {
        Link *deleted = list->head;
        list->head = list->head->next;
        free(deleted);
    }
}

// delete an element of the list passed in arguments
void delVal(List *list, Link* fileList)
{
    if (listIsEmpty(list) == 1)
    {
        if (list->head->id == fileList->id)
        {
            delFirst(list);
        }
        else
        {
            delValAux(list->head);
        }
    }
    else
    {
        printf("list of sockets is empty !");
    }
}

// recursive function to delete an element of the list
void delValAux(Link *fileList)
{
    if (fileList->next != NULL)
    {
        if (fileList->next->id == fileList->id)
        {
            Link *deleted = fileList->next;
            deleted->next = fileList->next->next;
            free(deleted);
        }
        else
        {
            delValAux(fileList->next);
        }
    }
    else
    {
        printf("Value not found !");
    }
}

// chek if the file id is in the list. Return 0 if the file id is in the list
int fileIdInList(List *listFile, int id)
{
    if (listIsEmpty(listFile) == 1)
    {
        Link *current = listFile->head;
        while (current != NULL && current->id != id)
        {
            current = current->next;
        }
        if (current != NULL && current->id == id)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

// get the file id from the filename
int getIdByFilename(List *list, char *filename)
{
    if (listIsEmpty(list) == 1)
    {
        Link *current = list->head;
        while (current != NULL && (strcmp(current->filename, filename) != 0))
        {
            current = current->next;
        }
        if (current != NULL && (strcmp(current->filename, filename) == 0))
        {
            return current->id;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

// get the filename from the file id
char *getFilenameById(List *list, int id)
{
    if (listIsEmpty(list) == 1)
    {
        Link *current = list->head;
        while (current != NULL && id != current->id)
        {
            current = current->next;
        }
        if (current != NULL && current->id == id)
        {
            return current->filename;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

// display the list
void displayFileList(List *list)
{
    printf("\n");
    if (listIsEmpty(list) == 1)
    {
        blueMessage("\nList of your files : \n\n");
        Link *current = list->head;
        while (current != NULL)
        {
            printf("\033[0;34m"); // colors for complex string
            printf("    %d. %s\n", current->id, current->filename);
            reset();
            current = current->next;
        }
    }
    else
    {
        blueMessage("Your folder is empty\n");
    }
}

// fill the list with file of the folder passed in arguments
void fillListFile(char *folder, List* list)
{
    DIR *d;
    struct dirent *dir;
    Link *link = malloc(sizeof(link));
    
    d = opendir(folder);
    if (d)
    {
        int i = 1;
        while ((dir = readdir(d)) != NULL)
        {
            if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0))
            {
                link->filename = dir->d_name;
                link->id = i;
                i++;
                addLast(list,link);

            }
        }
        closedir(d);
    }
}