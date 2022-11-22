#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0

int n; //verNum

typedef struct incidence Incidence;

typedef struct vertex {
    char data;
    Incidence *head;
    int degree;
} Vertex;

typedef struct edge{
    Vertex *start;
    Vertex *end;
    struct edge* next;
}Edge;

struct incidence {
    Edge *edge;
    Incidence *next;
};

typedef struct graphType {
    Vertex **verList;
    Edge *edgeHead;
} Digraph;

typedef struct node{
    Vertex *vertex;
    struct node *next;
    struct node *prev;
}Node;

typedef struct queue{
    Node *head;     //in
    Node *tail;     //out
}Queue;

/* graph func*/
Vertex *newVertex(char data){
    Vertex *new = (Vertex *) calloc(1, sizeof(Vertex));
    new->data = data;
    new->head = (Incidence *) malloc(sizeof(Incidence));
    new->head->edge = NULL;
    new->head->next = NULL;

    return new;
}

Edge *newEdge(Digraph *graph, Vertex *start, Vertex *end){
    Edge *new = (Edge *) malloc(sizeof(Edge));
    new->start = start;
    new->end = end;

    new->next = graph->edgeHead->next;
    graph->edgeHead->next = new;

    return new;
}

void *newIncidence(Vertex* vertex, Edge* edge){
    Incidence *new = (Incidence *) malloc(sizeof(Incidence));
    new->edge = edge;

    new->next = vertex->head->next;
    vertex->head->next = new;
}

Digraph *initGraph(){
    Digraph *new = (Digraph *) malloc(sizeof(Digraph));
    new->edgeHead = (Edge *) malloc(sizeof(Edge));
    new->edgeHead->next = NULL;

    new->verList = (Vertex **) malloc(sizeof(Vertex *) * MAX_VERTICES);

    return new;
}

Digraph *buildGraph(){
    scanf("%d", &n);
    getchar();

    Digraph *new = initGraph();

    char data;
    for (int i = 0; i < n; i++) {
        scanf("%c", &data);
        new->verList[i] = newVertex(data);
        getchar();
    }

    return new;
}

int index(Digraph * graph, char data){
    for (int i = 0; i < n; i++) {
        if (graph->verList[i]->data == data)
            return i;
    }
    return -1;
}

void addEdge(Digraph* graph, char start, char end){
    int u = index(graph, start);
    int w = index(graph, end);

    Vertex *s = graph->verList[u];
    Vertex *e = graph->verList[w];

    Edge *new = newEdge(graph, s, e);

    newIncidence(s, new);
    e->degree++;
}

/* queue func*/

Queue *initQueue(){
    Queue *new = (Queue *) malloc(sizeof(Queue));

    new->head = (Node *) malloc(sizeof(Node));
    new->tail = (Node *) malloc(sizeof(Node));

    new->head->next = new->tail;
    new->head->prev = new->head;
    new->tail->prev = new->head;
    new->tail->next = new->tail;

    return new;
}
int isEmpty(Queue* queue){
    if(queue->head->next == queue->tail)
        return TRUE;
    else
        return FALSE;
}
void enqueue(Queue* queue, Vertex* vertex){
    Node *new = (Node *) malloc(sizeof(Node));
    new->vertex = vertex;

    new->next = queue->head->next;
    new->prev = queue->head;
    queue->head->next->prev = new;
    queue->head->next = new;
}
Vertex *dequeue(Queue* queue){
    Node *cur = queue->tail->prev;

    cur->prev->next = queue->tail;
    queue->tail->prev = cur->prev;

    return cur->vertex;
}

void topologicalSort(Digraph* digraph){
    Queue *queue = initQueue();
    char *list = (char *) malloc(sizeof(char) * n);
    int idx = 0;

    for (int i = 0; i < n; i++) {
        if(digraph->verList[i]->degree == 0)
            enqueue(queue, digraph->verList[i]);
    }

    int i = 1;
    while (!isEmpty(queue)) {
        Vertex *u = dequeue(queue);
        list[idx++] = u->data;
        i++;

        Incidence *cur = u->head;
        while (cur->next != NULL) {
            cur = cur->next;
            --cur->edge->end->degree;
            if(cur->edge->end->degree == 0)
                enqueue(queue, cur->edge->end);
        }
    }

    if(i <= n)
        puts("0");
    else {
        for (int j = 0; j < idx; j++)
            printf("%c ", list[j]);
    }
}

int main() {
    Digraph *digraph = buildGraph();

    int m;
    scanf("%d", &m);
    getchar();

    char start,end;
    for (int i = 0; i < m; i++) {
        scanf("%c %c", &start, &end);
        getchar();
        addEdge(digraph, start, end);
    }

    /*for (int i = 0; i < n; i++) {
        printf("%c %d\n", digraph->verList[i]->data, digraph->verList[i]->degree);
    }*/

    topologicalSort(digraph);

    return 0;
}