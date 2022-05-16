#ifndef LIST_H_ /* Include guard */
#define LIST_H_

typedef struct Link Link;

struct Link
{
    int id;
    char *filename;
    int fileSize;
    Link *next;
};

typedef struct List List;

struct List
{
    Link *head;
    Link *last;
};

List *createList();                             // create an empty list
int listIsEmpty(List *list);                    // check if the list is empty. Return 0 if the list is empty
void addLast(List *list, Link *fileList);       // add a file to the last position of the list
Link *next(Link *link);                         // go to the next Link of the list
void delFirst(List *list);                      // delete the first element of the list
void delVal(List *list, Link *fileList);        // delete an element of the list passed in arguments
void delValAux(Link *fileList);                 // recursive function to delete an element of the list
int fileIdInList(List *listFile, int id);       // chek if the file id is in the list. Return 0 if the file id is in the list
int getIdByFilename(List *list, char *filename);// get the file id from the filename
char *getFilenameById(List *list, int id);      // get the filename from the file id
void displayFileList(List *list);               // display the list
void fillListFile(char *folder, List *list);    // fill the list with file of the folder passed in arguments

#endif // LIST_H_