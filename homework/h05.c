#include <stdio.h>
#include <stdlib.h>
#define INF 10000       // 초기 최단거리 값


/* 인접리스트 그래프와 함수 */
typedef struct incidence Incidence;

typedef struct vertices {
    char data;
    int dest;       // 각 정점에 이르는 최단 거리
    int cnt;        // 각 정점에 이르는 최단 경로의 수
    int label;      // 큐에 들어가 있는 정점인지 확인하기 위한 변수
    Incidence *head;    // 정점이 연결되어 있는 edge List (단일 연결 리스트로 구현)
} Vertices;

typedef struct edge {
    Vertices *u, *v;
    int weight;
} Edge;

struct incidence{
    Edge* edge;
    Incidence *next;
};

typedef struct graph{
    int verNum;     // 정점의 개수를 저장하기 위한 변수
    int edgeNum;
    Vertices **verList;     // 정점 포인터 배열
}ListGraph;

// 새로운 연결을 만드는 함수
void insertConnect(Vertices *u, Vertices* v, int weight){
    // 각 정점의 Incidence 리스트에 저장할 edge를 새로 만듬
    Edge *new = (Edge *) malloc(sizeof(Edge));
    new->u = u;
    new->v = v;
    new->weight = weight;

    // 각 정점의 Incidence 리스트에 새로 만든 edge 추가
    Incidence *uIn = (Incidence *) malloc(sizeof(Incidence));
    Incidence *vIn = (Incidence *) malloc(sizeof(Incidence));

    uIn->edge = new;
    uIn->next = u->head->next;
    u->head->next = uIn;

    vIn->edge = new;
    vIn->next = v->head->next;
    v->head->next = vIn;
}

// 정점의 data는 정점배열 0번 부터 verNum -1 까지 문자 'A' 부터 'A' + verNum - 1 로 저장 함으로
// 알파벳 순으로 정점을 배열에 저장하고 있다.
ListGraph *initGraph(int verNum, int edgeNum){
    ListGraph *graph = (ListGraph *) malloc(sizeof(ListGraph));
    graph->verNum = verNum;
    graph->edgeNum = edgeNum;

    graph->verList = (Vertices **) malloc(sizeof(Vertices *) * verNum);
    for (int i = 0; i < verNum; i++) {
        graph->verList[i] = (Vertices *) malloc(sizeof(Vertices));
        graph->verList[i]->head = (Incidence *) malloc(sizeof(Incidence));
        graph->verList[i]->head->next = NULL;
        graph->verList[i]->data = 65 + i;
        graph->verList[i]->label = 0;
    }

    insertConnect(graph->verList[0], graph->verList[1], 8);
    insertConnect(graph->verList[0], graph->verList[2], 1);
    insertConnect(graph->verList[0], graph->verList[3], 4);
    insertConnect(graph->verList[1], graph->verList[2], 7);
    insertConnect(graph->verList[1], graph->verList[4], 4);
    insertConnect(graph->verList[2], graph->verList[4], 3);
    insertConnect(graph->verList[2], graph->verList[5], 9);
    insertConnect(graph->verList[2], graph->verList[3], 5);
    insertConnect(graph->verList[3], graph->verList[5], 4);

    return graph;
}

// edge에서 정점 u 가 아닌 반대편의 정점을 반환 하는 함수
Vertices *oppositeVertices(Vertices* u, Edge* edge){
    if(edge->u == u)
        return edge->v;
    else
        return edge->u;
}



/* 알고리즘에서 사용될 큐와 함수*/

// 큐에 들어갈 노드는 vertices를 저장한다
typedef struct node{
    Vertices *vertices;
    struct node* next;
    struct node* prev;
}Node;

typedef struct queue {
    Node *head;
    Node *tail;
} Queue;

// 큐 초기화 함수
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

// 큐에 새로운 vertices를 저장하는 함수
void enqueue(Queue* queue, Vertices* vertices){
    Node *node = (Node *) malloc(sizeof(Node));
    node->vertices = vertices;
    vertices->label = 1;

    node->prev = queue->head;
    node->next = queue->head->next;
    queue->head->next->prev = node;
    queue->head->next = node;
}

// 큐가 비어 있는지 확인하는 함수
int isEmpty(Queue *queue){
    if(queue->head->next == queue->tail)
        return 1;
    else
        return 0;
}

// 큐에 저장되어 있는 노드 중 vertices의 dest(최단 거리) 가 가장 작은 노드를 삭제하고 vertices 를 반환하는 함수
Vertices* removeMin(Queue* queue){
    Node *cur = queue->head->next;
    Node *node = cur;
    Vertices *result = node->vertices;
    int min = cur->vertices->dest;

    while (cur != queue->tail) {
        if (min > cur->vertices->dest) {
            min = cur->vertices->dest;
            result = cur->vertices;
            node = cur;
        }
        cur = cur->next;
    }
    node->next->prev = node->prev;
    node->prev->next = node->next;

    free(node);
    result->label = 0;

    return result;
}

// 알고리즘을 수행하기 위해 그래프의 초기 상태를 구성하는 함수
void initSetting(ListGraph* graph, Queue* queue, int s){
    for (int i = 0; i < graph->verNum; i++) {
        graph->verList[i]->dest = INF;
        graph->verList[i]->cnt = 0;
        graph->verList[i]->label = 0;
    }

    // 기준이 되는 노드의 최단 거리는 0, 최단 경로의 수는 1로 변경
    graph->verList[s]->dest = 0;
    graph->verList[s]->cnt = 1;

    // 모든 노드를 큐에 저장
    for (int i = 0; i < graph->verNum; i++) {
        enqueue(queue, graph->verList[i]);
    }
}

void Dijkstra(ListGraph* graph, int s, int e){

    Queue *queue = initQueue();     // 큐 생성

    initSetting(graph, queue, s);   // 초기값 구성


    while (!isEmpty(queue)) {
        Vertices *u = removeMin(queue);     // 현재 큐에서 거리가 가장 작은 정점
        Incidence* cur = u->head;

        // u가 연결된 정점들을 모두 방문
        while(cur->next != NULL){
            cur = cur->next;
            Vertices *v = oppositeVertices(u, cur->edge);   // 연결된 정점

            // 새로 측정한 최단 거리가 기존의 거리와 같다면
            // 같은 최단 거리 이므로 최단 경로의 수에 정점 u에 도달 하기 위한 최단 경로의 수를 더해 줌.
            if(u->dest + cur->edge->weight == v->dest)
                v->cnt = v->cnt + u->cnt;

            // 새로운 최단 거리를 발견
            // 최단 거리를 갱신 해 주고, 정점 u에 도달 하기 위한 최단 경로의 수로 갱신.
            else if(v->label == 1 && u->dest + cur->edge->weight < v->dest){
                v->dest = u->dest + cur->edge->weight;

                v->cnt = u->cnt;
            }
        }

        // 따라서 최단 경로가 아니라면 새로운 최단 경로의 수로 계속 갱신이 되고
        // 최단 경로를 찾았고, 같은 최단 거리라 판단하면 최단 경로의 수를 추가 함.
    }

    printf("%c, %c : 최단거리 = %d, 최단경로 수 = %d\n", graph->verList[s]->data, graph->verList[e]->data,
           graph->verList[e]->dest, graph->verList[e]->cnt);
}

int main(){
    ListGraph *graph = initGraph(6, 9);

    Dijkstra(graph, 2, 0);
    Dijkstra(graph, 2, 5);
    Dijkstra(graph, 5, 2);
    Dijkstra(graph, 1, 3);

    return 0;
}


