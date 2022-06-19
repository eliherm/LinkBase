#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

#define LIST_NAME_MAX 100
#define PROMPT_MAX 61
#define NUM_PROMPT_ARGS 61
#define PROMPT_ARG_LEN 21 // 20 chars for each argument

typedef enum {
    HELP, PRINT_LIST, COUNT, APPEND, PREPEND, INSERT_IDX, DEL_FIRST, DEL_LAST, DEL_IDX, NO_CMD, INVALID_CMD, QUIT
} cmdType;

void extractArgs(char input[], char argList[][PROMPT_ARG_LEN]) {
    int argIndex = 0;

    char *ptr = NULL;
    ptr = strtok(input, " ");
    if (ptr == NULL) return;

    strncpy(argList[argIndex], ptr, PROMPT_ARG_LEN);
    argList[argIndex][PROMPT_ARG_LEN - 1] = '\0'; // Ensure the output from strncpy is null terminated
    argIndex++;
    while(argIndex < 3) {
        ptr = strtok(NULL, " ");
        if (ptr == NULL) break;
        strncpy(argList[argIndex], ptr, PROMPT_ARG_LEN);
        argList[argIndex][PROMPT_ARG_LEN - 1] = '\0';
        argIndex++;
    }
}

void removeNewline(char in[]) {
    if ((strlen(in) > 0) && (in[strlen(in) - 1] == '\n')) {
        in[strlen(in) - 1] = '\0';
    }
}

void strToLower(char in[]) {
    for (char *p = in; *p; ++p) {
        *p = tolower(*p);
    }
}

/*
 * Command List
 * ------------
 * 1) help [Shows help menu]
 * 1) view [printList]
 * 2) count [count]
 * 3) append (value) [append]
 * 4) prepend (value) [prepend]
 * 5) insert (index) (value) [insertIdx]
 * 6) del_first [deleteFirst]
 * 7) del_last [deleteLast]
 * 8) del_idx [deleteIdx]
 */
cmdType cmdIndex(char cmd[]) {
    if (strcmp(cmd, "help") == 0) {
        return HELP;
    } else if (strcmp(cmd, "view") == 0) {
        return PRINT_LIST;
    } else if (strcmp(cmd, "count") == 0) {
        return COUNT;
    } else if (strcmp(cmd, "append") == 0) {
        return APPEND;
    } else if (strcmp(cmd, "prepend") == 0) {
        return PREPEND;
    } else if (strcmp(cmd, "insert") == 0) {
        return INSERT_IDX;
    } else if (strcmp(cmd, "del_first") == 0) {
        return DEL_FIRST;
    } else if (strcmp(cmd, "del_last") == 0) {
        return DEL_LAST;
    } else if (strcmp(cmd, "del_idx") == 0) {
        return DEL_IDX;
    } else if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
        return QUIT;
    } else if (strcmp(cmd, "") == 0) {
        return NO_CMD;
    } else {
        return INVALID_CMD;
    }
}

void prompt(LinkedList *list) {
    printf("\nInteract with list '%s' using the prompt below.\nRemember, you can always type 'help' for some assistance 😉.\n\n", list->name);

    int promptLoop = 1;
    int value;
    int idx;
    char *ptr = NULL;

    while (promptLoop) {
        char promptIn[PROMPT_MAX] = {};
        printf("> ");
        fgets(promptIn, PROMPT_MAX, stdin);
        removeNewline(promptIn);

        char argList[NUM_PROMPT_ARGS][PROMPT_ARG_LEN] = {};
        extractArgs(promptIn, argList);
        strToLower(argList[0]);

        switch (cmdIndex(argList[0])) {
            case HELP:
                printf("LinkBase v0.2.0\n⚠️  Note: All indexes and values must be integers\n\n");
                printf("%-20s\t%-20s\n", "view", "prints the contents of the list");
                printf("%-20s\t%-20s\n", "count", "counts the contents of the list");
                printf("%-20s\t%-20s\n", "append [value]", "appends a value to the list");
                printf("%-20s\t%-20s\n", "prepend [value]", "prepends a value to the list");
                printf("%-20s\t%-20s\n", "insert [index] [value]", "inserts a value into the list at a specified index");
                printf("%-20s\t%-20s\n", "del_first", "deletes the first value of the list");
                printf("%-20s\t%-20s\n", "del_last", "deletes the last value of the list");
                printf("%-20s\t%-20s\n", "del_idx [index]", "deletes a value at a specified index");
                printf("%-20s\t%-20s\n", "exit", "Ends the current session");
                printf("%-20s\t%-20s\n\n", "quit", "Ends the current session");
                break;
            case PRINT_LIST:
                printList(list, list->name);
                break;
            case COUNT:
                printf("List '%s' has %d entries.\n", list->name, count(list));
                break;
            case APPEND:
                errno = 0;
                value = (int) strtol(argList[1], &ptr, 10);
                if (errno != 0) {
                    printf("Invalid argument. The value supplied must be an integer.\n");
                    break;
                }

                append(list, value);
                printf("Value (%d) was successfully appended.\n", value);
                break;
            case PREPEND:
                errno = 0;
                value = (int) strtol(argList[1], &ptr, 10);
                if (errno != 0) {
                    printf("Invalid argument. The value supplied must be an integer.\n");
                    break;
                }

                prepend(list, value);
                printf("Value (%d) was successfully prepended\n", value);
                break;
            case INSERT_IDX:
                errno = 0;
                idx = (int) strtol(argList[1], &ptr, 10);
                value = (int) strtol(argList[2], &ptr, 10);
                if (errno != 0) {
                    printf("Incorrect syntax.\nUsage: insert [index] [value]\nNote: The index and value must be integers.\n\n");
                    break;
                }

                if (insertIdx(list, idx, value)) {
                    printf("Value (%d) was successfully inserted.\n", value);
                }
                break;
            case DEL_FIRST:
                if (deleteFirst(list)) {
                    printf("The first value has been deleted.\n");
                }
                break;
            case DEL_LAST:
                if (deleteLast(list)) {
                    printf("The last value has been deleted.\n");
                }
                break;
            case DEL_IDX:
                errno = 0;
                idx = (int) strtol(argList[1], &ptr, 10);
                if (errno != 0) {
                    printf("Incorrect syntax.\nUsage: del_idx [index]\nNote: The index must be an integer.\n\n");
                    break;
                }

                if (deleteIdx(list, idx)) {
                    printf("The value at index (%d) has been deleted.\n", idx);
                }
                break;
            case NO_CMD:
                break;
            case INVALID_CMD:
                printf("Invalid command 😖. Type 'help' to view the list of available commands.\n\n");
                break;
            case QUIT:
                printf("Stay safe 🤙\n\n");
                promptLoop = 0;
                break;
            default:
                printf("Invalid command 😖. Type 'help' to view the list of available commands.\n\n");
                break;
        }
    }
}

void initialize() {
    char listName[LIST_NAME_MAX] = {};
    while (1) {
        printf("What should we call your list? 🤔: ");
        fgets(listName, LIST_NAME_MAX, stdin);
        removeNewline(listName);

        if (strlen(listName) >= 3) {
            break;
        }

        printf("The name of the list must be at least 3 characters.\n\n");
    }

    LinkedList list = {
        .head = NULL,
        .tail = NULL,
        .name = "",
        .initialized = 0
    };
    initList(&list, listName);
    prompt(&list);
    freeList(&list);
}

int main() {
    printf("Welcome to LinkBase 💾.\nCopyright (c) 2020 Elikem Hermon. All rights reserved.\n\n");
    initialize();
    return 0;
}
