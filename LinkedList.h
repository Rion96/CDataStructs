#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>

struct LinkedList
{
    void *elem;
    struct LinkedList *next;
};

/* Constructor for LinkedList structure,
 * demands first element of list.
 */
struct LinkedList *linked_init(void *first_elem);

/* Destructor for LinkedList structure.
 * Only destroys the list, not its elements.
 * Use linked_foreach() with &free to free elements.
 */
void linked_destroy(struct LinkedList **list);

/* Insert element to end of list. 
 * Initializes list if empty.
 */
void linked_append(struct LinkedList **list, void *elem);

/* Insert element to beginning of list. */
void linked_prepend(struct LinkedList **list, void *elem);

/* Remove and return first element of list. */
void *linked_poll(struct LinkedList **list);

/* Remove and return n'th element of list. */
void *linked_remove(struct LinkedList **list, size_t index);

/* Add element to n'th index of list. */
void linked_add(struct LinkedList **list, void *elem, size_t index);

/* Put element in n'th index of list. */
void linked_put(struct LinkedList *list, void *elem, size_t index);

/* Frees element in n'th index of list. */
void linked_free(struct LinkedList *list, size_t index);

/* Replaces element in n'th index of list.
 * Frees previous element.
 */
void linked_replace(struct LinkedList *list, void *elem, size_t index);

/* Return n'th element of list. */
void *linked_get(struct LinkedList *list, size_t index);

/* Return first element of list. */
void *linked_peek(struct LinkedList *list);

/* Returns length of list. */
size_t linked_length(struct LinkedList *list);

/* Apply function to elements of list. */
void linked_foreach(struct LinkedList *list, void (*f)(void *elem));

#endif /* LINKEDLIST_H */