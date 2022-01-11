CC = gcc
FLAGS = -g -Wall
AR=ar

all: graph lib
lib: lib_allFaunction.a
graph: main.o minheap.o GRAPH.o
	$(CC) $(FLAGS) -o graph main.o minheap.o GRAPH.o

main.o: main.c allFunctions.h
	$(CC) $(FLAGS) -c main.c

minheap.o: minheap.c allFunctions.h
	$(CC) $(FLAGS) -c minheap.c
GRAPH.o: GRAPH.c allFunctions.h
	$(CC) $(FLAGS) -c GRAPH.c

lib_allFaunction.a: minheap.o GRAPH.o
	$(AR) -rcs lib_allFaunction.a minheap.o GRAPH.o

.PHONY: clean all

clean:
		rm -f *.o *.a graph