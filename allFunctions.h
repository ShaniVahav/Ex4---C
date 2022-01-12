//
// Created by barse on 1/7/2022.
//

#ifndef DESKTOP_ALLFUNCTION_H
#define DESKTOP_ALLFUNCTION_H


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
    int ans ;
} node;

void insert_node_cmd(pnode *head,int node_num, double distance,pedge edges,struct GRAPH_NODE_ *next);
void delete_node_cmd(pnode* head,int IdDelNode );
node* getNode(pnode* head,int IdinNewNode);
void addEdge(pnode pointerToSrc, int dest , double weight, edge* next );
void deleteFromAlledges(pnode* head, int id);
int dijkstra(pnode* head, int src_id, int dest_id);
void tsp(pnode* head,int order[],int numberOfCitisMinus1);
void deleteGraph(pnode* head );
void permute(pnode * head,int citis [] , int l , int r);
void swap(int *x,  int *y);


#endif //DESKTOP_ALLFUNCTION_H
