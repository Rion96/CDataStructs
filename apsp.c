#include "Matrix.h"
#include "ialloc.h"
#include <stdio.h>
#include <stdlib.h>
#define N 4
/* Simple Floyd Warshall implementation to show Matrix structure */

Matrix *dist; /* Distance Matrix */

void floyd_warshall()
{
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int new_dist = iget(matrix_get(dist, i, k)) + iget(matrix_get(dist, k, j));
                if (new_dist < iget(matrix_get(dist, i, j)))
                {
                    matrix_replace(dist, i, j, ialloc(new_dist));
                }
            }
        }
    }
}

void addEdge(int from, int to, int cost)
{
    matrix_replace(dist, from, to, ialloc(cost));
}

void setup()
{
    dist = matrix_init(N, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                matrix_put(dist, i, j, ialloc(0));
            }
            else
            {
                matrix_put(dist, i, j, ialloc(10000));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    setup();
    addEdge(0, 1, 5);
    addEdge(0, 2, 1);
    addEdge(2, 3, 1);
    addEdge(3, 1, 1);
    printf("Current distance between 0 and 1: %d\n", iget(matrix_get(dist, 0, 1)));
    floyd_warshall();
    printf("New distance between 0 and 1: %d\n", iget(matrix_get(dist, 0, 1)));
    return 0;
}
