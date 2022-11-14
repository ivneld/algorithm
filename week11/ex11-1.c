#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct incidence Incidence;

typedef struct vertex{
    int key;
    Incidence *head;
    struct vertex* next;
    int label;
}Vertex;

typedef struct edge{
    Vertex *a;
    Vertex *b;
    struct edge* next;
}Edge;

struct incidence{
    Edge *edge;
    Incidence *next;
};
    // 0 1 2 4 5
typedef struct listGraph {
    Vertex *vertexList;
    Edge *edgeList;
} ListGraph;

ListGraph *initGraph(int verNum, int edgeNum){
    ListGraph *graph = (ListGraph *) malloc(sizeof(ListGraph));
    graph->vertexList = (Vertex *) malloc(sizeof(Vertex) * verNum); // vertex array
    graph->edgeList = (Edge *) malloc(sizeof(Edge));    // head of edgeList

    for (int i = 0; i < verNum-1; i++) {
        graph->vertexList[i].key = i + 1;
        graph->vertexList[i].next = &graph->vertexList[i + 1];

        graph->vertexList[i].head = (Incidence *) malloc(sizeof(Incidence));
        graph->vertexList[i].head->next = NULL;
    }
    graph->vertexList[verNum - 1].key = verNum;
    graph->vertexList[verNum-1].next = NULL;
    graph->vertexList[verNum - 1].head = (Incidence *) malloc(sizeof(Incidence));
    graph->vertexList[verNum - 1].head->next = NULL;
    return graph;
}

Edge *newEdge(ListGraph *graph, Vertex* start, Vertex* end){
    Edge *edge = (Edge *) malloc(sizeof(Edge));
    edge->a = start;
    edge->b = end;

    edge->next = graph->edgeList->next;
    graph->edgeList->next = edge->next;

    return edge;
}

Vertex *oppositeVertex(Vertex* vertex, Edge* e){
    if (vertex->key == e->a->key)
        return e->b;
    else
        return e->a;
}

void *addIncidence(Vertex* vertex, Edge* edge){
    int connectVertexKey;

    Incidence *incidence = (Incidence *) malloc(sizeof(Incidence));
    incidence->edge = edge;

    connectVertexKey = oppositeVertex(vertex, edge)->key;

    Incidence *cur, *prev;
    cur = vertex->head;
    prev = cur;

    while (cur->next != NULL) {
        cur = cur->next;
        if(connectVertexKey < oppositeVertex(vertex, cur->edge)->key) {
            break;
        }
        prev = cur;
    }
    incidence->next = cur;
    prev->next = incidence;
    // 0 3 5

    return incidence;
}

void insertEdge(ListGraph *graph, int a, int b){
    Vertex *start = &graph->vertexList[a - 1];
    Vertex *end = &graph->vertexList[b - 1];

    Edge *edge = newEdge(graph, start, end);
    addIncidence(start, edge);
    addIncidence(end, edge);
}


int main() {

    ListGraph *graph = initGraph(5, 7);

    insertEdge(graph, 1, 2);
    insertEdge(graph, 1, 3);


    return 0;
}