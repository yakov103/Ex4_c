#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



int main() {
   pnode graph;
    graph = (node *) malloc(sizeof (node)) ;
    int num_of_vertices, flag = 1 ;
    int *size ;
    size = &num_of_vertices;

    char menu = 1;
    while (menu != 'E'){
        if (flag) {
            scanf(" %c", &menu);
        }
        else {
            flag = 1 ;
        }
        switch (menu) {
            case 'A':
                scanf("%d",&num_of_vertices);
                menu = build_graph_cmd(&graph,size);
                flag = 0;
                break;
            case 'B':
                num_of_vertices = insert_node_cmd(&graph,size);
                break;
            default:
                break;
        }


    }




    return 0;
}