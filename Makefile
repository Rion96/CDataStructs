CC=gcc
CFLAGS= -Wall -g
ARRAYLIST=./ArrayList.h ./ArrayList.c
BINARYHEAP=./BinaryHeap.h ./BinaryHeap.c
LINKEDLIST=./LinkedList.h ./LinkedList.c
MATRIX=./Matrix.h ./Matrix.c
IALLOC=./ialloc.h ./ialloc.c

.PHONY: all
all: apsp dfs sort

apsp: $(MATRIX) $(IALLOC) ./apsp.c
	$(CC) $(CFLAGS) ./Matrix.c ./ialloc.c ./apsp.c -o $@

dfs: $(LINKEDLIST) $(ARRAYLIST) $(IALLOC) ./dfs.c
	$(CC) $(CFLAGS) ./LinkedList.c ./ArrayList.c ./ialloc.c ./dfs.c -o $@

sort: $(BINARYHEAP) $(IALLOC) ./sort.c
	$(CC) $(CFLAGS) ./BinaryHeap.c ./ialloc.c ./sort.c -o $@