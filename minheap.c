
#include "stdlib.h"
#include "stdio.h"

#define HEAP_CAPACITY 10000
#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2


typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int dest;
    double weight;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    double  distance ;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node;



typedef struct minHeap {
    int size ;
    node *elem ;
} minHeap ;


/*
    Function to initialize the min heap with size = 0
*/
minHeap initMinHeap(int size) {
    minHeap hp ;
    hp.size = 0 ;
    return hp ;
}


/*
    Function to swap data within two nodes of the min heap using pointers
*/
void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}


void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].distance < hp->elem[i].distance) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].distance < hp->elem[smallest].distance) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}

void insertNode(minHeap *hp, node* n) {
    if(hp->size) {
        hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
    } else {
        hp->elem = malloc(sizeof(node)) ;
    }

    
  

    int i = (hp->size)++ ;
    while(i && n->distance < hp->elem[PARENT(i)].distance) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    hp->elem[i] = *n ;
}



void deleteNode(minHeap *hp) {

    if(hp->size) {
       // printf("Deleting node %d\n\n", hp->elem[0].distance) ;
        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
       // printf("\nMin Heap is empty!\n") ;
        free(hp->elem) ;
    }
}

void deleteMinHeap(minHeap *hp) {
    free(hp->elem) ;

}