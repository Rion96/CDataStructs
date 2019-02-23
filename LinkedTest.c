#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(void *e)
{
    int *i = (int *)e;
    printf("%d\n", (*i));
}

void dec(void *e)
{
    int *i = (int *)e;
    (*i)--;
}

int main(int argc, char *argv[])
{
    struct LinkedList *list = linked_init("B");
    linked_append(&list, "C");
    linked_prepend(&list, "A");
    linked_prepend(&list, "9");
    while (linked_length(list) > 0)
    {
        printf("%s\n", (char *)linked_poll(&list));
    }

    for (int i = 1; i <= 8; i++)
    {
        int *value = malloc(sizeof(int));
        *value = i;
        linked_append(&list, value);
    }
    int x = 5;
    linked_add(&list, &x, 7);

    printf("List contents:\n");
    linked_foreach(list, &print_int);

    printf("Decremented by one:\n");
    linked_foreach(list, &dec);
    linked_foreach(list, &print_int);

    linked_foreach(list, &free);
    linked_destroy(&list);
    return 0;
}
