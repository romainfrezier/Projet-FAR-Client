/**
 * @file tools.h
 * @authors Romain FREZIER
 * @authors Etienne TILLIER
 * @brief Regex tools
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef TOOLS_H_ /* Include guard */
#define TOOLS_H_

/**
 * @brief Compare the entry with the regex
 *
 * @param entry message to compare
 * @param model regex
 * @return 0 -> the entry match with the model
 */
int regex(char *entry, char *model);

/**
 * @brief Get the group made by the regex
 *
 * @param list array to fill
 * @param n number of groups wanted
 * @param message message to compare
 * @param regexString regex
 */
void getRegexGroup (char *list[], int n, char *message, char *regexString);

#endif // TOOLS_H_