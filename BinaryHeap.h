#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <stddef.h>

struct BinaryHeap
{
    size_t init_size;
    size_t max_size;
    size_t size;
    void **array;
    int (*comp)(void *, void *);
};

/* Constructor for BinaryHeap structure,
 * demands initial size of heap.
 */
struct BinaryHeap *heap_init(size_t size, int (*comp)(void *, void *));

/* Destructor for BinaryHeap structure.
 * Only destroys the heap, not its elements.
 * Use heap_foreach() with &free to free elements.
 */
void heap_destroy(struct BinaryHeap *heap);

/* Insert element into heap. */
void heap_insert(struct BinaryHeap *heap, void *elem);

/* Return first element of heap. */
void *heap_peek(struct BinaryHeap *heap);

/* Remove and return first element of heap. */
void *heap_poll(struct BinaryHeap *heap);

/* Returns size of heap. */
size_t heap_size(struct BinaryHeap *heap);

/* Apply function to elements of heap. */
void heap_foreach(struct BinaryHeap *heap, void (*f)(void *));

#endif /* BINARYHEAP_H */