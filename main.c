#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "allFunction.h"

///////////////////A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0



int main() {
    pnode begin = NULL;
    pnode *head = &begin;
    int i = 0;
    int size = 0;
    int capacity = 25;
    char *str = NULL;//a pointer to an array of chars.
    str = malloc(capacity * sizeof(char));
    char current = 0;
    while (current != '\n') {
        scanf("%c", &current);
        if (size == capacity - 1) {
            if (current == 32)
                continue;
            str = realloc(str, capacity + 10);
            if (str == NULL) {  /////////////// just in case
                free(str);
                return 1;
            }
            capacity += 10;
        }
        if (current != 32) {
            str[i] = current;
            i++;
            size++;
        }       ///////////A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0
    }
        str[i] = '\n';


        i = 0;
        while (str[i] != '\n') {
            char c = str[i];
            if (c == 'A') {
                deleteGraph(head);
                i++;
                i++;
                bool flag = true;
                int dexOfnewNode = 0 ;
                do {
                    if (flag == true) {
                        i++;
                            dexOfnewNode = str[i] - '0';
                        if (getNode(head, dexOfnewNode) == NULL) {
                            insert_node_cmd(head, dexOfnewNode,100000,NULL,NULL);
                        }
                        i++;
                    }
                    int dest = str[i] - '0' ;
                    char zona = str[i];
                    if(47>zona || zona > 57)
                        continue;
                    if (getNode(head, dest) == NULL) {
                        insert_node_cmd(head, dest,100000,NULL,NULL);
                    }
                    int w = str[i + 1] - '0';
                    pnode PointerTosrc = (pnode)getNode(head,dexOfnewNode);
                    addEdge(PointerTosrc, dest, w, NULL);
                    i = i + 2;
                    if (str[i] != 'n')
                        flag = false;
                    else
                        flag = true;
                } while (str[i] == 'n' || (str[i] > 47 && str[i] < 59));
                c = str[i];
            }
            if (c == 'B') {
                i++;
                int numberOfdeletedB = str[i] - '0';
                i++;
                delete_node_cmd(head, numberOfdeletedB);
                insert_node_cmd(head, numberOfdeletedB,100000,NULL,NULL);
                while (str[i] < 59 && str[i] > 47) {
                    int dest = str[i] - '0';
                    int w = str[i + 1] - '0';
                    pnode pointer = getNode(head,numberOfdeletedB);
                    addEdge(pointer, dest, w, NULL);
                    i = i + 2;
                }
                c = str[i];
            }
            if (c == 'D') {
                i++;
                int numberOfDeletedC = str[i] - '0';
                delete_node_cmd(head, numberOfDeletedC);
                deleteFromAlledges(head, numberOfDeletedC);
                i++;
                c = str[i];
            }
            if (c == 'S') {
                i++;
                int src = str[i] - '0';
                i++;
                int dest = str[i] - '0';
                int answer = dijkstra(head, src, dest);
                printf("Dijsktra shortest path: %d\n", answer);

                i++;
                c = str[i];
            }

            if (c == 'T') {
                /////// update befure tsp
                i++;
                int numberofNodes = str[i] - '0';
                i++;
                int array[numberofNodes];
                int j = 0 ;
                for ( j = 0; j < numberofNodes; j++) {
                    int idOfCity = str[i+j] - '0';
                    c = str[i +j];
                    array[j] = idOfCity;
                }
                i = i + j ;
                (*head)->ans = 100000;
         
                 permute(head, array, 0 , numberofNodes-1 );
                if((*head)->ans >= 100000) {
                    printf("TSP shortest path: -1");
                }
                else {
                    printf("TSP shortest path: %d\n", (*head)->ans);
                }
                (*head)->ans = 100000;
                c = str[i];
            }


        }
   
    deleteGraph(head);
    }



































































