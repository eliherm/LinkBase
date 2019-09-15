#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct node {
    struct node *next;
    int value;
    bool empty;
} Node;

typedef struct idx_node {
    struct idx_node *next;
    Node *entries;
    char name[21];
} indexNode;

typedef enum { ERR_MEM, ERR_INIT, ERR_NO_INIT } errors;
void exceptionHandler(errors err) {
    switch (err) {
        case ERR_MEM:
            perror("Error");
            exit(EXIT_FAILURE);
        case ERR_INIT:
            fprintf(stderr, "Error: The linked list is already initialized\n");
            break;
        case ERR_NO_INIT:
            fprintf(stderr, "Error: The linked list is not initialized\n");
            break;
        default:
            fprintf(stderr, "Fatal: Unknown Error\n");
            exit(EXIT_FAILURE);
    }
}

Node* initList(Node *listHead) {
    if (listHead != NULL) {
        exceptionHandler(ERR_INIT);
        return NULL;
    }

    // Create a new node
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        exceptionHandler(ERR_MEM);
        return NULL;
    }

    new->value = 0;
    new->next = NULL;
    new->empty = true;
    listHead = new;
    return listHead;
}

Node* append(Node *listHead, int val) {
    if (listHead == NULL) {
        exceptionHandler(ERR_NO_INIT);
        return NULL;
    }

    // Create a new node
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        exceptionHandler(ERR_MEM);
        return NULL;
    }

    new->value = val;
    new->next = NULL;
    new->empty = false;

    // Find the end of the list
    Node *Tail = listHead;
    while (Tail->next != NULL) Tail = Tail->next; // Iterate to the end of the linked list
    Tail->next = new;
    return listHead;
}

Node* prepend(Node *listHead, int val) {
    // Create a new node
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        exceptionHandler(ERR_MEM);
        return NULL;
    }

    new->value = val;
    new->next = listHead;
    new->empty = false;
    listHead = new;
    return listHead;
}

indexNode* prependIndex(indexNode *listHead, Node *entries, char name[]) {
    // Create a new node
    indexNode *new = (indexNode *) malloc(sizeof(indexNode));
    if (new == NULL) {
        exceptionHandler(ERR_MEM);
        return NULL;
    }

    new->entries = entries;
    new->next = listHead;
    strcpy(new->name, name);
    listHead = new;
    return listHead;
}

indexNode* deleteIndex(indexNode *listHead, char name[], bool *success) {
    bool exists = false;

    if (listHead == NULL) {
        exceptionHandler(ERR_NO_INIT);
        return NULL;
    }

    indexNode *current = listHead;
    indexNode *prev = NULL;

    while(current != NULL) {
        if (strcmp(current->name, name) == 0) {
            exists = true;
            break;
        }

        if (current->next == NULL) break;
        prev = current;
        current = current->next;
    }

    if (exists) {
        if (current == listHead) {
            listHead = listHead->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        *success = true;
        return listHead;
    } else {
        *success = false;
        return listHead;
    }
}

void printList(Node *listHead, char title[]) {
    if (listHead == NULL) {
        exceptionHandler(ERR_NO_INIT);
        return;
    }

    Node *iterator = listHead;
    printf("%s: [ ", title);

    // Check for empty collections
    if (iterator->empty == true) {
        printf("]\n");
        return;
    }

    while(iterator != NULL) {
        if (iterator->next == NULL) {
            printf("%d ]\n", iterator->value);
            break;
        }
        printf("%d, ", iterator->value);
        iterator = iterator->next;
    }
}
