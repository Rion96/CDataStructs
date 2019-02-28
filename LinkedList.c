#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

LinkedList *linked_init(void *first_elem)
{
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        fprintf(stderr, "Error: Could not initialize LinkedList struct!\n");
        return NULL;
    }
    list->elem = first_elem;
    list->next = NULL;
    return list;
}

void linked_destroy(LinkedList **list)
{
    LinkedList *curr = *list;
    LinkedList *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *list = NULL;
}

void linked_append(LinkedList **list, void *elem)
{
    LinkedList *curr = *list;
    if (curr == NULL)
    {
        *list = linked_init(elem);
        return;
    }
    LinkedList *node = malloc(sizeof(LinkedList));
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

void linked_prepend(LinkedList **list, void *elem)
{
    LinkedList *node = malloc(sizeof(LinkedList));
    if (node == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for LinkedList!\n");
        return;
    }
    node->elem = elem;
    node->next = (*list);
    *list = node;
}

void *linked_poll(LinkedList **list)
{
    if (list == NULL)
    {
        return NULL;
    }
    LinkedList *curr = *list;
    LinkedList *next = curr->next;
    void *elem = curr->elem;
    free(curr);
    *list = next;
    return elem;
}

void *linked_peek(LinkedList *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->elem;
}

void *linked_get(LinkedList *list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }
    while (index > 0 && list != NULL)
    {
        list = list->next;
        index--;
    }
    if (index > 0 || list == NULL)
    {
        return NULL;
    }
    return list->elem;
}

void linked_add(LinkedList **list, void *elem, size_t index)
{
    LinkedList *curr = *list;
    if (index == 0)
    {
        linked_prepend(list, elem);
    }
    while (curr != NULL && index > 1)
    {
        curr = curr->next;
        index--;
    }
    if (index > 1 || curr == NULL)
    {
        return;
    }
    LinkedList *next = malloc(sizeof(LinkedList));
    if (next == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for LinkedList!\n");
        return;
    }
    next->elem = elem;
    next->next = curr->next;
    curr->next = next;
}

void linked_put(LinkedList *list, void *elem, size_t index)
{
    while (list != NULL && index > 0)
    {
        list = list->next;
        index--;
    }
    if (index > 0 || list == NULL)
    {
        return;
    }
    list->elem = elem;
}

void linked_free(LinkedList *list, size_t index)
{
    while (list != NULL && index > 0)
    {
        list = list->next;
        index--;
    }
    if (index > 0 || list == NULL)
    {
        return;
    }
    free(list->elem);
}

void linked_replace(LinkedList *list, void *elem, size_t index)
{
    linked_free(list, index);
    linked_put(list, elem, index);
}

void *linked_remove(LinkedList **list, size_t index)
{
    LinkedList *curr = *list;
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
    LinkedList *next = curr->next->next;
    free(curr->next);
    curr->next = next;
    return elem;
}

size_t linked_length(LinkedList *list)
{
    size_t length = 0;
    while (list != NULL)
    {
        list = list->next;
        length++;
    }
    return length;
}

void linked_foreach(LinkedList *list, void (*f)(void *elem))
{
    if (list == NULL || f == NULL)
    {
        return;
    }
    while (list != NULL)
    {
        (*f)(list->elem);
        list = list->next;
    }
}