#include <stdio.h>
#include "linkedList.h"

#define DISPLAY_NAME_MAX 100

typedef enum {
    INIT, APPEND, PREPEND, INSERT_IDX, DEL_FIRST, DEL_LAST, DEL_IDX
} testCaseType;

void testCase(testCaseType type, LinkedList *list, char displayName[], const int *val, const int *idx) {
    switch (type) {
        case INIT:
            initList(list, "testList");
            snprintf(displayName, DISPLAY_NAME_MAX, "%s (initial)", list->name);
            break;
        case APPEND:
            if (val == NULL) return;
            append(list, *val);
            snprintf(displayName, DISPLAY_NAME_MAX, "%s (append)", list->name);
            break;
        case PREPEND:
            if (val == NULL) return;
            prepend(list, *val);
            snprintf(displayName, DISPLAY_NAME_MAX, "%s (prepend)", list->name);
            break;
        case INSERT_IDX:
            if (val == NULL || idx == NULL) return;
            insertIdx(list, *idx, *val);
            snprintf(displayName, DISPLAY_NAME_MAX, "%s (insert at index %d)", list->name, *idx);
            break;
        case DEL_FIRST:
            deleteFirst(list);
            snprintf(displayName, DISPLAY_NAME_MAX, "%s (delete first)", list->name);
            break;
        case DEL_LAST:
            deleteLast(list);
            snprintf(displayName, DISPLAY_NAME_MAX, "%s (delete last)", list->name);
            break;
        case DEL_IDX:
            if (idx == NULL) return;
            deleteIdx(list, *idx);
            snprintf(displayName, DISPLAY_NAME_MAX, "%s (delete at index %d)", list->name, *idx);
            break;
        default:
            return;
    }

    printList(list, displayName);
    printf("%s length: %d\n\n", list->name, count(list));
}

int main() {
    LinkedList list = {
        .head = NULL,
        .tail = NULL,
        .name = "",
        .initialized = 0
    };

    char displayName[DISPLAY_NAME_MAX];
    int val = 0;
    int idx = 0;

    printHeading("Running Test Cases");
    testCase(INIT, &list, displayName, NULL, NULL);
    testCase(APPEND, &list, displayName, &val, NULL);
    val++;
    testCase(PREPEND, &list, displayName, &val, NULL);
    val++;
    idx++;
    testCase(INSERT_IDX, &list, displayName, &val, &idx);
    testCase(DEL_FIRST, &list, displayName, NULL, NULL);
    testCase(DEL_LAST, &list, displayName, NULL, NULL);
    testCase(DEL_IDX, &list, displayName, NULL, &idx);
    idx = 0;
    testCase(DEL_IDX, &list, displayName, NULL, &idx);
    testCase(PREPEND, &list, displayName, &val, NULL);
    testCase(DEL_FIRST, &list, displayName, NULL, NULL);
    testCase(DEL_LAST, &list, displayName, NULL, NULL);
    idx = 10;
    testCase(INSERT_IDX, &list, displayName, &val, &idx);
    idx = 1;
    val = 1;
    testCase(INSERT_IDX, &list, displayName, &val, &idx);
    val = 3;
    testCase(PREPEND, &list, displayName, &val, NULL);
    val = 0;
    testCase(APPEND, &list, displayName, &val, NULL);

    freeList(&list);
    return 0;
}
