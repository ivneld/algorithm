#include <stdio.h>
#include <stdlib.h>

typedef struct incidence Incidence;

typedef struct vertex{
    int key;
    Incidence *head;
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

typedef struct listGraph {
    Vertex *vertexList;
    Edge *edgeHead;
} ListGraph;

Vertex *newVertex(int key){
    Vertex *vertex = (Vertex *) malloc(sizeof(Vertex));
    vertex->key = key;
    vertex->label = 1;  // before visit
    vertex->head = (Incidence *) malloc(sizeof(Incidence));
    vertex->head->edge = NULL;
    vertex->head->next = NULL;
    return vertex;
}
Edge* newEdge(ListGraph *graph, Vertex* start, Vertex* end){
    Edge *edge = (Edge *) malloc(sizeof(Edge));
    edge->a = start;
    edge->b = end;

    edge->next = graph->edgeHead->next;
    graph->edgeHead->next = edge;
    return edge;
}
ListGraph *initGraph(int verNum){
    ListGraph *graph = (ListGraph *) malloc(sizeof(ListGraph));

    graph->vertexList = (Vertex *) malloc(sizeof(Vertex) * verNum);

    for (int i = 0; i < verNum; i++) {
        graph->vertexList[i].key = i + 1;
        graph->vertexList[i].head = (Incidence *) malloc(sizeof(Incidence));
        graph->vertexList[i].label = 1;
    }

    graph->edgeHead = (Edge *) malloc(sizeof(Edge));

    return graph;
}
int oppositeVertexKey(Vertex* vertex, Edge* edge){
    if(edge->a->key == vertex->key)
        return edge->b->key;
    else
        return edge->a->key;
}
void addIncidence(Vertex* vertex, Edge* edge){
    Incidence *incidence = (Incidence *) malloc(sizeof(Incidence));
    incidence->edge = edge;

    Incidence *cur = vertex->head;
    if(cur->next == NULL) {
        incidence->next = cur->next;
        cur->next = incidence;
        return;
    }

    while (cur->next != NULL) {
        Incidence *prev = cur;
        cur = cur->next;
        if (oppositeVertexKey(vertex, edge) < oppositeVertexKey(vertex, cur->edge)) {
            incidence->next = cur;
            prev->next = incidence;
            break;
        }
    }
    incidence->next = cur->next;
    cur->next = incidence;
}
void addEdge(ListGraph* graph, int start, int end){
    Edge *edge = newEdge(graph, &graph->vertexList[start - 1], &graph->vertexList[end - 1]);

    addIncidence(&graph->vertexList[start - 1], edge);
    addIncidence(&graph->vertexList[end - 1], edge);

}
int main() {
    ListGraph *graph = initGraph(5);

    addEdge(graph, 1, 2);
    return 0;
}