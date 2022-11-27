#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0

int n,m;

typedef struct incidence Incidence;

typedef struct vertex {
    int data;
    Incidence *head;
} Vertex;

typedef struct edge{
    Vertex *u;
    Vertex *v;
    int weight;
    struct edge* next;
}Edge;

struct incidence {
    Edge *edge;
    Incidence *next;
};

typedef struct graphType {
    Vertex **verList;
    Edge *edgeHead;
} Graph;


/*    graph func     */
Vertex *newVertex(){
    Vertex *new = (Vertex *) malloc(sizeof(Vertex));

    new->head = (Incidence *) malloc(sizeof(Incidence));
    new->head->next = NULL;
    new->head->edge = NULL;

    return new;
}

Incidence* newIncidence(Vertex* vertex, Edge* edge){
    Incidence *new = (Incidence *) malloc(sizeof(Incidence));
    new->edge = edge;
    new->next = NULL;

    Incidence *cur = vertex->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = new;

    return new;
}

Edge *newEdge(Graph* graph, Vertex* u, Vertex* v, int weight){
    Edge *edge = (Edge *) malloc(sizeof(Edge));

    edge->u = u;
    edge->v = v;
    edge->weight = weight;
    edge->next = NULL;

    Edge *cur = graph->edgeHead;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = edge;

    return edge;
}

Graph *initGraph(){
    Graph *new = (Graph *) malloc(sizeof(Graph));
    new->edgeHead = (Edge *) malloc(sizeof(Edge));
    new->edgeHead->next = NULL;

    new->verList = (Vertex **) malloc(sizeof(Vertex *) * MAX_VERTICES);

    return new;
}

void addConnect(Graph* graph, Vertex* u, Vertex* v, int weight){
    Edge *new = newEdge(graph, u, v, weight);

    newIncidence(u, new);
    newIncidence(v, new);
}

Vertex *oppositeVertex(Vertex* u, Edge* edge){
    if(edge->u == u) return edge->v;
    else return edge->u;
}

Graph *buildGraph(){
    scanf("%d %d", &n, &m);

    Graph *graph = initGraph();

    for (int i = 0; i < n; i++) {
        graph->verList[i] = newVertex();
        graph->verList[i]->data = i + 1;
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addConnect(graph, graph->verList[u - 1], graph->verList[v - 1], w);
    }

    return graph;
}

/*             queue              */
typedef struct node{
    struct node *next;
    struct node *prev;
    Vertex *vertex;
}Node;

typedef struct queue {
    Node *head;
    Node *tail;
} Queue;

/*     queue func      */
Node* newNode(Vertex* vertex){
    Node *new = (Node *) malloc(sizeof(Node));
    new->vertex = vertex;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

Queue* initQueue(){
    Queue *new = (Queue *) malloc(sizeof(Queue));
    new->head = newNode(NULL);
    new->tail = newNode(NULL);
    new->head->next = new->tail;
    new->tail->prev = new->head;
    return new;
}

void enqueue(Queue* queue, Vertex* vertex){
    Node *node = newNode(vertex);
    node->next = queue->head->next;
    node->prev = queue->head;

    queue->head->next->prev = node;
    queue->head->next = node;
}

Vertex *removeMin(Queue* queue){

}

int main(){
    Graph *graph = buildGraph();

    Edge *cur = graph->edgeHead;
    while (cur->next != NULL) {
        cur = cur->next;
        printf("%d %d %d\n", cur->u->data, cur->v->data, cur->weight);
    }
    return 0;
}
