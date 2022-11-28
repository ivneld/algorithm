#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define BIG_INT 10000

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

Incidence **parent;
int *dest;


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

    dest = (int *) malloc(sizeof(int) * n);
    parent = (Incidence **) malloc(sizeof(Incidence *) * m);

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

Queue *enqueue(Queue* queue, Vertex* vertex){
    Node *node = newNode(vertex);
    node->vertex = vertex;
    node->prev = queue->head;
    node->next = queue->head->next;

    queue->head->next->prev = node;
    queue->head->next = node;

    return queue;
}

Vertex *removeMin(Queue* queue){

    Node *result = queue->head;
    int min = BIG_INT;

    Node *cur = queue->head->next;
    while (cur != queue->tail) {
        if(cur->vertex->data < min) {
            min = cur->vertex->data;
            result = cur;
        }
        cur = cur->next;
    }

    result->next->prev = result->prev;
    result->prev->next = result->next;

    return result->vertex;
}

int isEmpty(Queue *queue){

    if (queue->head->next == queue->tail) {
        return 1;
    }
    else return 0;
}

void replaceKey(Queue *queue, Vertex* z, int d){
    Node *cur = queue->head->next;

    while (cur != queue->tail) {
        if (cur->vertex == z) {
            int idx = cur->vertex->data - 1;
            dest[idx] = d;
            return;
        }
        cur = cur->next;
    }
}

int isContain(Queue *queue, Vertex* vertex){
    Node* cur=queue->head;

    while (cur != queue->tail) {
        cur = cur->next;
        if(cur->vertex == vertex) return 1;
    }
    return 0;
}


int* Prim_JarnikMST(Graph* graph){
    int *list = (int *) malloc(sizeof(int) * n);
    int idx = 0;

    for (int i = 0; i < n; i++) {
        dest[i] = BIG_INT;
        parent[i] = NULL;
    }

    dest[0] = 0;
    list[idx++] = 1;
    Queue *queue = initQueue();

    for (int i = 0; i < n; i++) {
        enqueue(queue, graph->verList[i]);
    }

    while (!isEmpty(queue)) {
        Vertex *u = removeMin(queue);
        int x = u->data;

        Incidence *e = u->head->next;
        while (e != NULL) {
            Vertex *z = oppositeVertex(u, e->edge);

            int w = e->edge->weight;
            int data = dest[z->data - 1];

            if (e->edge->weight < dest[z->data - 1]) {
                dest[z->data - 1] = e->edge->weight;
                replaceKey(queue, z, e->edge->weight);
                list[idx++] = z->data;
            }
            e = e->next;
        }
    }

    return list;
}

int main(){
    Graph *graph = buildGraph();

    int *list = Prim_JarnikMST(graph);

    int sum = 0;

    for (int i = 0; i < n; i++) {
        printf(" %d", list[i]);
        sum += dest[i];
    }
    printf("\n%d", sum);

    return 0;
}

/*5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6*/