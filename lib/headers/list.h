/**
 * @file list.h
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Linked list of file
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef LIST_H_ /* Include guard */
#define LIST_H_

/**
 * @brief Data about file
 */
typedef struct File File;

/**
 * @brief Data about file
 *
 * @param id file id
 * @param filename filename
 * @param fileSize file size in bytes
 * @param next next File in the list
 */
struct File
{
    int id;
    char *filename;
    int fileSize;
    File *next;
};

/**
 * @brief Files list data
 */
typedef struct List List;

/**
 * @brief Files list data
 *
 * @param head first element of the linked list
 * @param last last element of the linked list
 */
struct List
{
    File *head;
    File *last;
};

/**
 * @brief Create an empty list
 *
 * @param size size of the list
 * @return the new List created
 */
List *createList();

/**
 * @brief Check if the list is empty
 *
 * @param list list to check
 * @return 0 -> list is empty
 * @return 1 -> list is not empty
 */
int listIsEmpty(List *list);

/**
 * @brief Add a file to the last position of the list
 *
 * @param list list where the file will be added
 * @param file data about file
 */
void addLast(List *list, File *file);

/**
 * @brief Next file in the linked list
 *
 * @param file actual file
 * @return next file
 */
File *next(File *file);

/**
 * @brief Delete the first element of the list
 *
 * @param list list where the element will be deleted
 */
void delFirst(List *list);

/**
 * @brief Delete an element of the list passed in arguments
 *
 * @param list list where the element will be deleted
 * @param file element to delete
 */
void delVal(List *list, File *file);

/**
 * @brief Recursive function to delete an element of the list
 *
 * @param file client from where we start to search
 */
void delValAux(File *file);

/**
 * @brief Check if the file id is in the list
 *
 * @param fileList list of files
 * @param id file id searched
 * @return 0 -> file id in the list
 * @return 1 -> file id not in the list
 */
int fileIdInList(List *fileList, int id);

/**
 * @brief Get the file id from the filename
 *
 * @param list list of files
 * @param filename file name searched
 * @return file id
 * @return -1 -> Error (file name not in the list)
 */
int getIdByFilename(List *list, char *filename);

/**
 * @brief Get the filename from the file id
 *
 * @param list list of files
 * @param id file id searched
 * @return file name
 * @return NULL -> Error (file id not in the list)
 */
char *getFilenameById(List *list, int id);

/**
 * @brief Display the list
 *
 * @param list list of files
 */
void displayFileList(List *list);

/**
 * @brief Fill the list with file of the folder passed in arguments
 *
 * @param folder folder to check
 * @param list list to fill
 */
void fillListFile(char *folder, List *list);

#endif // LIST_H_