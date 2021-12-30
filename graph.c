#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define INFTY 10000
char *pstring="1234";
int   plen;
int *tsp_array;
int **tsp_permutations;

void permutatuion();
void  perminit(char *s);
int   permtick(void);
void buildperm(char *s);

//    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 B 5 3 9 E
char build_graph_cmd(pnode *head, int *ptrSize, int first_graph) {



    int size_g = *ptrSize;
    pnode graph;
    graph = *head;

    if (!first_graph){
        pedge edge_to_del ;
        pedge temp_edge_to_del;
        for (int i = 0 ; i < size_g ; i++){
            edge_to_del = (graph+i)->edges;
            while(edge_to_del != NULL){
                temp_edge_to_del = edge_to_del;
                edge_to_del = edge_to_del->next;
                free(temp_edge_to_del);
                temp_edge_to_del = NULL;
            }
        }

    }
    free(graph);
    graph = (node *) malloc(sizeof(node) * size_g);
    pnode currentNode = graph;


    for (int i = 0; i < size_g; i++) {
        currentNode->node_num = i;
        currentNode++;
    }

    pedge newEdge = NULL;
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

                    newEdge = (edge *) malloc(sizeof(edge));
                    newEdge->next = NULL;
                    newEdge->endpoint = NULL;
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

    return menu;
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

                    for (int i = 0; i < size_g; i++) {
                        check = graph + i;
                        if (check->node_num == (menu - '0')) {
                            savePos = i;
                            break;
                        }

                    }

                    newEdge->endpoint = (graph + savePos);
                    scanf(" %d", &weight);
                    newEdge->weight = weight;
                    newEdge->next=NULL;

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
    printf("\n");
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


    pnode node_to_copy;
    int node_to_del  ;
    scanf(" %d", &node_to_del);
    pedge prevEdge, tempEdge;
    for (int i = 0; i < size_g + 1; i++) {
        node_to_copy = oldGraph+i;
        if (node_to_copy->node_num != node_to_del) {
            tempEdge = node_to_copy->edges;
            if (tempEdge != NULL && tempEdge->endpoint->node_num == node_to_del) {
                if (tempEdge->next == NULL) {
                    node_to_copy->edges = NULL;
                } else {
                    node_to_copy->edges = tempEdge->next;
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

            newGraph[k] = *node_to_copy;
           k++;


        } else {
            continue;
        }


    }

    *ptrSize = size_g;
    *head = newGraph;


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
            k = currEdge->endpoint->node_num;
            for (int j = 0 ; j < size_g; j++ ){
                if ( k == (graph+j)->node_num){
                    k = j;
                    break;
                }
            }

            dijkstra_matrix[i * size_g + k] = currEdge->weight;
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
                for (int j = 0 ; j < size_g; j++ ){
                    if ( k == (graph+j)->node_num){
                        k = j;
                        break;
                    }
                }
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
    free(visited);
    char src;
    char dest;
    scanf(" %c", &src);
    if (isdigit(src)) {
        scanf(" %c", &dest);
        if (isdigit(dest)) {
            int first = src-'0';
            int second = dest-'0';
            for ( int i =0 ; i <size_g ; i++){
              if (first == (graph+i)->node_num){
                  first= i ;
              }
              if (second == (graph+i)->node_num){
                  second= i ;
              }

            }
            printf("Dijsktra shortest path: %d " ,dijkstra_matrix[first * size_g + second]);
        }
    }
    printf("\n");
    free(dijkstra_matrix);

}

//A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 1 2 3 E
int factorial (int n){
    if ( n == 0 )return 1 ;
    else {
        return n * factorial(n-1);
    }
}


void TSP_cmd(pnode head, int *ptrSize){

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
            k = currEdge->endpoint->node_num;
            for (int j = 0 ; j < size_g; j++ ){
                if ( k == (graph+j)->node_num){
                    k = j;
                    break;
                }
            }

            dijkstra_matrix[i * size_g + k] = currEdge->weight;
            currEdge = currEdge->next;
        }

        while (counter) {
            min = INT_MAX;
            for (int x = 0; x < size_g; x++) {
                if (dijkstra_matrix[i * size_g + x] < min) {
                    if (visited[x] == 0) {
                        node_iter = x;
                        min = dijkstra_matrix[i * size_g + x];
                    }
                }
            }
            currEdge = (graph + node_iter)->edges;
            while (currEdge != NULL) {
                temp = currEdge->weight;
                k = currEdge->endpoint->node_num;
                for (int j = 0 ; j < size_g; j++ ){
                    if ( k == (graph+j)->node_num){
                        k = j;
                        break;
                    }
                }
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
    free(visited);

    int timesToRun;
    scanf(" %d",&timesToRun);

    plen = timesToRun;
    tsp_array = (int*) malloc(sizeof(int)*timesToRun);
    for (int i = 0 ; i < timesToRun ; i++){
        scanf(" %d",&tsp_array[i]);
        for ( int j = 0 ; j < size_g ; j++){
            if (tsp_array[i] == (graph+j)->node_num){
                tsp_array[i] = j;
                break;
            }

        }
    }

    int factorial_permutation = factorial(timesToRun);
    tsp_permutations = malloc(sizeof(int*)*factorial_permutation);
    for (int i =0 ; i < factorial_permutation ; i ++) {
        tsp_permutations[i]= (int*)malloc (sizeof(int)* timesToRun);
    }

    

    pstring = (char*) calloc(plen+1,sizeof (char));
    for (int i = 0 ; i < timesToRun ; i++){
        pstring[i] = (int)tsp_array[i]+'0';
    }
    permutatuion();
    min = INFTY;
    int sum;
    int *currArray, the_one,the_second;
    for (int i = 0; i < factorial_permutation ; i++ ){
        sum=0 ;
        currArray = tsp_permutations[i];
        for ( int j = 0; j < timesToRun-1 ; j++ ){
           the_one = currArray[j];
           the_second =  currArray[j+1];
            sum+= dijkstra_matrix[the_one*size_g+the_second];
        }
        if ( sum < min){
            min = sum;
        }

    }

    if (min >= 5000){
        min = -1;
    }
    printf("TSP shortest path: %d \n",min);

    for (int i =0 ; i < factorial_permutation ; i ++) {
        free(tsp_permutations[i]);
    }
    free(dijkstra_matrix);
    free(tsp_permutations);

}




// A 4 n 0 1 6 2 2 3 1 n 2 0 1 1 5 n 3 1 1 n 1 S 2 1 E
// A 3 n 0 2 2 1 4 n 2 1 1 n 1 E

/* -- Permutation String -- */


/* -- Declare functions used later -- */


/* -- Global Variables -- */
char *perm, *poly;
int *permInt, *polyInt;
int tempkey;
/* -- -- MAIN -- -- */
void permutatuion(){
    tempkey = 0 ;

    perminit(pstring);

    do {
        /* Build current permutation from poly */
        buildperm(pstring);

        for ( int i = 0 ; i < plen ; i++){
            tsp_permutations[tempkey][i]= (int)perm[i]-'0';
        }
        tempkey++;

        // Do some real work 

        // The stack is lightweight because the entire
        // state is held in poly, and there is no need
        // for the function callback nonsense 

        // Permtick advances poly to the next permutation
        // and returns 0 when there are none left 

    } while(permtick());
}






void perminit(char *s) {
    // We have moved the init code to an init function,
    // where it truly belongs 


    perm=(char *)malloc((plen+1)*sizeof(char));
    perm[plen]=0;

    poly=(char *)malloc((plen+1)*sizeof(char));

    // poly is a byte array that we are going to use as a big counter 
    int p;
    for(p=0;p<plen;p++) poly[p]=0;
}

int permtick(void) {
    // Each time we call permtick, it increments our poly counter 

    int ret=-1;   // Return True by default 
    int p=plen-2; // Start at 2nd to last position 

    while( p >= 0 ) {
        // Increment poly digit 
        poly[p]++;

        // If poly digit exceeds plen-p, move to
        // the next digit and loop 
        if(poly[p]>=(plen-p)) {
            poly[p]=0;
            p--;

            // FYI - this is why poly[plen-1] is always 0:
            // That's it's maximum value, which is why we
            // start at plen-2 
        } else {
            p=-2;        // Done looping 
        }
    }

    // All permutations have been calculated and p=-1 
    if(p==-1) ret=0;

    return(ret);
}


void buildperm(char *s) {
    // Build a permutation from the poly counter 

    char c;
    int i;

    // Start with a fresh copy of the string 
    for(i=0;i<plen;i++) perm[i]=s[i];

    // Swap digits based on each poly digit 
    // if poly[i]>0 then swap with the (i+nth) digit 
    for(i=0;i<(plen-1);i++) if(poly[i]>0) {
            c              =perm[i];
            perm[i]        =perm[i+poly[i]];
            perm[i+poly[i]]=c;
        }
}