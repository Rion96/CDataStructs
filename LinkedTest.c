#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf("%d\n", *((int *)linked_get(list, 8)));
    while (linked_length(list) > 0)
    {
        printf("%d\n", *((int *)linked_poll(&list)));
    }
    return 0;
}
