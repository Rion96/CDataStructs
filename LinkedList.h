#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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

/* Insert element to beginning of list (make new head of list). */
void linked_prepend(struct LinkedList **list, void *elem);

/* Remove and return first element of list. */
void *linked_poll(struct LinkedList **list);

/* Remove and return n'th element of list. */
void *linked_remove(struct LinkedList **list, int index);

/* Return n'th element of list. */
void *linked_get(struct LinkedList *list, int index);

/* Return first element of list. */
void *linked_peek(struct LinkedList *list);

/* Returns length of list. */
int linked_length(struct LinkedList *list);

/* Apply function to elements of list. */
void linked_foreach(struct LinkedList *list, void (*f)(void *elem));

#endif /* LINKEDLIST_H */