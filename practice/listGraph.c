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
    AdjList* adj;
} Graph;

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

AdjListNode* newAdjListNode (int w) {
    AdjListNode* newNode = NULL;

    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = w;
    newNode->next = NULL;

    return newNode;
}

void addEdge (Graph* g, int v, int w) {
    AdjListNode* newNode=NULL;

    newNode = newAdjListNode(w);
    newNode->next = g->adj[v].head;
    g->adj[v].head = newNode;

    newNode = newAdjListNode(v);
    newNode->next = g->adj[w].head;
    g->adj[w].head = newNode;
}

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

int main (void) {
    Graph *g = NULL;

    g= createGraph(4);

    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,1,3);
    addEdge(g,2,3);

    printGraph(g);

    return 0;
}