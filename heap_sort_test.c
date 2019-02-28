#include "ialloc.h"
#include "BinaryHeap.h"
#include <stdio.h>

int main(void)
{
    int test[] = {5, 4, 3, 2, 1, 0, 9};
    heap_sort(test, 7, sizeof(int), &icomp);
    for (int i = 0; i < 7; i++)
    {
        printf("%d\n", test[i]);
    }
}