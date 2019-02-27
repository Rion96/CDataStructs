#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stddef.h>

struct ArrayList
{
    size_t init_size;   /* Initial size of array. Array will not shrink below this size. */
    size_t max_size;    /* Current maximum size of array. Array will need to expand if reached. */
    size_t size;        /* Current size of array. */
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

/* Insert element to end of list. */
void array_append(struct ArrayList *list, void *elem);

/* Insert element to beginning of list. */
void array_prepend(struct ArrayList *list, void *elem);

/* Remove and return first element of list. */
void *array_poll(struct ArrayList *list);

/* Remove and return n'th element of list. */
void *array_remove(struct ArrayList *list, size_t index);

/* Add element to n'th index of list. */
void array_add(struct ArrayList *list, void *elem, size_t index);

/* Put element in n'th index of list. */
void array_put(struct ArrayList *list, void *elem, size_t index);

/* Frees element in n'th index of list. */
void array_free(struct ArrayList *list, size_t index);

/* Replaces element in n'th index of list.
 * Frees previous element.
 */
void array_replace(struct ArrayList *list, void *elem, size_t index);

/* Return n'th element of list. */
void *array_get(struct ArrayList *list, size_t index);

/* Return first element of list. */
void *array_peek(struct ArrayList *list);

/* Returns length of list. */
size_t array_length(struct ArrayList *list);

/* Apply function to elements of list. */
void array_foreach(struct ArrayList *list, void (*f)(void *elem));

#endif /* ARRAYLIST_H */