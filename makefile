CC = gcc
FLAGS = -g -Wall
AR=ar

all: graph lib
lib: lib_allFaunctions.a
graph: main.o GRAPH.o
	$(CC) $(FLAGS) -o graph main.o GRAPH.o

main.o: main.c
	$(CC) $(FLAGS) -c main.c

GRAPH.o: GRAPH.c
	$(CC) $(FLAGS) -c GRAPH.c

lib_allFaunctions.a: GRAPH.o
	$(AR) -rcs lib_allFaunctions.a GRAPH.o

.PHONY: clean all

clean:
		rm -f *.o *.a graph