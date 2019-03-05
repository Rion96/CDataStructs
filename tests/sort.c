#include "BinaryHeap.h"
#include "ialloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 16
/* Simple "heapsort" implementation to show BinaryHeap structure. */

BinaryHeap *heap; /* Binary Heap used for sorting. */

int main(int argc, char *argv[])
{
    srand(time(NULL));
    heap = heap_init(N, &icomp);
    printf("Naive heap sort using BinaryHeap's heap_poll():\n");
    for (int i = 0; i < N; i++)
    {
        heap_insert(heap, ialloc(rand()));
    }
    while (heap_size(heap) > 0)
    {
        printf("%d\n", ifree(heap_poll(heap)));
    }
    printf("In place heap sort using BinaryHeap's heap_sort():\n");
    int values[N];
    for (int i = 0; i < N; i++)
    {
        values[i] = rand();
    }
    heap_sort(values, N, sizeof(int), &icomp);
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", values[i]);
    }
    return 0;
}
