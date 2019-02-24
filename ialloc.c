#include "ialloc.h"
#include <stdlib.h>
#include <stdio.h>

int *ialloc(int val)
{
    int *i = malloc(sizeof(int));
    if (i == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for integer!");
        return NULL;
    }
    *i = val;
    return i;
}

int iget(void *ptr)
{
    if (ptr == NULL)
    {
        return 0;
    }
    int *i = (int *)ptr;
    return (*i);
}

int ifree(void *ptr)
{
    if (ptr == NULL)
    {
        return 0;
    }
    int *i = (int *)ptr;
    int val = (*i);
    free(i);
    return val;
}

void iprint(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    int *i = (int *)ptr;
    printf("%d\n", (*i));
}