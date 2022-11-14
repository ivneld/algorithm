#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int vertexNumber;
    int** adj; // 2차원 배열을 저장하기 위한 공간
} Graph;

// n개의 정점을 가진 Grpah를 만든다.
Graph* createGraph(int n) {
    int i,j = 0;
    Graph *G = NULL;
    G = (Graph*)malloc(sizeof(Graph));

    G->vertexNumber = n;
    G->adj = malloc(sizeof(int*) * n);

    for (i = 0; i < n; i++) {
        G->adj[i] = malloc(sizeof(int) * n);
    }

// 그래프 초기화
    for (i=0; i < n; i++) {
        for (j=0; j < n; j++) {
            G->adj[i][j] = 0;
        }
    }
    return G;
}

// 무방향그래프에 대한 새로운 간선을 추가한다.
void addEdge (Graph* g, int v, int w) {
    g->adj[v][w] = 1;
    g->adj[w][v] = 1;
}

void printGraph (Graph* g) {
    int i,j = 0;

    for (i=0; i < g->vertexNumber; i++) {
        for (j=0; j < g->vertexNumber; j++) {
            printf("%d ", g->adj[i][j]);
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