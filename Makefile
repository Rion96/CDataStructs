CC=gcc
CDSDIR=./cds/
TESTSDIR=./tests/
CFLAGS= -Wall -g -I$(CDSDIR) -I$(TESTSDIR)
ARRAYLIST=$(addprefix $(CDSDIR), ArrayList.h ArrayList.c)
BIGINTEGER=$(addprefix $(CDSDIR), BigInteger.h BigInteger.c)
BINARYHEAP=$(addprefix $(CDSDIR), BinaryHeap.h BinaryHeap.c heap_sort.c)
BINARYTREE=$(addprefix $(CDSDIR), BinaryTree.h BinaryTree.c)
LINKEDLIST=$(addprefix $(CDSDIR), LinkedList.h LinkedList.c)
MATRIX=$(addprefix $(CDSDIR), Matrix.h Matrix.c)
IALLOC=$(addprefix $(TESTSDIR), ialloc.h ialloc.c)
OBJECTS=ArrayList.o BinaryHeap.o LinkedList.o Matrix.o ialloc.o heap_sort.o BinaryTree.o BigInteger.o

.PHONY: all library
all: apsp dfs sort tree

library: $(OBJECTS)
	ar -rcs libcds.a $(OBJECTS)

apsp: $(OBJECTS) $(TESTSDIR)apsp.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)apsp.c -o $@

bigints: $(OBJECTS) $(TESTSDIR)bigints.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)bigints.c -o $@

dfs: $(OBJECTS) $(TESTSDIR)dfs.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)dfs.c -o $@

sort: $(OBJECTS) $(TESTSDIR)sort.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)sort.c -o $@

tree: $(OBJECTS) $(TESTSDIR)tree.c
	$(CC) $(CFLAGS) $(OBJECTS) $(TESTSDIR)tree.c -o $@

ialloc.o: $(IALLOC)
	$(CC) $(CFLAGS) $(TESTSDIR)ialloc.c -c -o $@

Matrix.o: $(MATRIX)
	$(CC) $(CFLAGS) $(CDSDIR)Matrix.c -c -o $@

LinkedList.o: $(LINKEDLIST)
	$(CC) $(CFLAGS) $(CDSDIR)LinkedList.c -c -o $@

BinaryTree.o: $(BINARYTREE)
	$(CC) $(CFLAGS) $(CDSDIR)BinaryTree.c -c -o $@

BinaryHeap.o heap_sort.o: $(BINARYHEAP)
	$(CC) $(CFLAGS) $(CDSDIR)BinaryHeap.c $(CDSDIR)heap_sort.c -c

BigInteger.o: $(BIGINTEGER)
	$(CC) $(CFLAGS) $(CDSDIR)BigInteger.c -c -o $@

ArrayList.o: $(ARRAYLIST)
	$(CC) $(CFLAGS) $(CDSDIR)ArrayList.c -c -o $@