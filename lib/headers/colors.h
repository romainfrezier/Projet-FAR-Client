/**
 * @file colors.h
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Color library
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef COLORS_H_ /* Include guard */
#define COLORS_H_

/**
 * @brief Print a green message
 *
 * @param message : string to print
 */
void greenMessage(char *message);

/**
 * @brief Print a blue message
 *
 * @param message : string to print
 */
void blueMessage(char *message);

/**
 * @brief Print a purple message
 *
 * @param message : string to print
 */
void purpleMessage(char *message);

/**
 * @brief Print a red message
 *
 * @param message : string to print
 */
void redMessage(char *message);

/**
 * @brief Print a red message and exit the process
 * @brief Use it for errors
 *
 * @param message : string to print
 */
void redErrorMessage(char *message);

/**
 * @brief Reset the print color
 */
void reset();

#endif // COLORS_H_