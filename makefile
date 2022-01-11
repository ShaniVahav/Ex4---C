CC = gcc
FLAGS = -g -Wall
AR=ar

all: prog

prog: main.o minheap.o allFunction.h
	$(CC) $(FLAGS) -o graph main.o minheap.o
main.o: main.c allFunction.h
	$(CC) $(FLAGS) -c main.c
minheap.o: minheap.c minheap.h
	$(CC) $(FLAGS) -c minheap.c

.PHONY: clean all

clean:
		rm -f *.o *.a graph