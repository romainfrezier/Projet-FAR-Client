/**
 * @file fileClient.h
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief File functions
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef FILECLIENT_H_ /* Include guard */
#define FILECLIENT_H_

/**
 * @brief Data for sending file
 */
typedef struct sendFileStruct sendFileStruct;

/**
 * @brief Data for sending file
 *
 * @param socketServer socket descriptor for the connexion between client and server
 * @param filename file name
 * @param path file path
 * @param fileSize size fo the file in bytes
 */
struct sendFileStruct
{
    int socketServer;
    char *filename;
    char *path;
    long fileSize;
};

/**
 * @brief Data for receiving file
 */
typedef struct getFileStruct getFileStruct;

/**
 * @brief Data for receiving file
 *
 * @param socketServer socket descriptor for the connexion between client and server
 * @param cmd message from the client
 */
struct getFileStruct
{
    int socketServer;
    char *cmd;
};

/**
 * @brief Data of the file
 */
typedef struct fileStruct fileStruct;

/**
 * @brief Data of the file
 *
 * @param filenameSize Size of the filename
 * @param fileSize Size of the file in bytes
 * @param path file path
 */
struct fileStruct
{
    size_t filenameSize;
    long fileSize;
    char *path;
};

/**
 * @brief Connect socket for send file
 *
 * @param data data for sending file
 * @param port port for sending file
 * @param ip ip address of the server
 */
void connectSocketFileSend(sendFileStruct *data, int port, char *ip);

/**
 * @brief Connect socket for get file
 *
 * @param data data for receiving file
 * @param port port for receiving file
 * @param ip ip address of the server
 */
void connectSocketFileGet(getFileStruct *data, int port, char *ip);

/**
 * @brief Prepare the sending of the file
 *
 * @param sendFileData data for sending file
 * @return NULL
 */
void * prepareTransfer(void *sendFileData);

/**
 * @brief Transfer the file to the server
 *
 * @param socket socket descriptor for the connexion between client and server
 * @param file file data
 * @param name file name
 */
void fileTransfer(int socket, fileStruct *file, char *name);

/**
 * @brief Prepare the receiving of the file
 *
 * @param data data for receiving file
 * @return NULL
 */
void * prepareGetFile(void *data);

/**
 * @brief Receive the file from the server
 *
 * @param fileInfo file data
 * @param serverSocket socket descriptor for the connexion between client and server
 * @param filename file name
 */
void receiveFile(fileStruct *fileInfo, int serverSocket, char *filename);

/**
 * @brief Choose a file name for the file transferred, with the objective to not overwrite the file
 *
 * @param nameFile the file name of the file that the client send
 * @param i used for recursive call. Initial value need to be 1
 * @return the new filename
 */
char *chooseNameFile(char *nameFile, int i);

#endif // FILECLIENT_H_