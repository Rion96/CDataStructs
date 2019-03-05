# Data Structures in C
Various data structures implemented in C.

* ArrayList
* BinaryHeap
* BinaryTree
* LinkedList
* Matrix

The data structures are implemented to work with void pointers. This way it is possible to use them for different data types. This is of course less than ideal, but making these data structures work with generics was a goal of mine.

Some examples are included as well to show the data structures in action. An implementation of the Floyd-Warshall algorithm to show the Matrix data structure in apsp.c, a DFS to show the ArrayList and LinkedList in dfs.c, and finally a little sorting program to show the BinaryHeap in sort.c. I also included some helper functions (ialloc.c) that should make working with heap allocated integers easier.