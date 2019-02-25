# Data Structures in C
Various data structure implementations in C.

- ArrayList
- LinkedList
- BinaryHeap
- Matrix

The data structures are implemented to work with void pointers. This way it is possible to use them for different data types. This is of course less than ideal, but making these data structures work with "generics" was a goal of mine, and doing this in C didn't give me a lot of other options.

Some examples are included as well to show the data structures in action. An implementation of the Floyd-Warshall algorithm to show the Matrix data structure in apsp.c, a DFS to show the ArrayList and LinkedList in dfs.c, and finally a little sorting program to show the BinaryHeap in sort.c. I also included some helper functions (ialloc.c) that should make working with heap allocated integers easier.