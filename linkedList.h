#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// A node of the linked list
typedef struct node {
    struct node *next;
    int value;
} Node;

// Keeps track of a linked list instance
typedef struct {
    Node *head;
    Node *tail;
    char *name;
    int initialized;
} LinkedList;

typedef enum {
    ERR_MEM, ERR_INIT_LIST, ERR_NO_INIT_LIST, ERR_CORRUPTED_LIST
} errors;

void initList(LinkedList *list, char *name);

int isEmpty(LinkedList *list);

void append(LinkedList *list, int val);

void prepend(LinkedList *list, int val);

int insertIdx(LinkedList *list, int idx, int val);

int deleteFirst(LinkedList *list);

int deleteLast(LinkedList *list);

int deleteIdx(LinkedList *list, int idx);

int count(LinkedList *list);

void printList(LinkedList *list, char *listName);

void printHeading(char *heading);

void freeList(LinkedList *list);

void exceptionHandler(errors err);

#endif //LINKED_LIST_H
