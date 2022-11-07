#include <stdio.h>
#include <stdlib.h>

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};
typedef struct AdjListNode AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int vertexNumber;
    AdjList* adj; // 인접한 정점을 저장하기 위한 공간
} Graph;

// n개의 정점을 가진 Grpah를 만든다간
Graph* createGraph(int n) {
    int i = 0;
    Graph *G = NULL;
    G = (Graph*)malloc(sizeof(Graph));

    G->vertexNumber = n;
    G->adj = (AdjList*)malloc(sizeof(AdjList) * n);
    for (i=0; i < n; i++) {
        G->adj[i].head = NULL;
    }
    return G;
}

// 새로운 인접 리스트 노드를 생성한다.
AdjListNode* newAdjListNode (int w) {
    AdjListNode* newNode = NULL;

    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = w;
    newNode->next = NULL;

    return newNode;
}

// 무방향그래프에 대한 새로운 간선을 추가한다.
void addEdge (Graph* g, int v, int w) {
    AdjListNode* newNode=NULL;

    newNode = newAdjListNode(w);
    newNode->next = g->adj[v].head;
    g->adj[v].head = newNode;

    newNode = newAdjListNode(v);
    newNode->next = g->adj[w].head;
    g->adj[w].head = newNode;
}

// Graph를 출력한다.
void printGraph (Graph* g) {
    int i = 0;
    AdjListNode* temp = NULL;

    for (i=0; i<g->vertexNumber; i++) {
        temp = g->adj[i].head;
        printf("V[%d] ", i);
        while (temp) {
            printf("-> %d ", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

void main (void) {
    Graph *g = NULL;

    g= createGraph(4);

    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,1,3);
    addEdge(g,2,3);

    printGraph(g);

}