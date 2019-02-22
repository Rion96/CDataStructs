#include "LinkedList.h"
#include <stdlib.h>

struct LinkedList *linked_init(void *first_elem)
{
    struct LinkedList *list = malloc(sizeof(struct LinkedList));
    list->elem = first_elem;
    list->next = NULL;
    return list;
}

void linked_destroy(struct LinkedList **list)
{
    LinkedList *curr = *list;
    LinkedList *next = NULL;
    while(curr->next != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    (*list) = NULL;
}

/* Insert and delete functions */
void linked_append(struct LinkedList *list, void *elem);
void linked_prepend(struct LinkedList **list, void *elem);
void linked_remove(struct LinkedList **list, int index);