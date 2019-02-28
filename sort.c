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
    for (int i = 0; i < N; i++)
    {
        heap_insert(heap, ialloc(rand()));
    }
    while (heap_size(heap) > 0)
    {
        printf("%d\n", ifree(heap_poll(heap)));
    }
    return 0;
}
