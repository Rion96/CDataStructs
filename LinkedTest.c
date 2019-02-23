#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(void *e)
{
    int *i = (int *)e;
    printf("%d\n", (*i));
}

int main(int argc, char const *argv[])
{
    struct LinkedList *list = linked_init("B");
    linked_append(&list, "C");
    linked_prepend(&list, "A");
    while (linked_length(list) > 0)
    {
        printf("%s\n", (char *)linked_poll(&list));
    }
    for (int i = 1; i <= 100; i++)
    {
        int *value = malloc(sizeof(int));
        *value = i;
        linked_append(&list, value);
    }
    linked_foreach(list, &print_int);
    linked_foreach(list, &free);
    linked_destroy(&list);
    return 0;
}
