#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ArrayList.h"
#include "LinkedList.h"
#include "ialloc.h"
#define N 16
/* Simple DFS graph traversal to show ArrayList and LinkedList in action */
typedef struct LinkedList LinkedList;
typedef struct ArrayList ArrayList;

ArrayList **adj;   /* Adjacency lists */
LinkedList *stack; /* Stack for DFS */

void dfs(int start)
{
    bool *visited = calloc(N, sizeof(bool));
    stack = linked_init(ialloc(start));
    while (linked_length(stack) > 0)
    {
        int node = ifree(linked_poll(&stack));
        visited[node] = true;
        printf("%d\n", node);
        for (int i = 0; i < array_length(adj[node]); i++)
        {
            int neighbor = iget(array_get(adj[node], i));
            if (!visited[neighbor])
            {
                linked_prepend(&stack, ialloc(neighbor));
            }
        }
    }
    free(visited);
    linked_destroy(&stack);
}

void addEdge(int from, int to)
{
    array_append(adj[from], ialloc(to));
}

int main(int argc, char const *argv[])
{
    adj = malloc(sizeof(ArrayList) * N);
    for (int i = 0; i < N; i++)
    {
        adj[i] = array_init(8);
    }
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 4);
    addEdge(4, 6);
    addEdge(4, 5);
    addEdge(3, 7);
    addEdge(1, 3);
    addEdge(3, 8);
    addEdge(8, 9);
    addEdge(9, 10);
    addEdge(10, 11);
    addEdge(11, 12);
    addEdge(0, 13);
    addEdge(13, 14);
    addEdge(14, 15);
    dfs(0);
    return 0;
}
