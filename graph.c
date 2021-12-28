#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <ctype.h>

//    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2
void build_graph_cmd(pnode *head, int SIZE){

    pnode graph ;
    graph = *head;
    graph = (node* ) realloc(graph, SIZE);
    pnode currentNode = graph;
    for ( int i = 0 ; i < SIZE; i++){
        currentNode->node_num = i ;
        currentNode++;
    }





    char menu = 1;
    int keyNode, weight, destNode;
    while (menu){
        scanf(" %c",&menu);

        switch (menu) {
            case 'n':
                scanf(" %d", &keyNode);
                currentNode = (graph+keyNode) ;
                pedge currEdge;
                currEdge = ( edge*) malloc(sizeof (edge));
                currentNode->edges = currEdge;
                scanf("%d",&destNode);
                currEdge->endpoint = (graph+destNode);
                scanf("%d",&weight);
                currEdge->weight = weight;

                break;
            default:
                if (isdigit(menu)){
                    pedge  newEdge;
                    newEdge = (edge*) malloc(sizeof (edge));
                    currEdge->next= newEdge;
                    currEdge = currEdge->next;
                    keyNode = menu - '0';
                    currEdge->endpoint = (graph+keyNode);
                    scanf("%d", &weight);
                    currEdge->weight = weight;


                    break;
                }
                else {
                    menu = '\0';
                    head = &graph;
                    break;
                }

        }
    }




}


void insert_node_cmd(pnode *head){



}