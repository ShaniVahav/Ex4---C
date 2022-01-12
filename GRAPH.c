#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "allFunction.h"


static int  largestIndex = 0;


void insert_node_cmd(pnode *head,int node_num, double distance,pedge edges,struct GRAPH_NODE_ *next){
    node* inNewNode = (node*) malloc(sizeof(node));
    inNewNode->next = NULL;
    inNewNode->edges = NULL;
    inNewNode->distance = 100000;
    inNewNode->node_num = node_num;
    if(inNewNode->node_num > largestIndex)
        largestIndex =inNewNode->node_num;
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
            temp = NULL;
        }
        current = current->next;
        free((*head));
        (*head) = current;
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
    if (current == NULL)
        return NULL;     
    else
        return current;
    return NULL;
}

void addEdge(pnode pThisNode, int dest , double weight, edge* next ) {
     if(pThisNode->edges == NULL) {
            edge *currentEdge = (edge *) malloc(sizeof(edge));
        
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
 bool stop(bool Visited[largestIndex+1]){
    for(int i = 0 ; i < largestIndex+1 ; i ++){
        if(Visited[i] == false)
            return false;    ///// dont stop the loop
    }
     return true;
}
/////double (* distance)[largestIndex+1]
int dijkstra(pnode* head, int src_id, int dest_id){
    int len_array = largestIndex+1;
    int d[len_array];
    int phi[len_array];
    bool visited[len_array];

    for (int i = 0; i < len_array; ++i) {
        phi[i] = 0;
        visited[i] = false;
        d[i] = 1000;
    }
    d[src_id] = 0;
    bool allVisited = false;
    int mindis = src_id;
    while (allVisited == false){
        node current;
        for (int i = 0; i < len_array ; ++i) {
            if(d[i] < d[mindis] && visited[i] == false){
                mindis = i;
            }
            current = *getNode(head, mindis);
            pedge edges = current.edges;
            while (edges != NULL){
                if(d[mindis] + edges->weight < d[edges->dest]) {
                    d[edges->dest] = d[mindis] + edges->weight;
                    phi[edges->dest] = mindis;
                }
                edges = edges->next;
            }
            visited[mindis] = true;

            // check if all visited
            allVisited = true;
            for (int j = 0; j < len_array; ++j) {
                if(visited[j] == false){
                    // check if is an actual node
                    node* n = *head;
                    while(n != NULL) {
                        if(n->node_num == j){
                            allVisited = false;
                            mindis = j;
                            break;
                        }
                        else{
                            n = n->next;
                        }
                    }

                }
            }
        }
    }
    int sum = 0, w;
    int i = dest_id;
    while (i != src_id){
        pedge pre_node_edges_node = getNode(head, phi[i])->edges;
        while (pre_node_edges_node != NULL){
            if(pre_node_edges_node->dest == i){
                w = pre_node_edges_node->weight;
                break;
            }
            pre_node_edges_node = pre_node_edges_node->next;
        }
        if(pre_node_edges_node == NULL){
            return -1;
        }
        sum += w;
        i = phi[i];
    }
    return sum;
}
void swap(int *x,  int *y){
int temp;
temp = *x;
*x = *y;
*y = temp;
}
/////////////A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0

 void permute(pnode* head,int citis [] , int l , int r){
    // printf(" athzeret is  : %d",athzeret);
    int i;
    if (l == r) {
        tsp(head,  citis, r);  ////// citis are order now
    }
    else{
        for (i = l; i <= r; i++){
            swap((citis+l), (citis+i));
            (permute(head,citis, l+1, r));
            swap((citis+l), (citis+i));
        }
    }
}




void tsp(pnode* head,int order[],int numberOfCitisMinus1) {
   // printf("nu");
    double sum = 0;      //////  sum of this path;   ///// for sending to dijkstra
    for (int i = 0; i < numberOfCitisMinus1; i++) {
        int answer = dijkstra(head, order[i],order[i+1]);
        if(answer == -1 ) {
            answer = answer + 100000;
            sum += answer;
        }
        else
           sum += answer;
    }
    if((*head)->ans > sum)
        (*head)->ans   = sum;


}
void deleteGraph(pnode* head ) {
    pnode current = *head;
    while (current != NULL) {
        current = *head;
        int number = current->node_num;
        current = current->next;
        delete_node_cmd(head, number);
        deleteFromAlledges(head, number);
    }
}













