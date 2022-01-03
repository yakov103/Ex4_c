#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main() {
    pnode graph;
    graph = (node *) malloc(sizeof(node));
    int num_of_vertices, flag = 1;
    int *size;
    size = &num_of_vertices;
    int first_graph = 1;
    int counter = 0 ;
    pnode *arr;
    arr= (pnode*)malloc(sizeof (pnode)*20);
    pnode to_delete =NULL;
    char menu = 1;
    while (menu != EOF) {
        if (flag) {
            scanf(" %c", &menu);
        } else {
            flag = 1;
        }
        switch (menu) {
            case 'A':
                scanf(" %d", &num_of_vertices);
                if (!first_graph){

                }
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