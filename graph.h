#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

char build_graph_cmd(pnode *head, int *ptrSize, int first_graph);

char insert_node_cmd(pnode *head, int *ptrSize);

void delete_node_cmd(pnode *head, int *ptrSize);

void printGraph_cmd(pnode head, int *ptrSize); //for self debug
void deleteGraph_cmd(pnode *head);

void shortsPath_cmd(pnode head, int *ptrSize);

void TSP_cmd(pnode head, int *ptrSize);


#endif
