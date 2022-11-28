#include <stdio.h>
#include <stdlib.h>
#define BIG_INT 10000

int n,m;

typedef struct graph {
    int **arr;
    int *dest;
} ArrGraph;

ArrGraph *initGraph(){
    scanf("%d %d", &n, &m);

    ArrGraph *graph = (ArrGraph *) malloc(sizeof(ArrGraph));

    graph->arr = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        graph->arr[i] = (int *) malloc(sizeof(int) * n);
    }

    graph->dest = (int *) malloc(sizeof(int) * n);

    graph->dest[0] = 0;
    for(int i = 1; i<n; i++)
        graph->dest[i] = BIG_INT;

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph->arr[u - 1][v - 1] = w;
        graph->arr[v - 1][u - 1] = w;
    }

    return graph;
}


typedef struct node{
    int data;
    int *key;
    struct node* next;
    struct node* prev;
}Node;

typedef struct queue {
    Node *head;
    Node *tail;
} Queue;

Queue *initQueue(){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->head = (Node *) malloc(sizeof(Node));
    queue->tail = (Node *) malloc(sizeof(Node));
    queue->head->next = queue->tail;
    queue->tail->prev = queue->head;
    queue->head->prev = NULL;
    queue->tail->next = NULL;

    return queue;
}
Node* getNode(){
    Node *node = (Node *) malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->key = NULL;

    return node;
}
void enqueue(Queue *queue, int v, int* key){
    Node *node = getNode();

    node->data = v;
    node->key = key;

    node->prev = queue->head;
    node->next = queue->head->next;

    queue->head->next->prev = node;
    queue->head->next = node;
}
Queue *buildQueue(ArrGraph* graph){
    Queue *queue = initQueue();

    for (int i = 0; i < n; i++)
        enqueue(queue, i + 1, &graph->dest[i]);

    return queue;
}
int isEmpty(Queue *queue){
    if(queue->head->next == queue->tail) return 1;
    else return 0;
}
int removeMin(Queue *queue){
    if(isEmpty(queue))
        return -1;

    Node* minNode = queue->head->next;
    Node *cur = queue->head->next;

    while (cur != queue->tail) {
         if(*cur->key < *minNode->key)
             minNode = cur;
        cur = cur->next;
    }

    minNode->prev->next = minNode->next;
    minNode->next->prev = minNode->prev;
    int result = minNode->data;

    free(minNode);

    return result;
}
int isContain(Queue *queue, int u){
    if(isEmpty(queue)) return 0;

    Node *cur = queue->head->next;
    while (cur != queue->tail) {
        if(cur->data == u) return 1;
        cur = cur->next;
    }
    return 0;
}
/*void replaceKey(Queue *queue, int u){
    if (isEmpty(queue)) {
        puts("replaceERROR");
        return;
    }
    Node *cur = queue->head->next;
    while (cur != queue->tail) {
        if(cur->data)
    }
}*/
void PrimJarnikMST(ArrGraph *graph){
    int MST[n];
    int idx = 0;

    Queue *queue = buildQueue(graph);

    while (!isEmpty(queue)) {
        int u = removeMin(queue);
        MST[idx++] = u;

        for (int i = 0; i < n; i++) {
            if(graph->arr[u-1][i] != 0) {
                if (isContain(queue, i + 1) && graph->arr[u - 1][i] < graph->dest[i]) {
                    graph->dest[i] = graph->arr[u - 1][i];
                }
            }
        }
    }

    for (int i = 0; i < idx; i++)
        printf(" %d", MST[i]);
    puts("");
}

int main() {
    ArrGraph *graph = initGraph();

    PrimJarnikMST(graph);

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += graph->dest[i];
    printf("%d", sum);
    return 0;
}


/*
 * 5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6*/