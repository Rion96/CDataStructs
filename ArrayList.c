#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>
#define MINSIZE 16 /* Minimum size for shrink operations to take place */
#define FACTOR 2   /* Shrink/expand factor */

struct ArrayList *array_init(size_t size)
{
    if (size <= 0)
    {
        return NULL;
    }
    struct ArrayList *list = malloc(sizeof(struct ArrayList));
    if (list == NULL)
    {
        fprintf(stderr, "Error: Could not initialize ArrayList struct!\n");
        return NULL;
    }
    list->array = malloc(sizeof(void *) * size);
    if (list->array == NULL)
    {
        fprintf(stderr, "Error: Could not create ArrayList!\n");
        return NULL;
    }
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

static void array_grow(struct ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    void **array = malloc(sizeof(void *) * list->max_size * FACTOR);
    if (array == NULL)
    {
        fprintf(stderr, "Error: Could not expand ArrayList!\n");
        return;
    }
    for (int i = 0; i < list->size; i++)
    {
        array[i] = list->array[i];
    }
    free(list->array);
    list->array = array;
    list->max_size *= FACTOR;
}

static void array_shrink(struct ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    if (list->size * 2 > list->max_size)
    {
        return;
    }
    void **array = malloc(sizeof(void *) * list->max_size / FACTOR);
    if (array == NULL)
    {
        fprintf(stderr, "Error: Could not shrink ArrayList!\n");
        return;
    }
    for (int i = 0; i < list->size; i++)
    {
        array[i] = list->array[i];
    }
    free(list->array);
    list->array = array;
    list->max_size /= FACTOR;
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
    if (list->size == list->max_size)
    {
        return;
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
    if (index == list->size)
    {
        array_append(list, elem);
    }
    if (list->size == list->max_size)
    {
        array_grow(list);
    }
    if (list->size == list->max_size)
    {
        return;
    }
    for (int i = list->size; i > index; i--)
    {
        list->array[i] = list->array[i - 1];
    }
    list->array[index] = elem;
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