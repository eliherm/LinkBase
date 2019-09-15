#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"

#define ARG_LENGTH 21 // 20 chars for each argument
#define INPUT_LENGTH 61

indexNode *indexHead = NULL;

void convertCase(char arg[]) {
    int i = 0;
    while(arg[i] != '\0') {
        arg[i] = tolower(arg[i]);
        i++;
    }
}

indexNode* findCollection(char name[]) {
    indexNode *current = indexHead;

    while(current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        if (current->next == NULL) break;
        current = current->next;
    }

    return NULL;
}

void createCollection(char name[]) {
    if (name[0] == '\0') {
        fprintf(stderr, "Enter a collection name\n");
        return;
    }

    if (findCollection(name) == NULL) {
        Node *Collection = NULL;
        Collection = initList(Collection);
        indexHead = prependIndex(indexHead, Collection, name);
        printf("Collection %s was successfully created\n", name);
    } else {
        fprintf(stderr, "%s cannot be created, it already exists\n", name);
    }

}

void prependCollection(char name[], int value) {
    if (name[0] == '\0') {
        fprintf(stderr, "Enter a collection name\n");
        return;
    }

    indexNode *collection = findCollection(name);
    if (collection != NULL) {
        if (collection->entries->empty == true) {
            collection->entries->value = value;
            collection->entries->empty = false;
        } else {
            collection->entries = prepend(collection->entries, value);
        }
        printf("Collection %s was successfully updated\n", name);
    } else {
        fprintf(stderr, "Collection %s was not not found\n", name);
    }
}

void appendCollection(char name[], int value) {
    if (name[0] == '\0') {
        printf("Enter a collection name\n");
        return;
    }

    indexNode *collection = findCollection(name);
    if (collection != NULL) {
        if (collection->entries->empty == true) {
            collection->entries->value = value;
            collection->entries->empty = false;
        } else {
            collection->entries = append(collection->entries, value);
        }
        printf("Collection %s was successfully updated\n", name);
    } else {
        fprintf(stderr, "Collection %s was not not found\n", name);
    }
}

void viewDB() {
    if (indexHead == NULL) {
        fprintf(stderr, "The are no collections to be viewed\n");
        return;
    }

    indexNode *collection = indexHead;
    while (collection != NULL) {
        printList(collection->entries, collection->name);
        if (collection->next == NULL) break;
        collection = collection->next;
    }
}

void viewCollection(char name[]) {
    if (indexHead == NULL) {
        fprintf(stderr, "The are no collections to be viewed\n");
        return;
    }

    if (name[0] == '\0') {
        fprintf(stderr, "Enter a collection name\n");
        return;
    }

    indexNode *collection = findCollection(name);
    if (collection != NULL) {
        printList(collection->entries, collection->name);
    } else {
        fprintf(stderr, "Collection %s was not not found\n", name);
    }
}

void deleteCollection(char name[]) {
    if (indexHead == NULL) {
        fprintf(stderr, "The are no collections to be deleted\n");
        return;
    }

    if (name[0] == '\0') {
        fprintf(stderr, "Enter a collection name\n");
        return;
    }

    char confirmation[10] = {};
    printf("Warning: This action cannot be reverted\nAre you sure you want to delete collection %s ?\nEnter 'y' or 'n' to confirm: ", name);
    fgets(confirmation, 10, stdin);

    // Remove newline
    if ((strlen(confirmation) > 0) && (confirmation[strlen(confirmation) - 1] == '\n')) {
        confirmation[strlen(confirmation) - 1] = '\0';
    }

    convertCase(confirmation);
    if ((strcmp(confirmation, "y") == 0) || (strcmp(confirmation, "yes") == 0)) {
        bool success;
        indexHead = deleteIndex(indexHead, name, &success);
        if (success) {
            printf("\nCollection %s was successfully deleted\n", name);
        } else {
            fprintf(stderr, "Collection %s was not found\n", name);
        }
    } else {
        printf("\n");
    }
}

void extractArgs(char input[], char argList[][ARG_LENGTH]) {
    int argIndex = 0;

    char *ptr = NULL;
    ptr = strtok(input, " ");
    if (ptr == NULL) return;

    strcpy(argList[argIndex], ptr);
    argIndex++;
    while(argIndex < 3) {
        ptr = strtok(NULL, " ");
        if (ptr == NULL) break;
        strcpy(argList[argIndex], ptr);
        argIndex++;
    }
}

int commandList(char cmd[]) {
    if (strcmp(cmd, "help") == 0) {
        return 1;
    } else if (strcmp(cmd, "create") == 0) {
        return 2;
    } else if (strcmp(cmd, "prepend") == 0) {
        return 3;
    } else if (strcmp(cmd, "append") == 0) {
        return 4;
    } else if (strcmp(cmd, "view") == 0) {
        return 5;
    } else if (strcmp(cmd, "delete") == 0) {
        return 6;
    } else if ((strcmp(cmd, "exit") == 0) || (strcmp(cmd, "quit") == 0)) {
        return 0;
    } else {
        return -1;
    }
}

// TODO: Use getch() for arrow keys
void prompt() {
    bool isTerminated = false;
    char *endPtr = NULL;
    int value = 0;

    while (!isTerminated) {
        char input[INPUT_LENGTH] = {};
        printf("> ");
        fgets(input, INPUT_LENGTH, stdin);

        // Remove newline
        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n')) {
            input[strlen(input) - 1] = '\0';
        }

        char argList[3][ARG_LENGTH] = {};
        extractArgs(input, argList);

        convertCase(argList[0]); // Convert command to lowercase
        switch(commandList(argList[0])) {
            case 1: // Help
                printf("Display help\n");
                break;
            case 2: // Create collection
                createCollection(argList[1]);
                break;
            case 3: // Prepend to collection
                value = (int) strtol(argList[2], &endPtr, 10);
                prependCollection(argList[1], value);
                break;
            case 4: // Append to collection
                value = (int) strtol(argList[2], &endPtr, 10);
                appendCollection(argList[1], value);
                break;
            case 5: // Display collection(s)
                convertCase(argList[1]); // Convert flag to lowercase

                if ((strcmp(argList[1], "--all") == 0) || (strcmp(argList[1], "-a") == 0)) {
                    viewDB();
                } else if ((strcmp(argList[1], "--one") == 0) || (strcmp(argList[1], "-o") == 0)) {
                    viewCollection(argList[2]);
                } else {
                    printf("Incorrect syntax.\nView all collections: view [--all / -a]\nView one collection: view [--one / -o] [collection name]\n");
                }
                break;
            case 6: // Delete a collection
                deleteCollection(argList[1]);
                break;
            case 0:
                // Exit
                isTerminated = true;
                break;
            default:
                printf("Invalid command. Type 'help' for a list of commands.\n");
        }
    }
}

int main() {
    printf("Welcome to LinkBase.\nCopyright (c) 2019 Elikem Hermon. All rights reserved.\n\nType 'help' for help.\n\n");
    prompt();
}
