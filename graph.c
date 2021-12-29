#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <ctype.h>

//    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 5 3 9 E
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

//    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 2 3 9 E
char insert_node_cmd(pnode *head, int *ptrSize){
    int size_g = *ptrSize;

    int keyNode , flag = 0 , weight , isFirst = 1 , savePos  ;
    char menu ;
    scanf("%d",&keyNode);
    pnode check = *head;
    pnode curr;
    pnode graph = *head;
    pedge currEdge ,tempEdge;
    for (int i = 0 ; i < size_g ; i++){
        check = graph+i;
        if (check->node_num == keyNode ){
            savePos= i ;
            flag = 1;
            break;
        }

    }


    if (flag){
        curr = graph+savePos;
        currEdge = curr->edges;
        tempEdge = currEdge;
        while (tempEdge != NULL){
            currEdge->next = NULL;
            free(currEdge);
            currEdge = NULL;
            currEdge = tempEdge->next;
            tempEdge = currEdge;
        }




    }
    else {

        graph = (node*) realloc(graph , sizeof (node)*size_g+1);
        curr = graph + size_g;
        curr->node_num = keyNode;
        pedge currEdge;
        scanf(" %c",&menu);
        while (1){
            if (isdigit(menu)) {
                if (isFirst) {

                    currEdge = (edge *) malloc(sizeof(edge));
                    curr->edges = currEdge;
                    currEdge->endpoint = (graph + (menu - '0'));
                    scanf(" %d", &weight);
                    currEdge->weight = weight;
                    isFirst = 0 ;
                }
                else {
                    pedge newEdge;
                    newEdge = (edge *) malloc(sizeof(edge));
                    currEdge->next = newEdge;
                    newEdge->endpoint = (graph + (menu - '0'));
                    scanf(" %d", &weight);
                    newEdge->weight = weight;

                }

            }
            else{
                *head = graph;
                *ptrSize = size_g+1;
                return menu;
            }
            scanf(" %c",&menu);


        }


    }





}

void printGraph_cmd(pnode head, int *ptrSize){
    int size_g= *ptrSize;
    pnode currNode;
    pedge currEdge;

    for ( int i = 0 ; i < size_g ; i++){
        currNode = (head+i);
        printf("id : %d  , edges :\n ", currNode->node_num);
        if ( currNode->edges != NULL) { // will be checked on printing
            currEdge = currNode->edges;
            printf("direct to %d , weight is %d\n",currEdge->endpoint->node_num, currEdge->weight);
            while (currEdge->next != NULL) {
            currEdge = currEdge->next;
            printf("direct to %d , weight is %d\n",currEdge->endpoint->node_num, currEdge->weight);
            }
        }

    }




}