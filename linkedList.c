#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

void initList(LinkedList *list, char *name) {
    // Check for initialization issues
    if (list->head != NULL || list->tail != NULL || list->initialized != 0) {
        exceptionHandler(ERR_INIT_LIST);
    }

    list->name = name;
    list->initialized = 1;
}

int isEmpty(LinkedList *list) {
    if (list->head == NULL && list->tail == NULL) {
        return 1;
    } else if (list->head == NULL || list->tail == NULL) {
        exceptionHandler(ERR_CORRUPTED_LIST);
    }

    return 0;
}

void append(LinkedList *list, int val) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        exceptionHandler(ERR_MEM);
    }

    new->next = NULL;
    new->value = val;

    if (isEmpty(list)) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
}

void prepend(LinkedList *list, int val) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL) {
        exceptionHandler(ERR_MEM);
    }

    new->value = val;
    new->next = list->head;

    if (isEmpty(list)) {
        list->head = new;
        list->tail = new;
    } else {
        list->head = new;
    }
}

int insertIdx(LinkedList *list, int idx, int val) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    if (idx < 0) {
        printf("The specified index of %d is invalid. Only positive indexes are supported.\n", idx);
        return 0;
    }

    Node *new = (Node *) malloc(sizeof(Node));
    new->value = val;

    if (isEmpty(list)) {
        new->next = NULL;
        list->head = new;
        list->tail = new;
        printf("The list is empty. The new node will be inserted at index 0.\n");
        return 1;
    }

    // Insertion at the beginning of the linked list
    if (idx == 0) {
        new->next = list->head;
        list->head = new;
        return 1;
    }

    int listIdx = 0;
    Node *itr = list->head;
    while ((listIdx != idx - 1) && (itr != NULL)) {
        listIdx++;
        itr = itr->next;
    }

    if (itr == NULL) {
        printf("The specified index of %d is invalid. The linked list goes up to index %d.\n", idx, listIdx - 1);
        free(new);
        return 0;
    } else if (itr->next == NULL) {
        printf("The specified index of %d is invalid. The linked list goes up to index %d.\n", idx, listIdx);
        free(new);
        return 0;
    }

    // Insertion in the middle and at the end of the linked list
    new->next = itr->next;
    itr->next = new;
    if (itr == list->tail) {
        list->tail = new;
    }
    return 1;
}

int deleteFirst(LinkedList *list) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    if (isEmpty(list)) {
        printf("The list is empty, the specified node cannot be deleted.\n");
        return 0;
    }

    Node *temp = list->head;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
    }

    free(temp);
    return 1;
}

int deleteLast(LinkedList *list) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    if (isEmpty(list)) {
        printf("The list is empty, the specified node cannot be deleted.\n");
        return 0;
    }

    Node *temp = list->tail;
    if (list->tail == list->head) {
        list->head = NULL;
        list->tail = NULL;
        free(temp);
    } else {
        Node *itr = list->head;

        // Skip to the node before the tail
        while (itr->next != list->tail) {
            itr = itr->next;
        }

        itr->next = NULL;
        list->tail = itr;
        free(temp);
    }

    return 1;
}

int deleteIdx(LinkedList *list, int idx) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    if (idx < 0) {
        printf("The specified index of %d is invalid. Only positive indexes are supported.\n", idx);
        return 0;
    }

    if (isEmpty(list)) {
        printf("The list is empty. There is no node to delete.\n");
        return 0;
    }

    if (idx == 0) {
        deleteFirst(list);
        return 1;
    }

    int listIdx = 0;
    Node *itr = list->head;
    while ((listIdx != idx - 1) && (itr != NULL)) {
        listIdx++;
        itr = itr->next;
    }

    if (itr == NULL) {
        printf("The specified index of %d is invalid. The linked list goes up to index %d.\n", idx, listIdx - 1);
        return 0;
    } else if (itr->next == NULL) {
        printf("The specified index of %d is invalid. The linked list goes up to index %d.\n", idx, listIdx);
        return 0;
    }

    // Deleting in the middle and at the end of the linked list
    Node *temp = itr->next;
    if (itr->next == list->tail) {
        list->tail = itr;
    }

    itr->next = itr->next->next;
    free(temp);
    return 1;
}

int count(LinkedList *list) {
    if (isEmpty(list)) {
        return 0;
    }

    int count = 0;
    Node *itr = list->head;
    while (itr != NULL) {
        count++;
        itr = itr->next;
    }
    return count;
}

void printList(LinkedList *list, char *listName) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    if (isEmpty(list)) {
        printf("%s: [ ]\n", listName);
        return;
    }

    printf("%s: [ ", listName);
    Node *iterator = list->head;
    while (iterator->next != NULL) {
        printf("%d, ", iterator->value);
        iterator = iterator->next;
    }

    printf("%d ]\n", iterator->value);
}

void printHeading(char *heading) {
    printf("++");
    for (int i = 0; i < strlen(heading); ++i) {
        printf("-");
    }
    printf("++\n  %s  \n++", heading);
    for (int i = 0; i < strlen(heading); ++i) {
        printf("-");
    }
    printf("++\n");
}

void freeList(LinkedList *list) {
    if (list->initialized != 1) {
        exceptionHandler(ERR_NO_INIT_LIST);
    }

    char heading[100];
    snprintf(heading, 100, "Cleanup Log (%s)", list->name);
    printHeading(heading);

    if (isEmpty(list)) {
        list->name = NULL;
        printf("Nothing to clean. The list is empty.\n\n");
        return;
    }

    Node *iterator = list->head;
    while (iterator != list->tail) {
        Node *temp = iterator;
        iterator = iterator->next;

        if (temp == list->head) {
            printf("List head freed (%d)\n", temp->value);
        } else {
            printf("List node freed (%d)\n", temp->value);
        }

        free(temp);
    }

    printf("List tail freed (%d)\n\n", list->tail->value);
    free(list->tail);
    list->head = NULL;
    list->tail = NULL;
    list->name = NULL;
}

void exceptionHandler(errors err) {
    switch (err) {
        case ERR_MEM:
            perror("Error");
            exit(EXIT_FAILURE);

        case ERR_INIT_LIST:
            fprintf(stderr, "Error: The linked list could not be initialized\n");
            exit(EXIT_FAILURE);

        case ERR_NO_INIT_LIST:
            fprintf(stderr, "Error: The linked list has not been initialized\n");
            exit(EXIT_FAILURE);

        case ERR_CORRUPTED_LIST:
            fprintf(stderr, "Error: The linked list has been corrupted\n");
            exit(EXIT_FAILURE);

        default:
            fprintf(stderr, "Fatal: Unknown Error\n");
            perror("");
            exit(EXIT_FAILURE);
    }
}
