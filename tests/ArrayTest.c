#include "ArrayList.h"
#include "ialloc.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct ArrayList *list = array_init(16);
    for (int i = 16; i <= 32; i++)
    {
        array_append(list, ialloc(i));
    }
    for (int i = 15; i >= 0; i--)
    {
        int *x = malloc(sizeof(int));
        *x = i;
        array_prepend(list, x);
    }
    //array_foreach(list, &print_int);
    for (int i = 0; i < 16; i++)
    {
        array_poll(list);
    }
    array_replace(list, ialloc(10000), 16);
    array_foreach(list, &iprint);
    array_foreach(list, &free);
    array_destroy(list);
    return 0;
}
