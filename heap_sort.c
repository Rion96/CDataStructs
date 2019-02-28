#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* in-place heap sort */

static void sift_down(void *array, size_t nmemb, size_t size,
                        int (*comp)(void *, void *), int index)
{
    void *tmp = malloc(size);
    if (tmp == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for heap_sort sift_down operation!\n");
        return;
    }
    while (index * 2 + 1 < nmemb)
    {
        int child_index = index * 2 + 1;
        size_t parent_offset = size * index;
        size_t child_offset = size * child_index;
        void *parent = (array + parent_offset);
        void *child = (array + child_offset);
        if (child_index + 1 < nmemb)
        {
            void *right_child = (array + child_offset + size);
            if (comp(child, right_child) < 0)
            {
                child = right_child;
                child_index++;
            }
        }
        if (comp(parent, child) < 0)
        {
            memcpy(tmp, child, size);
            memcpy(child, parent, size);
            memcpy(parent, tmp, size);
            index = child_index;
        }
        else
        {
            break;
        }
    }
    free(tmp);
}

void heap_sort(void *array, size_t nmemb, size_t size, int (*comp)(void *,void *))
{
    void *tmp = malloc(size);
    if (tmp == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for heap_sort operation!\n");
        return;
    }
    /* Initialize as heap */
    for (int t = nmemb / 2 - 1; t >= 0; t--)
    {
        sift_down(array, nmemb, size, comp, t);
    }
    /* Poll until heap is empty */
    while (nmemb > 0)
    {
        tmp = memcpy(tmp, array, size);
        nmemb--;
        size_t last_elem_offset = size * nmemb;
        void *last_elem = (array + last_elem_offset);
        memcpy(array, last_elem, size);
        memcpy(last_elem, tmp, size);
        sift_down(array, nmemb, size, comp, 0);
    }
}