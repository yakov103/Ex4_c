#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



int main() {
   pnode graph;
    graph = (node *) malloc(sizeof (node)) ;
    int num_of_vertices;


    char menu = 1;
    while (menu != 'E'){
        scanf(" %c",&menu);
        switch (menu) {
            case 'A':
                scanf("%d",&num_of_vertices);
                build_graph_cmd(&graph,num_of_vertices);
                int a = 3;
                break;
            default:
                break;
        }


    }




    return 0;
}