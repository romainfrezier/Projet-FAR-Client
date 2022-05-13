#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../headers/list.h"
#include "../headers/colors.h"

// Boolean : 0 = true ; 1 = false

List *createList()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

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

void addFirst(List *list, Link* fileList)
{
    Link *link = (Link *)malloc(sizeof(Link));
    link->id = fileList->id;
    link->filename = fileList->filename;
    if (list->head == NULL)
    {
        list->head = link;
        link->next = NULL;
    }
    else
    {
        link->next = list->head;
        list->head = link;
    }
    
}

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

void delFirst(List *list)
{
    if (list->head != NULL)
    {
        Link *deleted = list->head;
        list->head = list->head->next;
        free(deleted);
    }
}

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

void displayFileList(List *list)
{
    printf("\n");
    if (listIsEmpty(list) == 1)
    {
        blueMessage("List of your files : \n\n");
        Link *current = list->head;
        while (current != NULL)
        {
            printf("    %d. %s\n", current->id, current->filename);
            current = current->next;
        }
    }
    else
    {
        blueMessage("Your folder is empty\n");
    }
}

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
                addFirst(list,link);
            }
        }
        closedir(d);
    }
}