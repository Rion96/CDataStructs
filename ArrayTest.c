#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(void *e)
{
    int *i = (int *)e;
    printf("%d\n", (*i));
}

int main(int argc, char *argv[])
{
    struct ArrayList *list = array_init(16);
    for (int i = 16; i <= 32; i++)
    {
        int *x = malloc(sizeof(int));
        *x = i;
        array_append(list, x);
    }
    for (int i = 15; i >= 0; i--)
    {
        int *x = malloc(sizeof(int));
        *x = i;
        array_prepend(list, x);
    }
    //array_foreach(list, &print_int);
    for (int i = 0; i < 24; i++)
    {
        array_poll(list);
    }
    array_foreach(list, &print_int);
    array_foreach(list, &free);
    array_destroy(list);
    return 0;
}
