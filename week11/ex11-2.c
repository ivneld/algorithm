#include <stdio.h>
#include <stdlib.h>

typedef struct arrGraph {
    int **arr;
    int *label;
} ArrayGraph;

ArrayGraph *initGraph(int verNum){
    ArrayGraph *graph = (ArrayGraph *) malloc(sizeof(ArrayGraph));

    graph->arr = (int **) malloc(sizeof(int *) * verNum);
    for (int i = 0; i < verNum; i++) {
        graph->arr[i] = (int *) malloc(sizeof(int) * verNum);
    }

    graph->label = (int *) malloc(sizeof(int) * verNum);
    for (int i = 0; i < verNum; i++)
        graph->label[i] = 1;

    return graph;
}
void addEdge(ArrayGraph* graph, int start, int end){
    graph->arr[start - 1][end - 1] = 1;
    graph->arr[end - 1][start - 1] = 1;
}
void BFS(ArrayGraph* graph, int verNum, int start){
    if(graph->label[start-1]==1)
        printf("%d\n", start);

    for (int i = 0; i < verNum; i++) {
        if(graph->arr[start-1][i] == 1 && graph->label[i] == 1)
            printf("%d\n", i + 1);
    }

    graph->label[start - 1] = 0;
    for (int i = 0; i < verNum; i++) {
        if(graph->arr[start-1][i] == 1 && graph->label[i] == 1) {
            graph->label[i] = 0;
            
        }
    }
}
int main() {
    ArrayGraph *graph = initGraph(6);

    addEdge(graph, 3, 5);
    addEdge(graph, 1, 3);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 6, 4);
    addEdge(graph, 3, 6);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 5);


    BFS(graph, 6, 1);
    return 0;
}