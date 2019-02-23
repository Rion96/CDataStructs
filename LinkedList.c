#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

struct LinkedList *linked_init(void *first_elem)
{
    struct LinkedList *list = malloc(sizeof(struct LinkedList));
    if (list == NULL)
    {
        fprintf(stderr, "Error: Could not initialize LinkedList struct!\n");
        return NULL;
    }
    list->elem = first_elem;
    list->next = NULL;
    return list;
}

void linked_destroy(struct LinkedList **list)
{
    struct LinkedList *curr = *list;
    struct LinkedList *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *list = NULL;
}

void linked_append(struct LinkedList **list, void *elem)
{
    struct LinkedList *curr = *list;
    if (curr == NULL)
    {
        *list = linked_init(elem);
        return;
    }
    struct LinkedList *node = malloc(sizeof(struct LinkedList));
    if (node == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for LinkedList!\n");
        return;
    }
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
    if (node == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for LinkedList!\n");
        return;
    }
    node->elem = elem;
    node->next = (*list);
    *list = node;
}

void *linked_poll(struct LinkedList **list)
{
    if (list == NULL)
    {
        return NULL;
    }
    struct LinkedList *curr = *list;
    struct LinkedList *next = curr->next;
    void *elem = curr->elem;
    free(curr);
    *list = next;
    return elem;
}

void *linked_peek(struct LinkedList *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->elem;
}

void *linked_get(struct LinkedList *list, int index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index == 0)
    {
        return linked_peek(list);
    }
    while (index > 0 && list->next != NULL)
    {
        list = list->next;
        index--;
    }
    if (index > 0)
    {
        return NULL;
    }
    return list->elem;
}

void linked_add(struct LinkedList **list, void *elem, int index)
{
    struct LinkedList *curr = *list;
    int length = linked_length(curr);
    if (index < 0 || index > length)
    {
        return;
    }
    if (index == 0)
    {
        linked_prepend(list, elem);
    }
    if (index == length)
    {
        linked_append(list, elem);
    }
    while (index > 1)
    {
        curr = curr->next;
        index--;
    }
    struct LinkedList *next = malloc(sizeof(struct LinkedList));
    if (next == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for LinkedList!\n");
        return;
    }
    next->elem = elem;
    next->next = curr->next;
    curr->next = next;
}

void *linked_remove(struct LinkedList **list, int index)
{
    struct LinkedList *curr = *list;
    if (curr == NULL)
    {
        return NULL;
    }
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
    int length = 0;
    while (list != NULL)
    {
        list = list->next;
        length++;
    }
    return length;
}

void linked_foreach(struct LinkedList *list, void (*f)(void *elem))
{
    while (list != NULL)
    {
        (*f)(list->elem);
        list = list->next;
    }
}