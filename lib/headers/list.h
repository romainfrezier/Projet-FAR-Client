#ifndef LIST_H_ /* Include guard */
#define LIST_H_

typedef struct Link Link;

struct Link
{
    int id;
    char *filename;
    Link *next;
};

typedef struct List List;

struct List
{
    Link *head;
};

List *createList();
int listIsEmpty(List *list);
void addFirst(List *list, Link *fileList);
Link *next(Link *link);
void delFirst(List *list);
void delVal(List *list, Link *fileList);
void delValAux(Link *fileList);
int fileIdInList(List *listFile, int id);
int getIdByFilename(List *list, char *filename);
char *getFilenameById(List *list, int id);
void displayFileList(List *list);
void fillListFile(char *folder, List *list);

#endif // LIST_H_