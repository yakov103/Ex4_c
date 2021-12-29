#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define INFTY 10000

//    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 5 3 9 E
char build_graph_cmd(pnode *head, int *ptrSize) {
    int size_g = *ptrSize;

    pnode graph;
    graph = *head;
    free(graph);
    graph = (node *) malloc(sizeof(node) * size_g);
    pnode currentNode = graph;
    for (int i = 0; i < size_g; i++) {
        currentNode->node_num = i;
        currentNode++;
    }


    char menu = 1;
    int keyNode, weight, destNode, flag = 1;
    while (menu) {
        if (flag) {
            scanf(" %c", &menu);
        } else {
            flag = 1;
        }
        switch (menu) {
            case 'n':
                scanf(" %d", &keyNode);
                currentNode = (graph + keyNode);
                pedge currEdge;
                currEdge = (edge *) malloc(sizeof(edge));
                currentNode->edges = currEdge;
                scanf(" %c", &menu);
                if (isdigit(menu)) {
                    destNode = menu - '0';
                    currEdge->endpoint = (graph + destNode);
                    scanf(" %d", &weight);
                    currEdge->weight = weight;


                } else {
                    flag = 0;
                    currentNode->edges = NULL;
                    free(currEdge);
                }

                break;
            default:
                if (isdigit(menu)) {
                    pedge newEdge;
                    newEdge = (edge *) malloc(sizeof(edge));
                    currEdge->next = newEdge;
                    currEdge = currEdge->next;
                    keyNode = menu - '0';
                    currEdge->endpoint = (graph + keyNode);
                    scanf("%d", &weight);
                    currEdge->weight = weight;


                    break;
                } else {
                    *head = graph;
                    *ptrSize = size_g;
                    return menu;
                    break;
                }

        }
    }


}

//    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 2 3 9 E
//    A 4 n 0 1 1 2 2 n 2 0 0 1 1 n 1 3 3 0 0 n 3 B 5 3 3 E
char insert_node_cmd(pnode *head, int *ptrSize) {
    int size_g = *ptrSize;

    int keyNode, flag = 0, weight, isFirst = 1, savePos;
    char menu;
    scanf("%d", &keyNode);
    pnode check = *head;
    pnode curr;
    pnode graph = *head;
    pedge currEdge, tempEdge;
    for (int i = 0; i < size_g; i++) {
        check = graph + i;
        if (check->node_num == keyNode) {
            savePos = i;
            flag = 1;
            break;
        }

    }


    if (flag) {
        curr = graph + savePos;
        currEdge = curr->edges;

        while (currEdge != NULL) {
            tempEdge = currEdge;
            currEdge = currEdge->next;
            free(tempEdge);
        }
        currEdge = NULL;
        curr->edges = NULL;
        scanf(" %c", &menu);
        while (1) {
            if (isdigit(menu)) {
                if (isFirst) {

                    currEdge = (edge *) malloc(sizeof(edge));
                    curr->edges = currEdge;
                    currEdge->endpoint = (graph + (menu - '0'));
                    scanf(" %d", &weight);
                    currEdge->weight = weight;
                    isFirst = 0;
                } else {
                    pedge newEdge;
                    newEdge = (edge *) malloc(sizeof(edge));
                    currEdge->next = newEdge;
                    newEdge->endpoint = (graph + (menu - '0'));
                    scanf(" %d", &weight);
                    newEdge->weight = weight;

                }

            } else {
                *head = graph;
                *ptrSize = size_g;
                return menu;
            }
            scanf(" %c", &menu);


        }


    } else {

        graph = (node *) realloc(graph, sizeof(node) * size_g + 1);
        curr = graph + size_g;
        curr->node_num = keyNode;
        pedge currEdge;
        scanf(" %c", &menu);
        while (1) {
            if (isdigit(menu)) {
                if (isFirst) {

                    currEdge = (edge *) malloc(sizeof(edge));
                    curr->edges = currEdge;
                    currEdge->endpoint = (graph + (menu - '0'));
                    scanf(" %d", &weight);
                    currEdge->weight = weight;
                    isFirst = 0;
                } else {
                    pedge newEdge;
                    newEdge = (edge *) malloc(sizeof(edge));
                    currEdge->next = newEdge;
                    newEdge->endpoint = (graph + (menu - '0'));
                    scanf(" %d", &weight);
                    newEdge->weight = weight;

                }

            } else {
                *head = graph;
                *ptrSize = size_g + 1;
                return menu;
            }
            scanf(" %c", &menu);


        }


    }


}

void printGraph_cmd(pnode head, int *ptrSize) {
    int size_g = *ptrSize;
    pnode currNode;
    pedge currEdge;

    for (int i = 0; i < size_g; i++) {
        currNode = (head + i);
        printf("id : %d  , edges :\n ", currNode->node_num);
        if (currNode->edges != NULL) { // will be checked on printing
            currEdge = currNode->edges;
            int direct = currEdge->endpoint->node_num;
            int weight = currEdge->weight;
            printf("direct to %d , weight is %d\n", direct, weight);
            while (currEdge->next != NULL) {
                currEdge = currEdge->next;
                printf("direct to %d , weight is %d\n", currEdge->endpoint->node_num, currEdge->weight);
            }
        }

    }


}

// A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 5 3 9 D 2 E
void delete_node_cmd(pnode *head, int *ptrSize) {
    int size_g = *ptrSize, k = 0;
    size_g--;
    pnode newGraph;
    newGraph = (node *) malloc(sizeof(node) * (size_g));
    pnode oldGraph = *head;
    pnode ptr_free_old_graph = *head;
    pnode new_graph_first = newGraph;
    int node_to_del;
    scanf(" %d", &node_to_del);
    pedge prevEdge, tempEdge;
    for (int i = 0; i < size_g + 1; i++) {
        if (oldGraph->node_num != node_to_del) {
            tempEdge = oldGraph->edges;
            if (tempEdge != NULL && tempEdge->endpoint->node_num == node_to_del) {
                if (tempEdge->next == NULL) {
                    oldGraph->edges = NULL;
                } else {
                    oldGraph->edges = tempEdge->next;
                }
                free(tempEdge);
            } else {
                while (tempEdge != NULL && tempEdge->endpoint->node_num != node_to_del) {
                    prevEdge = tempEdge;
                    tempEdge = tempEdge->next;
                }
                if (tempEdge != NULL) {
                    prevEdge->next = tempEdge->next;
                    free(tempEdge);
                }
            }

            *newGraph = *oldGraph;
            oldGraph++;
            newGraph++;


        } else {
            oldGraph++;
        }
        prevEdge = NULL;
        tempEdge = NULL;


    }
    free(ptr_free_old_graph);
    ptr_free_old_graph = NULL;
    *ptrSize = size_g;
    *head = new_graph_first;


}
char caer;

//A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 S 0 2 E
void shortsPath_cmd(pnode head, int *ptrSize) {
    int *dijkstra_matrix;
    int size_g = *ptrSize;
    dijkstra_matrix = (int *) malloc(sizeof(int) * size_g * size_g);
    for (int i = 0; i < size_g * size_g; i++) {
        dijkstra_matrix[i] = INFTY;
    }
    pnode graph = head;
    int *visited, counter = size_g, min = INT_MAX, k, node_iter, temp;
    visited = (int *) calloc(size_g, sizeof(int));
    pedge currEdge;
    for (int i = 0; i < size_g; i++) {
        visited[i] = 1;
        counter--;
        dijkstra_matrix[i * size_g + i] = 0;
        currEdge = (graph + i)->edges;
        while (currEdge != NULL) {
            dijkstra_matrix[i * size_g + currEdge->endpoint->node_num] = currEdge->weight;
            currEdge = currEdge->next;
        }

        while (counter) {
            min = INT_MAX;
            for (k = 0; k < size_g; k++) {
                if (dijkstra_matrix[i * size_g + k] < min) {
                    if (visited[k] == 0) {
                        node_iter = k;
                        min = dijkstra_matrix[i * size_g + k];
                    }
                }
            }
            currEdge = (graph + node_iter)->edges;
            while (currEdge != NULL) {
                temp = currEdge->weight;
                k = currEdge->endpoint->node_num;
                if (dijkstra_matrix[i * size_g + k] > dijkstra_matrix[size_g * i + node_iter] + temp) {
                    dijkstra_matrix[i * size_g + k] = dijkstra_matrix[size_g * i + node_iter] + temp;
                }
                currEdge = currEdge->next;
            }
            counter--;
            visited[node_iter] = 1;
        }
        free(visited);
        visited = (int *) calloc(size_g, sizeof(int));
        counter = size_g;

    }

    printf("\nDijsktra shortest path:");
    char src;
    char dest;
    scanf(" %c", &src);
    if (isdigit(src)) {
        scanf(" %c", &dest);
        if (isdigit(dest)) {
            printf(" %d" ,dijkstra_matrix[(src-'0') * size_g + (dest-'0')]);
        }
    }
    printf("\n");


}


void TSP_cmd(pnode head, int *ptrSize){



    int *dijkstra_matrix;
    int size_g = *ptrSize;


    char ** strings , *tempStr [30];
    strings = malloc(size_g*size_g*sizeof (char*));




    dijkstra_matrix = (int *) malloc(sizeof(int) * size_g * size_g);
    for (int i = 0; i < size_g * size_g; i++) {
        dijkstra_matrix[i] = INFTY;
        strings[i]= (char*)calloc (30,sizeof (char));
    }
    pnode graph = head;
    int *visited, counter = size_g, min = INT_MAX, k, node_iter, temp;
    visited = (int *) calloc(size_g, sizeof(int));
    pedge currEdge;
    for (int i = 0; i < size_g; i++) {
        visited[i] = 1;
        counter--;
        dijkstra_matrix[i * size_g + i] = 0;
        currEdge = (graph + i)->edges;
        while (currEdge != NULL) {
            dijkstra_matrix[i * size_g + currEdge->endpoint->node_num] = currEdge->weight;
            sprintf(strings[i * size_g + currEdge->endpoint->node_num], "%d", currEdge->endpoint->node_num);

            currEdge = currEdge->next;
        }

        while (counter) {
            min = INT_MAX;
            for (k = 0; k < size_g; k++) {
                if (dijkstra_matrix[i * size_g + k] < min) {
                    if (visited[k] == 0) {
                        node_iter = k;
                        min = dijkstra_matrix[i * size_g + k];
                    }
                }
            }
            currEdge = (graph + node_iter)->edges;
            while (currEdge != NULL) {
                temp = currEdge->weight;
                k = currEdge->endpoint->node_num;
                if (dijkstra_matrix[i * size_g + k] > dijkstra_matrix[size_g * i + node_iter] + temp) {
                    dijkstra_matrix[i * size_g + k] = dijkstra_matrix[size_g * i + node_iter] + temp;
                    sprintf(strings[i * size_g + k],"%s_%d",strings[size_g * i + node_iter],k);
                }
                currEdge = currEdge->next;
            }
            counter--;
            visited[node_iter] = 1;
        }
        free(visited);
        visited = (int *) calloc(size_g, sizeof(int));
        counter = size_g;

    }

    printf("\nDijsktra shortest path:");
    char src;
    char dest;
    scanf(" %c", &src);
    if (isdigit(src)) {
        scanf(" %c", &dest);
        if (isdigit(dest)) {
            printf(" %d , %s" ,dijkstra_matrix[(src-'0') * size_g + (dest-'0')],strings[(src-'0') * size_g + (dest-'0')]);
        }
    }
    printf("\n");


}
// A 4 n 0 1 6 2 2 3 1 n 2 0 1 1 5 n 3 1 1 n 1 S 2 1 E
// A 3 n 0 2 2 1 4 n 2 1 1 n 1 E