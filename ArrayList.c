#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>
#define MINSIZE 16 /* Minimum size for shrink operations to take place */
#define FACTOR 2   /* Shrink/expand factor */

ArrayList *array_init(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }
    ArrayList *list = malloc(sizeof(ArrayList));
    if (list == NULL)
    {
        fprintf(stderr, "Error: Could not initialize ArrayList struct!\n");
        return NULL;
    }
    list->array = malloc(sizeof(void *) * size);
    if (list->array == NULL)
    {
        free(list);
        fprintf(stderr, "Error: Could not create ArrayList!\n");
        return NULL;
    }
    list->init_size = size;
    list->max_size = size;
    list->size = 0;
    return list;
}

void array_destroy(ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    free(list->array);
    free(list);
}

static void array_grow(ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    void **array = realloc(list->array, sizeof(void *) * list->max_size * FACTOR);
    if (array == NULL)
    {
        fprintf(stderr, "Error: Could not expand ArrayList!\n");
        return;
    }
    list->array = array;
    list->max_size *= FACTOR;
}

static void array_shrink(ArrayList *list)
{
    if (list == NULL)
    {
        return;
    }
    if (list->max_size < MINSIZE || list->max_size == list->init_size 
        || list->size * FACTOR > list->max_size)
    {
        return;
    }
    void **array = realloc(list->array, sizeof(void *) * list->max_size / FACTOR);
    if (array == NULL)
    {
        fprintf(stderr, "Error: Could not shrink ArrayList!\n");
        return;
    }
    list->array = array;
    list->max_size /= FACTOR;
}

void array_append(ArrayList *list, void *elem)
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

void array_prepend(ArrayList *list, void *elem)
{
    array_add(list, elem, 0);
}

void *array_poll(ArrayList *list)
{
    return array_remove(list, 0);
}

void *array_remove(ArrayList *list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index >= list->size)
    {
        return NULL;
    }
    void *elem = list->array[index];
    for (int i = index; i < list->size - 1; i++)
    {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
    if (list->max_size > MINSIZE && list->max_size > list->init_size
        && list->max_size > list->size * FACTOR)
    {
        array_shrink(list);
    }
    return elem;
}

void array_add(ArrayList *list, void *elem, size_t index)
{
    if (list == NULL)
    {
        return;
    }
    if (index > list->size)
    {
        return;
    }
    if (index == list->size)
    {
        array_append(list, elem);
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
    for (int i = list->size; i > index; i--)
    {
        list->array[i] = list->array[i - 1];
    }
    list->array[index] = elem;
    list->size++;
}

void array_put(ArrayList *list, void *elem, size_t index)
{
    if (list == NULL)
    {
        return;
    }
    if (index >= list->size)
    {
        return;
    }
    list->array[index] = elem;
}

void array_free(ArrayList *list, size_t index)
{
    if (list == NULL)
    {
        return;
    }
    if (index >= list->size)
    {
        return;
    }
    free(list->array[index]);
}

void array_replace(ArrayList *list, void *elem, size_t index)
{
    array_free(list, index);
    array_put(list, elem, index);
}

void *array_get(ArrayList *list, size_t index)
{
    if (list == NULL)
    {
        return NULL;
    }
    if (index >= list->size)
    {
        return NULL;
    }
    return list->array[index];
}

void *array_peek(ArrayList *list)
{
    return array_get(list, 0);
}

size_t array_length(ArrayList *list)
{
    if (list == NULL)
    {
        return 0;
    }
    return list->size;
}

void array_foreach(ArrayList *list, void (*f)(void *e))
{
    if (list == NULL || f == NULL)
    {
        return;
    }
    for (int i = 0; i < list->size; i++)
    {
        (*f)(list->array[i]);
    }
}