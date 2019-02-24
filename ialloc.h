#ifndef IALLOC_H
#define IALLOC_H
/* Helper functions for heap allocating integers */

int *ialloc(int val);
int iget(void *ptr);
int ifree(void *ptr);
void iprint(void *ptr);
int icomp(void *ptr1, void *ptr2);

#endif /* IALLOC_H */