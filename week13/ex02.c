#include <stdio.h>
#include <stdlib.h>

int n, m;

typedef struct graph {
    int **arr;
    int **sack;
    int *sackSize;
    int verNum;
} ArrGraph;


typedef struct node {
    int u;
    int v;
    int w;
    struct node* next;
    struct node* prev;
}Node;

typedef struct queue {
    Node* head;
    Node* tail;
}Queue;

Node* getNode() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    return node;
}
Queue* initQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->head = getNode();
    queue->tail = getNode();
    queue->head->next = queue->tail;
    queue->tail->prev = queue->head;

    return queue;
}
int isEmpty(Queue *queue) {
    if (queue->head->next == queue->tail) return 1;
    else return 0;
}
Node* removeMin(Queue* queue) {
    if (isEmpty(queue)) return NULL;

    Node *minNode = queue->head->next;
    Node *cur = queue->head->next;
    while (cur != queue->tail) {
        if (cur->w < minNode->w)
            minNode = cur;
        cur = cur->next;
    }
    minNode->prev->next = minNode->next;
    minNode->next->prev = minNode->prev;

    return minNode;
}
void enqueue(Queue* queue, int u, int v, int w) {
    Node *node = getNode();
    node->u = u;
    node->v = v;
    node->w = w;

    node->prev = queue->head;
    node->next = queue->head->next;
    queue->head->next->prev = node;
    queue->head->next = node;
}


ArrGraph *initGraph(Queue* queue) {
    scanf("%d %d", &n, &m);

    ArrGraph *graph = (ArrGraph *)malloc(sizeof(ArrGraph));
    graph->verNum = n;

    graph->arr = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        graph->arr[i] = (int *)malloc(sizeof(int) * n);
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph->arr[u - 1][v - 1] = w;
        graph->arr[v - 1][u - 1] = w;
        enqueue(queue, u, v, w);
    }

    graph->sack = (int **)malloc(sizeof(int *) * n);
    graph->sackSize = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        graph->sack[i] = (int *)malloc(sizeof(int) * n);
        graph->sack[i][0] = i + 1;
        graph->sackSize[i] = 1;
    }

    return graph;
}

int isSameSack(ArrGraph *graph, int u, int v) {
    if (graph->sack[u - 1] == graph->sack[v - 1])
        return 1;
    else
        return 0;
}

void mergeSack(ArrGraph* graph, int u, int v) {
    int idx = graph->sackSize[u - 1];

    for (int i = 0; i < graph->sackSize[v - 1]; i++) {
        graph->sack[u - 1][idx++] = graph->sack[v - 1][i];
    }


    for (int i = 0; i < idx; i++) {
        int vertexNum = graph->sack[u - 1][i];
        graph->sack[vertexNum - 1] = graph->sack[u - 1];
        graph->sackSize[vertexNum - 1] = idx;
    }

    /*printf("size : ");
    for (int i = 0; i < n; i++)
        printf("%d ", graph->sackSize[i]);
    puts("");*/
}
void Kruskal(ArrGraph *arrGraph, Queue *queue) {
    int size = arrGraph->verNum - 1;

    int *list = (int*)malloc(sizeof(int)*size);

    int idx = 0;

    while(!isEmpty(queue)) {
        Node *node = removeMin(queue);
        if (!isSameSack(arrGraph, node->u, node->v)) {
            list[idx++] = node->w;
            mergeSack(arrGraph, node->u, node->v);
        }
    }


    int sum = 0;
    for (int i = 0; i < idx; i++) {
        printf(" %d", list[i]);
        sum += list[i];
    }
    puts("");
    printf("%d", sum);
}

int main() {
    Queue *queue = initQueue();
    ArrGraph *arrGraph = initGraph(queue);

    Kruskal(arrGraph, queue);


    return 0;
}