#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "../headers/tools.h"

int regex(char* entry, char* model){
    regex_t regex;
    int regexRes;
    regexRes = regcomp(&regex, model, REG_EXTENDED);
    regexRes = regexec(&regex, entry, 0, NULL, 0);
    regfree(&regex);
    return regexRes;
}

void getRegexGroup (char *list[],int n, char *message, char *model) {
    regex_t regexCompiled;

    size_t maxGroups = n;
    regmatch_t groupArray[maxGroups];

    int regexRes = regex( message, model);

    if (regexRes == 0){
        regcomp(&regexCompiled, model, REG_EXTENDED);

        if (regexec(&regexCompiled, message, maxGroups, groupArray, 0) == 0) {
            for (int i = 0; i < maxGroups; i++) {
                if (groupArray[i].rm_so == (size_t)-1) {
                    break;  // No more groups
                }

                char sourceCopy[strlen(message) + 1];
                strcpy(sourceCopy, message);
                sourceCopy[groupArray[i].rm_eo] = 0;

                list[i] = (char *)malloc(strlen(sourceCopy + groupArray[i].rm_so));
                strcpy(list[i], sourceCopy + groupArray[i].rm_so);
            }
        }
        regfree(&regexCompiled);
    }
}