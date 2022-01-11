CC = gcc
FLAGS = -g -Wall
AR=ar

all: graph lib
lib: lib_allFaunctions.a
graph: main.o minheap.o GRAPH.o
	$(CC) $(FLAGS) -o graph main.o minheap.o GRAPH.o

main.o: main.c allFunctions.h
	$(CC) $(FLAGS) -c main.c

minheap.o: minheap.c allFunctions.h
	$(CC) $(FLAGS) -c minheap.c
GRAPH.o: GRAPH.c allFunctions.h
	$(CC) $(FLAGS) -c GRAPH.c

lib_allFaunctions.a: minheap.o GRAPH.o
	$(AR) -rcs lib_allFaunctions.a minheap.o GRAPH.o

.PHONY: clean all

clean:
		rm -f *.o *.a graph