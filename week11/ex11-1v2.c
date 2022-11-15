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
    Vertex **vertexList;
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
int oppositeVertexKey(Vertex* vertex, Edge* edge){
    if(edge->a->key == vertex->key)
        return edge->b->key;
    else
        return edge->a->key;
}
void newIncidence(Vertex* vertex, Edge* edge){
    Incidence *incidence = (Incidence *) malloc(sizeof(Incidence));
    incidence->edge = edge;
    int oppositeKey = oppositeVertexKey(vertex, edge);

    Incidence *cur = vertex->head;
    while (cur->next != NULL) {
        if (oppositeVertexKey(vertex, cur->next->edge) > oppositeKey) {
            incidence->next = cur->next;
            cur->next = incidence;
            return;
        }
        cur = cur->next;
    }
    incidence->next = cur->next;
    cur->next = incidence;
}
ListGraph *initGraph(int verNum){
    ListGraph *graph = (ListGraph *) malloc(sizeof(ListGraph));

    graph->vertexList = (Vertex **) malloc(sizeof(Vertex *) * verNum);

    for (int i = 0; i < verNum; i++) {
        graph->vertexList[i] = newVertex(i + 1);
    }

    graph->edgeHead = (Edge *) malloc(sizeof(Edge));
    graph->edgeHead->next = NULL;

    return graph;
}
void addEdge(ListGraph* graph, int start, int end){
    Edge *edge = newEdge(graph, graph->vertexList[start - 1], graph->vertexList[end - 1]);

    newIncidence(graph->vertexList[start - 1], edge);
    newIncidence(graph->vertexList[end - 1], edge);
}

void DFS(ListGraph* graph, int start){
    if(graph->vertexList[start-1]->label == 1) {
        printf("%d\n", graph->vertexList[start - 1]->key);
        graph->vertexList[start - 1]->label = 0;

        Incidence *cur = graph->vertexList[start - 1]->head;
        while (cur->next != NULL) {
            cur = cur->next;
            DFS(graph, oppositeVertexKey(graph->vertexList[start - 1], cur->edge));
        }
    }
}
int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    ListGraph *graph = initGraph(n);
    for (int i = 0; i < m; i++) {
        int start, end;
        scanf("%d %d", &start, &end);

        addEdge(graph, start, end);
    }

    DFS(graph, s);
    return 0;
}
