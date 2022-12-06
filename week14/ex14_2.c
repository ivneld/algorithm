#include <stdio.h>
#include <stdlib.h>
#define BIG_INT 10000

int n, m, s;

typedef struct edge {
    int u;
    int v;
    int w;
} Edge;

typedef struct graph {
    int **arr;
    int *label;
    Edge* edgeList;
} ArrayGraph;

int Min(int a, int b){
    return a > b ? b : a;
}
ArrayGraph *initGraph(){
    ArrayGraph *arrayGraph = (ArrayGraph *) malloc(sizeof(ArrayGraph));
    arrayGraph->label = (int *) malloc(sizeof(int) * n);
    arrayGraph->edgeList = (Edge *) malloc(sizeof(Edge) * m);

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
        graph->edgeList[i].u = u;
        graph->edgeList[i].v = v;
        graph->edgeList[i].w = w;
    }

    return graph;
}
int* initResultArray(){
    int* result = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        result[i] = BIG_INT;
    
    return result;
}
void BellmanFordShortestPaths(ArrayGraph* graph){
    int *result = initResultArray();

    result[s - 1] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (result[graph->edgeList[j].u - 1] == BIG_INT)
                continue;
            if(result[graph->edgeList[j].v - 1] > result[graph->edgeList[j].u - 1] + graph->edgeList[j].w)
                result[graph->edgeList[j].v - 1] = result[graph->edgeList[j].u - 1] + graph->edgeList[j].w;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s != i + 1 && result[i] != BIG_INT) {
            printf("%d %d\n", i + 1, result[i]);
        }
    }
}

int main() {
    ArrayGraph *graph = buildGraph();

    BellmanFordShortestPaths(graph);

    return 0;
}