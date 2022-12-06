#include <stdio.h>
#include <stdlib.h>
#define BIG_INT 10000

int n, m, s;
int *result;

typedef struct graph {
    int **arr;
    int *label;
} ArrayGraph;

ArrayGraph *initGraph(){
    ArrayGraph *arrayGraph = (ArrayGraph *) malloc(sizeof(ArrayGraph));
    arrayGraph->label = (int *) malloc(sizeof(int) * n);

    arrayGraph->arr = (int **) malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++) {
        arrayGraph->arr[i] = (int *) malloc(sizeof(int) * n);
    }


    return arrayGraph;
}
ArrayGraph *buildGraph(){
    scanf("%d %d %d", &n, &m, &s);

    ArrayGraph *graph = initGraph();

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph->arr[u - 1][v - 1] = w;
        graph->arr[v - 1][u - 1] = w;
    }

    return graph;
}



typedef struct node{
    int idx;
    struct node* prev;
    struct node* next;
}Node;

typedef struct queue {
    Node *head;
    Node *tail;
} Queue;

Node* getNode(){
    Node *node = (Node *) malloc(sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    return node;
}
Queue* initQueue(){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->head = (Node *) malloc(sizeof(Node));
    queue->tail = (Node *) malloc(sizeof(Node));

    queue->head->prev = NULL;
    queue->head->next = queue->tail;
    queue->tail->next = NULL;
    queue->tail->prev = queue->head;

    return queue;
}
int isEmpty(Queue* queue){
    if(queue->head->next == queue->tail) return 1;
    else return 0;
}
void enqueue(Queue *queue, int data) {
    Node *new = getNode();
    new->idx = data;

    new->next = queue->head->next;
    new->prev = queue->head;
    queue->head->next->prev = new;
    queue->head->next = new;
}
Node* dequeue(Queue *queue){
    if (isEmpty(queue)) return NULL;

    Node *node = queue->tail->prev;

    queue->tail->prev = queue->tail->prev->prev;
    queue->tail->prev->next = queue->tail;

    return node;
}
Node* removeMin(Queue *queue){
    if (isEmpty(queue)) return NULL;

    int min = result[queue->head->next->idx];
    Node *node = queue->head->next;

    Node* cur = queue->head;
    while (cur->next != queue->tail) {
        cur = cur->next;
        if(min > result[cur->idx]){
            min = result[cur->idx];
            node = cur;
        }
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;

    return node;
}
void Dijkstra(ArrayGraph* graph){
    Queue *queue = initQueue();

    result = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        result[i] = BIG_INT;
    result[s-1] = 0;
    graph->label[s - 1] = 1;

    for(int i = 0; i<n; i++){
        if (graph->arr[s - 1][i] != 0) {
            result[i] = graph->arr[s - 1][i];
            enqueue(queue, i);
            graph->label[i] = 1;
        }
    }

    while (!isEmpty(queue)) {
        Node *node = removeMin(queue);
        int idx = node->idx;

        for(int i = 0; i<n; i++){
            int weight;
            if(graph->arr[idx][i] != 0) weight = graph->arr[idx][i];
            else weight = BIG_INT;

            int cost = result[idx] + weight;
            if(result[i] > cost)
                result[i] = cost;

            if(graph->label[i] == 0) {
                enqueue(queue, i);
                graph->label[i] = 1;
            }
        }
    }
   /* for (int i = 0; i < n; i++) {
        for (int idx = 0; idx < n; idx++) {
            int weight;
            if(graph->arr[i][idx] == 0) weight = BIG_INT;
            else weight = graph->arr[i][idx];

            int cost = result[i] + weight;
            if(result[idx] > cost)
                result[idx] = cost;
        }
    }*/
}

int main() {
    ArrayGraph *graph = buildGraph();

    Dijkstra(graph);

    for (int i = 0; i < n; i++) {
        if(s != i + 1 && result[i] != BIG_INT)
            printf("%d %d\n", i + 1, result[i]);
    }
    return 0;
}