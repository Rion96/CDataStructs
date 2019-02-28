CC=gcc
CDSDIR=./cds/
TESTSDIR=./tests/
CFLAGS= -Wall -g -I$(CDSDIR) -I$(TESTSDIR)
ARRAYLIST=$(addprefix $(CDSDIR), ArrayList.h ArrayList.c)
BINARYHEAP=$(addprefix $(CDSDIR), BinaryHeap.h BinaryHeap.c heap_sort.c)
LINKEDLIST=$(addprefix $(CDSDIR), LinkedList.h LinkedList.c)
MATRIX=$(addprefix $(CDSDIR), Matrix.h Matrix.c)
IALLOC=$(addprefix $(TESTSDIR), ialloc.h ialloc.c)
OBJECTS=ArrayList.o BinaryHeap.o LinkedList.o Matrix.o ialloc.o heap_sort.o

.PHONY: all library
all: apsp dfs sort

library: $(OBJECTS)
	ar -rcs libcds.a $(OBJECTS)

apsp: $(OBJECTS) $(TESTSDIR)apsp.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)apsp.c -o $@

dfs: $(OBJECTS) $(TESTSDIR)dfs.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)dfs.c -o $@

sort: $(OBJECTS) $(TESTSDIR)sort.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)sort.c -o $@

ialloc.o: $(IALLOC)
	$(CC) $(CFLAGS) $(TESTSDIR)ialloc.c -c -o $@

Matrix.o: $(MATRIX)
	$(CC) $(CFLAGS) $(CDSDIR)Matrix.c -c -o $@

LinkedList.o: $(LINKEDLIST)
	$(CC) $(CFLAGS) $(CDSDIR)LinkedList.c -c -o $@

BinaryHeap.o heap_sort.o: $(BINARYHEAP)
	$(CC) $(CFLAGS) $(CDSDIR)BinaryHeap.c $(CDSDIR)heap_sort.c -c

ArrayList.o: $(ARRAYLIST)
	$(CC) $(CFLAGS) $(CDSDIR)ArrayList.c -c -o $@