#ifndef LINKEDLIST_H
#define LINEKDLIST_H

struct LinkedList {
    void *elem;
    struct LinkedList *next;
};

/**
 * Constructor for LinkedList structure,
 * demands first element of list
 */
struct LinkedList *linked_init(void *first_elem);
/* Destructor for LinkedList structure */
void linked_destroy(struct LinkedList **list);

/* Insert and delete functions */
void linked_append(struct LinkedList *list, void *elem);
void linked_prepend(struct LinkedList **list, void *elem);
void linked_remove(struct LinkedList **list, int index);

#endif /* LINKEDLIST_H */