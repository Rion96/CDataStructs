#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <stddef.h>

typedef struct BinaryHeap
{
    size_t init_size; /* Initial size of heap. Heap will not shrink below this size. */
    size_t max_size;  /* Current maximum size of heap. Heap will need to expand if reached. */
    size_t size;      /* Current size of heap */
    void **array;
    int (*comp)(void *, void *); /* Compare function */
} BinaryHeap;

/* Constructor for BinaryHeap structure,
 * demands initial size of heap and compare function.
 */
BinaryHeap *heap_init(size_t size, int (*comp)(void *, void *));

/* Destructor for BinaryHeap structure.
 * Only destroys the heap, not its elements.
 * Use heap_foreach() with &free to free elements.
 */
void heap_destroy(BinaryHeap *heap);

/* Insert element into heap. */
void heap_insert(BinaryHeap *heap, void *elem);

/* Return first element of heap. */
void *heap_peek(BinaryHeap *heap);

/* Remove and return first element of heap. */
void *heap_poll(BinaryHeap *heap);

/* Returns size of heap. */
size_t heap_size(BinaryHeap *heap);

/* Apply function to elements of heap. */
void heap_foreach(BinaryHeap *heap, void (*f)(void *));

/* In-place heap sort. */
void heap_sort(void *array, size_t nmemb, size_t size, int (*comp)(void *, void *));

#endif /* BINARYHEAP_H */