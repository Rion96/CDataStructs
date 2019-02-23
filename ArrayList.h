#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stddef.h>

struct ArrayList
{
    size_t max_size;
    size_t size;
    void **array;
};

/* Constructor for ArrayList structure,
 * demands initial size of array.
 */
struct ArrayList *array_init(size_t size);

/* Destructor for ArrayList structure.
 * Only destroys the list, not its elements.
 * Use array_foreach() with &free to free elements.
 */
void array_destroy(struct ArrayList *list);

/* Helper function for expanding array size */
void array_grow(struct ArrayList *list);

/* Helper function for shrinking array size */
void array_shrink(struct ArrayList *list);

/* Insert element to end of list. */
void array_append(struct ArrayList *list, void *elem);

/* Insert element to beginning of list. */
void array_prepend(struct ArrayList *list, void *elem);

/* Remove and return first element of list. */
void *array_poll(struct ArrayList *list);

/* Remove and return n'th element of list. */
void *array_remove(struct ArrayList *list, int index);

/* Add element to n'th index of list. */
void array_add(struct ArrayList *list, void *elem, int index);

/* Return n'th element of list. */
void *array_get(struct ArrayList *list, int index);

/* Return first element of list. */
void *array_peek(struct ArrayList *list);

/* Returns length of list. */
size_t array_length(struct ArrayList *list);

/* Apply function to elements of list. */
void array_foreach(struct ArrayList *list, void (*f)(void *elem));

#endif /* ARRAYLIST_H */