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
    int keyNode, weight, destNode, flag = 1 ;
    while (menu){
        if (flag){
        scanf(" %c",&menu);
            }
        else {
            flag = 1;
        }
        switch (menu) {
            case 'n':
                scanf(" %d", &keyNode);
                currentNode = (graph+keyNode) ;
                pedge currEdge;
                currEdge = ( edge*) malloc(sizeof (edge));
                currentNode->edges = currEdge;
                scanf(" %c",&menu);
                if (isdigit(menu)){
                    destNode = menu - '0';
                    currEdge->endpoint = (graph+destNode);
                    scanf(" %d",&weight);
                    currEdge->weight = weight;


                }
                else {
                    flag = 0 ;
                    currentNode ->edges = NULL;
                    free(currEdge);
                }

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

        while (currEdge != NULL){
            tempEdge= currEdge;
            currEdge = currEdge ->next;
            free(tempEdge);
        }
        currEdge= NULL;
        curr->edges = NULL;
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
                *ptrSize = size_g;
                return menu;
            }
            scanf(" %c",&menu);


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
// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 5 3 9 D 2 E
void delete_node_cmd(pnode *head, int *ptrSize ){
    int size_g = *ptrSize, k = 0 ;
    size_g--;
    pnode newGraph;
    newGraph = (node *) malloc(sizeof (node)*(size_g));
    pnode oldGraph = *head;
    pnode ptr_free_old_graph = *head;
    pnode new_graph_first= newGraph;
    int node_to_del;
    scanf(" %d",&node_to_del);
    pedge prevEdge ,tempEdge;
    for ( int i = 0; i < size_g+1 ; i++){
        if (oldGraph->node_num != node_to_del){
            tempEdge = oldGraph->edges;
            if (tempEdge != NULL  && tempEdge->endpoint->node_num == node_to_del){
                if (tempEdge->next == NULL){
                    oldGraph->edges = NULL;
                }
                else {
                    oldGraph->edges = tempEdge->next;
                }
                free(tempEdge);
            }
            else {
                while (tempEdge != NULL && tempEdge->endpoint->node_num != node_to_del){
                    prevEdge = tempEdge;
                    tempEdge = tempEdge->next;
                }
                if (tempEdge != NULL){
                    prevEdge->next = tempEdge->next;
                    free(tempEdge);
                }
            }

            *newGraph = *oldGraph;
            oldGraph++;
            newGraph++;


        }
        else {
            oldGraph++;
        }
        prevEdge= NULL;
        tempEdge= NULL;


    }
    free(ptr_free_old_graph);
    ptr_free_old_graph = NULL;
    *ptrSize = size_g;
    *head = new_graph_first;





}