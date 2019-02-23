#include "ArrayList.h"
#include <stdlib.h>
#include <string.h>
#define MINSIZE 16

struct ArrayList *array_init(size_t size)
{
    if (size <= 0)
    {
        return NULL;
    }
    struct ArrayList *list = malloc(sizeof(struct ArrayList));
    list->array = malloc(sizeof(void *) * size);
    list->max_size = size;
    list->size = 0;
    return list;    
}

void array_destroy(struct ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    free(list->array);
    free(list);
}

void array_grow(struct ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    void **array = malloc(sizeof(void *) * list->max_size * 2);
    memcpy(array, list->array, sizeof(void *) * list->max_size);
    list->array = array;
    list->max_size *= 2;
}

void array_shrink(struct ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    void **array = malloc(sizeof(void *) * list->max_size / 2);
    memcpy(array, list->array, sizeof(void *) * list->max_size / 2);
    list->array = array;
    list->max_size /= 2;
}

void array_append(struct ArrayList *list, void *elem)
{
    if (list == NULL)
    {
        return;
    }
    if (list->size == list->max_size)
    {
        array_grow(list);
    }
    list->array[list->size] = elem;
    list->size++;
}

void array_prepend(struct ArrayList *list, void *elem)
{
    array_add(list, elem, 0);
}

void *array_poll(struct ArrayList *list)
{
    return array_remove(list, 0);
}

void *array_remove(struct ArrayList *list, int index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index < 0 || index >= list->max_size)
    {
        return NULL;
    }
    void *elem = list->array[index];
    for (int i = index; i < list->size; i++)
    {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
    if (list->max_size > MINSIZE && list->max_size > list->size * 2)
    {
        array_shrink(list);
    }
    return elem;
}

void array_add(struct ArrayList *list, void *elem, int index)
{
    if (list == NULL)
    {
        return;
    }
    if (index < 0 || index > list->size)
    {
        return;
    }
    if (list->size == list->max_size)
    {
        array_grow(list);
    }
    for (int i = index; i < list->size; i++)
    {
        list->array[i + 1] = list->array[i];
    }
    list->size++;
}

void *array_get(struct ArrayList *list, int index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index < 0 || index > list->size)
    {
        return NULL;
    }
    return list->array[index];
}

void *array_peek(struct ArrayList *list)
{
    return array_get(list, 0);
}

size_t array_length(struct ArrayList *list)
{
    if (list == NULL)
    {
        return 0;
    }
    return list->size;
}

void array_foreach(struct ArrayList *list, void (*f)(void *e))
{
    if (list == NULL)
    {
        return;
    }
    for (int i = 0; i < list->size; i++)
    {
        (*f)(list->array[i]);
    }
}