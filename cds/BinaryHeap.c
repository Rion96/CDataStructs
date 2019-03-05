#include "BinaryHeap.h"
#include <stdio.h>
#include <stdlib.h>
#define MINSIZE 16 /* Minimum size for shrink operations to take place */
#define FACTOR 2   /* Shrink/expand factor */

BinaryHeap *heap_init(size_t size, int (*comp)(void *, void *))
{
    if (size == 0 || comp == NULL)
    {
        return NULL;
    }
    BinaryHeap *heap = malloc(sizeof(BinaryHeap));
    if (heap == NULL)
    {
        fprintf(stderr, "Error: Could not initialize BinaryHeap structure!\n");
        return NULL;
    }
    heap->array = malloc(sizeof(void *) * size);
    if (heap->array == NULL)
    {
        free(heap);
        fprintf(stderr, "Error: Could not initialize BinaryHeap array!\n");
        return NULL;
    }
    heap->init_size = size;
    heap->max_size = size;
    heap->size = 0;
    heap->comp = comp;
    return heap;
}

void heap_destroy(BinaryHeap *heap)
{
    if (heap == NULL)
    {
        return;
    }
    free(heap->array);
    free(heap);
}

static void sift_up(BinaryHeap *heap, int index)
{
    void **h = heap->array;
    while ((index - 1) / 2 >= 0)
    {
        if (heap->comp(h[(index - 1) / 2], h[index]) > 0)
        {
            void *tmp = h[index];
            h[index] = h[(index - 1) / 2];
            h[(index - 1) / 2] = tmp;
            index = (index - 1) / 2;
        }
        else
        {
            break;
        }
    }
}

static void sift_down(BinaryHeap *heap, int index)
{
    void **h = heap->array;
    while (index * 2 + 1 < heap->size)
    {
        int child = index * 2 + 1;
        if (index * 2 + 2 < heap->size)
        {
            if (heap->comp(h[child], h[index * 2 + 2]) > 0)
            {
                child = index * 2 + 2;
            }
        }
        if (heap->comp(h[index], h[child]) > 0)
        {
            void *tmp = h[child];
            h[child] = h[index];
            h[index] = tmp;
            index = child;
        }
        else
        {
            break;
        }
    }
}

static void heap_grow(BinaryHeap *heap)
{
    if (heap == NULL)
    {
        return;
    }
    void **array = realloc(heap->array, sizeof(void *) * heap->max_size * FACTOR);
    if (array == NULL)
    {
        fprintf(stderr, "Error: Could not expand BinaryHeap!\n");
        return;
    }
    heap->array = array;
    heap->max_size *= FACTOR;
}

static void heap_shrink(BinaryHeap *heap)
{
    if (heap == NULL)
    {
        return;
    }
    if (heap->max_size < MINSIZE || heap->max_size == heap->init_size 
        || heap->size * FACTOR > heap->max_size)
    {
        return;
    }
    void **array = realloc(heap->array, sizeof(void *) * heap->max_size / FACTOR);
    if (array == NULL)
    {
        fprintf(stderr, "Error: Could not shrink Arrayheap!\n");
        return;
    }
    heap->array = array;
    heap->max_size /= FACTOR;
}

void heap_insert(BinaryHeap *heap, void *elem)
{
    if (heap == NULL || elem == NULL)
    {
        return;
    }
    if (heap->size == heap->max_size)
    {
        heap_grow(heap);
    }
    if (heap->size == heap->max_size)
    {
        return;
    }
    heap->array[heap->size] = elem;
    sift_up(heap, heap->size);
    heap->size++;
}

void *heap_peek(BinaryHeap *heap)
{
    if (heap == NULL)
    {
        return NULL;
    }
    if (heap->size > 0)
    {
        return heap->array[0];
    }
    else
    {
        return NULL;
    }
}

void *heap_poll(BinaryHeap *heap)
{
    if (heap == NULL)
    {
        return NULL;
    }
    if (heap->size == 0)
    {
        return NULL;
    }
    void **h = heap->array;
    void *elem = h[0];
    heap->size--;
    h[0] = h[heap->size];
    sift_down(heap, 0);
    if (heap->max_size > MINSIZE && heap->max_size > heap->init_size
        && heap->max_size > heap->size * FACTOR)
    {
        heap_shrink(heap);
    }
    return elem;
}

size_t heap_size(BinaryHeap *heap)
{
    if (heap == NULL)
    {
        return 0;
    }
    return heap->size;
}

void heap_foreach(BinaryHeap *heap, void (*f)(void *elem))
{
    if (heap == NULL || f == NULL)
    {
        return;
    }
    for (int i = 0; i < heap->size; i++)
    {
        (*f)(heap->array[i]);
    }
}