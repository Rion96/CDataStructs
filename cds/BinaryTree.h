#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <stddef.h>

typedef struct BinaryTree
{
    void *elem;
    struct BinaryTree *left;
    struct BinaryTree *right;
    int (*comp)(void *, void *);
} BinaryTree;

/* Constructor for BinaryTree structure,
 * demands element of root node and comparison function.
 */
BinaryTree *tree_init(void *elem, int (*comp)(void *, void *));

/* Destructor for BinaryTree structure.
 * Only destroys the tree, not its elements.
 * Use tree_foreach() with &free to free elements.
 */
void tree_destroy(BinaryTree **tree);

/* Insert element into tree. */
void tree_insert(BinaryTree *tree, void *elem);

/* Return first element from tree that matches
 * comparison function with passed element.
 */
void *tree_get(BinaryTree *tree, void *elem);

/* Remove first element from tree that matches
 * comparison function with passed element.
 */
void tree_remove(BinaryTree **tree, void *elem);

/* Remove and return root element of tree. */
void *tree_poll(BinaryTree **tree);

/* Return root element of tree. */
void *tree_peek(BinaryTree *tree);

/* Returns size of tree. */
size_t tree_size(BinaryTree *tree);

/* Apply function to elements of tree (in-order traversal). */
void tree_foreach(BinaryTree *tree, void (*f)(void *));

#endif /* BINARYTREE_H */