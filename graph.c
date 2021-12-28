#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <ctype.h>

//    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 5 E
char build_graph_cmd(pnode *head, int *ptrSize){
    int size_g = *ptrSize;

    pnode graph ;
    graph = *head;
    free(graph);
    graph = (node*) malloc( sizeof (node)* size_g);
    pnode currentNode = graph;
    for ( int i = 0 ; i < size_g; i++){
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
                    *head = graph;
                    *ptrSize = size_g;
                    return menu;
                    break;
                }

        }
    }




}


char insert_node_cmd(pnode *head, int *ptrSize){
    int size_g = *ptrSize;

    int keyNode , flag = 0 , weight , isFirst = 1 ;
    char menu ;
    scanf("%d",&keyNode);
    pnode check = *head;
    for (int i = 0 ; i < size_g ; i++){
        if (check->node_num == keyNode ){
            flag = 1;
            break;
        }
    }


    if (flag){

    }
    else {
        pnode curr = *head;
        pnode graph = *head;
        curr = curr + size_g;
        curr = (node *) malloc(sizeof(node));
        curr->node_num = keyNode;
        pedge currEdge;
        scanf("%c",&menu);
        while (1){
            if (isdigit(menu)) {
                if (isFirst) {

                    currEdge = (edge *) malloc(sizeof(edge));
                    curr->edges = currEdge;
                    currEdge->endpoint = (graph + (menu - '0'));
                    scanf("%d", &weight);
                    currEdge->weight = weight;
                    isFirst = 0 ;
                }
                else {
                    pedge newEdge;
                    newEdge = (edge *) malloc(sizeof(edge));
                    currEdge->next = newEdge;
                    newEdge->endpoint = (graph + (menu - '0'));
                    scanf("%d", &weight);
                    newEdge->weight = weight;

                }

            }
            else{
                *head = graph;
                *ptrSize = size_g+1;
                return menu;
            }
            scanf("%c",&menu);


        }


    }





}