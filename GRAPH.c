#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "allFunction.h"






void insert_node_cmd(pnode *head,int node_num, double distance,pedge edges,struct GRAPH_NODE_ *next){
    node* inNewNode = (node*) malloc(sizeof(node));
    inNewNode->next = NULL;
    inNewNode->edges = NULL;
    inNewNode->distance = 100000;
    inNewNode->node_num = node_num;
    if(inNewNode->node_num > largestDex)
        largestDex =inNewNode->node_num;
    if(*head == NULL) {
        *head = inNewNode;
    }
    else{
        node* temp = *head;
        *head = inNewNode;
        (*inNewNode).next = temp;
    }
}
void delete_node_cmd(pnode* head,int IdDelNode ) {
    node *current = *head;
    if (current == NULL) {
        return;
    } else if (current->node_num == IdDelNode) {
        edge *currentEdge = current->edges;
        while (currentEdge != NULL) {
            edge *temp = currentEdge;
            currentEdge = currentEdge->next;
            free(temp);
        }
        current =current->next;
        free((*head));
        (*head) = current->next;
    } else {
        node *prevToCurrent = current;
        current = current->next;
        while (current != NULL && current->node_num != IdDelNode) {
            current = current->next;
            prevToCurrent = prevToCurrent->next;
        }
        if (current != NULL) {
            edge *currentEdge = current->edges;
            while (currentEdge != NULL) {
                edge *temp = currentEdge;
                currentEdge = currentEdge->next;
                free(temp);
            }
            prevToCurrent->next = current->next;
            free(current);
        }

    }
}
node* getNode(pnode* head,int IdinNewNode) {
    pnode current = *head;
    while (current != NULL && current->node_num != IdinNewNode) {
        current = current->next;
    }
    
    return current;
}

void addEdge(pnode pThisNode, int dest , double weight, edge* next ) {
     if(pThisNode->edges == NULL) {
            edge *currentEdge = (edge *) malloc(sizeof(edge));
            // currentEdge->dest - dest;
            currentEdge->next = NULL;
            currentEdge->dest = dest;
            currentEdge->weight = weight;
            pThisNode->edges = currentEdge;
        }
     else{
        edge * temp = pThisNode->edges;
        edge* currentEdge = (edge*)malloc(sizeof(edge));
        currentEdge->next = pThisNode->edges;
        currentEdge->dest = dest;
        currentEdge->weight = weight;
        pThisNode->edges = currentEdge;
        currentEdge->next = temp;
    }
}
void deleteFromAlledges(pnode* head, int id) {
    node *current = *head;
    while (current != NULL) {
        edge *currentDestP = current->edges;   ///// alsways
        if(currentDestP == NULL) {
            current = current->next;
            continue;
        }
        if(currentDestP->dest == id){
            currentDestP = currentDestP->next;
            free(current->edges);
            current->edges = currentDestP;
            current = current->next;
            continue;
        }
        else{
            edge *prevToPointer = currentDestP;
            currentDestP =currentDestP->next;
            while (currentDestP != NULL && currentDestP->dest != id) {
                currentDestP =currentDestP->next;
                prevToPointer= prevToPointer->next;
            }
            if (currentDestP != NULL) {
                prevToPointer->next = currentDestP->next;
                free(currentDestP);
            }
        }
        current = current->next;

    }
}
/////double (* distance)[largestDex+1]
double* dijkstra(pnode* head , int src ,double distance[largestDex+1], int timep,bool visited[largestDex+1]){
  //  printf("%d\n",timep);
   // pnode begin = *head;
    for(int i = 0 ; i < largestDex+1; i ++){
        visited[i] = false;
        distance[i] =100000;
    }
    minHeap* h = (minHeap*)malloc(sizeof(minHeap));
    h->elem =NULL;
    h->size = 0 ;
    node* pToCurrent = getNode(head, src);
    pToCurrent->distance = 0;
    insertNode( h, pToCurrent);
    // *(distance[src]) = 0 ;
    while (h->size !=0) {
        node current = h->elem[0];
        deleteNode(h); /////////////////// 205feb218a0
        if (visited[current.node_num] == false){
            visited[src] =true;
            edge *currentEdge = current.edges;
            while (currentEdge != NULL) {
                node *pTocurrentDest = getNode(head, currentEdge->dest);
                double x = pTocurrentDest->distance;   // ((*distance)[currentDest.node_num]);
                double y = current.distance; // *(distance[current.node_num]);
                double z = currentEdge->weight;
                if (x > y + z) {
                    // (*(distance[currentDest.node_num]) = *(distance[current.node_num]) + currentEdge->weight);
                    //currentDest.distance =  *(distance[currentDest.node_num]);
                    pTocurrentDest->distance = current.distance + currentEdge->weight;
                    distance[pTocurrentDest->node_num] = pTocurrentDest->distance;
                    insertNode(h, pTocurrentDest);
                }
                currentEdge = currentEdge->next;
            }
        }
    }
    for(int i =0 ; i < largestDex+1 ; i ++){
      //  printf("%d is %f:\n",i,distance[i]);
    }
    deleteMinHeap(h);
    free(h);
    pnode current = *head;
    while (current !=NULL){
        current->distance = 100000;
        current = current->next;
    }
    return distance;
    }

double tsp(pnode* head,int order[],int numberOfCitis ) {
   // printf("nu");
    double sum = 0;      //////  sum of this path;   ///// for sending to dijkstra
    for (int i = 0; i < numberOfCitis - 1; i++) {
       // int from = order[i];
        // int to = order[i + 1];
        double distance[largestDex + 1];
        bool visited[largestDex+1];
        double *arr = dijkstra(head, order[i], distance,time++,visited);
        int realNumber = order[i+1];
       // int w = arr[realNumber];/////returning arr of double
        double next = arr[realNumber];      ///
        if (next == 100000)
            return -1;
         sum += next;
    }
    return sum;

}
/////  n is built in
////// size is built in
//// array is the citis array
////// numberOfcitis is the size of the array
    int permute(pnode * head,int n, int size, int array[],int numberOfcitis ) {
    int tmp;int currentsum = 0;int j;int i;
    if (n == 1) {
        currentsum = tsp(head, array, numberOfcitis);
        if (minTotalsum > currentsum && currentsum!=-1)
            minTotalsum = currentsum;
    } else {
        for (i = 0; i < n; i++) {
            permute(head, n - 1, size, array, numberOfcitis);
            j = (n % 2 == 1) ? n - 1 : 0;
            tmp = array[n - 1];
            array[n - 1] = array[j];
            array[j] = tmp;
        }
        if(minTotalsum != 100000)
             // printf("min total sum is :  %d\n ", minTotalsum);
            return minTotalsum;
        
            return -1;
  //                  printf("-1");
    }
}

void deleteGraph(pnode* head ) {
    pnode current = *head;
    while (current != NULL) {
        int number = current->node_num;
        current = current->next;
        delete_node_cmd(head, number);
        deleteFromAlledges(head, number);
    }
}













