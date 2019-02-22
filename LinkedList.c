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
    struct LinkedList *curr = *list;
    struct LinkedList *next = NULL;
    while (curr->next != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(curr);
    *list = NULL;
}

void linked_append(struct LinkedList **list, void *elem)
{
    if ((*list) == NULL)
    {
        *list = linked_init(elem);
        return;
    }
    struct LinkedList *curr = *list;
    struct LinkedList *node = malloc(sizeof(struct LinkedList));
    node->elem = elem;
    node->next = NULL;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = node;
}

void linked_prepend(struct LinkedList **list, void *elem)
{
    struct LinkedList *node = malloc(sizeof(struct LinkedList));
    node->elem = elem;
    node->next = (*list);
    *list = node;
}

void *linked_poll(struct LinkedList **list)
{
    struct LinkedList *curr = *list;
    struct LinkedList *next = curr->next;
    void *elem = curr->elem;
    free(curr);
    *list = next;
    return elem;
}

void *linked_remove(struct LinkedList **list, int index)
{
    struct LinkedList *curr = *list;
    if (index == 0)
    {
        return linked_poll(list);
    }
    while (index > 1 && curr->next != NULL)
    {
        curr = curr->next;
        index--;
    }
    if (index > 1 || curr->next == NULL)
    {
        return NULL;
    }
    void *elem = curr->next->elem;
    struct LinkedList *next = curr->next->next;
    free(curr->next);
    curr->next = next;
    return elem;
}

int linked_length(struct LinkedList *list)
{
    if (list == NULL)
    {
        return 0;
    }
    int length = 1;
    while (list->next != NULL)
    {
        list = list->next;
        length++;
    }
    return length;
}