/**
 * @file list.c
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Implementation of a linked list of file
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../headers/list.h"
#include "../headers/colors.h"

List *createList()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->last = NULL;
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

void addLast(List *list, File* file)
{
    File *link = (File *)malloc(sizeof(File));
    link->id = file->id;
    link->filename = file->filename;
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

File *next(File *file)
{
    if (file->next == NULL)
    {
        return NULL;
    }
    else
    {
        return file->next;
    }
}

void delFirst(List *list)
{
    if (list->head != NULL)
    {
        File *deleted = list->head;
        list->head = list->head->next;
        free(deleted);
    }
}

void delVal(List *list, File* file)
{
    if (listIsEmpty(list) == 1)
    {
        if (list->head->id == file->id)
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

void delValAux(File *file)
{
    if (file->next != NULL)
    {
        if (file->next->id == file->id)
        {
            File *deleted = file->next;
            deleted->next = file->next->next;
            free(deleted);
        }
        else
        {
            delValAux(file->next);
        }
    }
    else
    {
        printf("Value not found !");
    }
}

int fileIdInList(List *fileList, int id)
{
    if (listIsEmpty(fileList) == 1)
    {
        File *current = fileList->head;
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
        File *current = list->head;
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
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

char *getFilenameById(List *list, int id)
{
    if (listIsEmpty(list) == 1)
    {
        File *current = list->head;
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
        blueMessage("\nList of your files : \n\n");
        File *current = list->head;
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

void fillListFile(char *folder, List* list)
{
    DIR *d;
    struct dirent *dir;
    File *link = malloc(sizeof(link));
    
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