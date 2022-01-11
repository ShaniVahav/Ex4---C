

#ifndef DESKTOP_ALLFUNCTION_H
#define DESKTOP_ALLFUNCTION_H

#include "stdbool.h"

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

static int minTotalsum = 100000;  /////////when we put "t" , got to remember to update it
static int  largestDex = 0 ;
// static  int numberOfVertex = 0 ;
static  int time = 1 ;


void swap(node *n1, node *n2);
void insertNode(minHeap *hp, node* n);
void deleteNode(minHeap *hp);
void heapify(minHeap *hp, int i);
void deleteMinHeap(minHeap *hp) ;


void insert_node_cmd(pnode *head,int node_num, double distance,pedge edges,struct GRAPH_NODE_ *next);
void delete_node_cmd(pnode* head,int IdDelNode );
node* getNode(pnode* head,int IdinNewNode);
void addEdge(pnode pointerToSrc, int dest , double weight, edge* next );
void deleteFromAlledges(pnode* head, int id);
double* dijkstra(pnode* head , int src ,double distance[largestDex+1], int timep,bool visited[largestDex+1]);
int permute(pnode * head,int n, int size, int array[],int numberOfcitis );
void deleteGraph(pnode* head );




#endif //DESKTOP_ALLFUNCTION_H
