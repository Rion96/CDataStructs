#ifndef IALLOC_H
#define IALLOC_H
/* Helper functions for heap allocating integers */

int *ialloc(int val);
int iget(void *ptr);
int ifree(void *ptr);
void iprint(void *ptr);

#endif /* IALLOC_H */