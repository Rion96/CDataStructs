#include "ialloc.h"
#include "BinaryTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 8

/* Testing Binary Tree. */

int main(void)
{
    srand(time(NULL));
    BinaryTree *tree = tree_init(ialloc(rand()), icomp);
    for (int i = 0; i < N - 1; i++)
    {
        tree_insert(tree, ialloc(rand()));
    }
    printf("Size: %d\n", tree_size(tree));
    for (int i = 0; i < N; i++)
    {
        tree_insert(tree, ialloc(rand()));
    }
    printf("New size: %d\n", tree_size(tree));
    printf("All Elements:\n");
    tree_foreach(tree, iprint);
    printf("Polling elements:\n");
    while (tree_size(tree) > 0)
    {
        printf("%d\n", ifree(tree_poll(&tree)));
    }
}