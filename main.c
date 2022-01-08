#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main() {
    pnode graph;
    graph = (node *) malloc(sizeof(node));
    if ( graph == NULL ){
        printf("failed to allocate memory !! ");
        exit(1);
    }
    int num_of_vertices, flag = True;
    int *size;
    size = &num_of_vertices;
    int first_graph = True;
    int counter = 0 ;
    pnode *arr;
    arr= (pnode*)malloc(sizeof (pnode)*50);
    if ( arr == NULL ){
        printf("failed to allocate memory !! ");
        exit(1);
    }
    pnode to_delete =NULL;
    char menu = True;

    while (menu != EOF || menu != '\n' || menu != '\0') {
        if (flag) {
            scanf("%c", &menu);
            if (menu == EOF || menu == '\n'|| menu == '\0'){
           break;
            }
        } else {
            flag = True;
            if (menu == EOF || menu == '\n'|| menu == '\0'){
                break;
            }
        }
        switch (menu) {
            case 'A':
                scanf("%d", &num_of_vertices);

                menu = build_graph_cmd(&graph, size, first_graph);
                first_graph = 0;
                flag = 0;
                break;
            case 'B':
                menu = insert_node_cmd(&graph, size);
                flag = 0;
                break;
            case 'D':
                to_delete = delete_node_cmd(&graph, size);
                arr[counter]= to_delete;
                counter++;
                break;

            case 'S':
                shortsPath_cmd(graph, size);
                break;
            case 'T':
                TSP_cmd(graph, size);
                break;
            default:
                break;
        }


    }

    pedge currEdge;
    pedge tempEdge;

        for (int z = 0; z < num_of_vertices; z++) {
            currEdge = (graph + z)->edges;

            if (currEdge != NULL && currEdge->next == NULL ){
            free(currEdge);
            continue;
            }
            while (currEdge != NULL) {
                tempEdge = currEdge;
                currEdge = currEdge->next;
                free(tempEdge);
            }
        }
        if (to_delete != NULL) {
            for (int i = 0; i < counter ; i++){
                free(arr[i]);
            }

        }
    free(arr);
    free(graph);



    return 0;
}