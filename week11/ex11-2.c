#include <stdio.h>
#include <stdlib.h>

typedef struct arrGraph {
    int **arr;
    int *label;
    int verNum;
} ArrGraph;

ArrGraph *initGraph(int n){
    ArrGraph *graph = (ArrGraph *) malloc(sizeof(ArrGraph));
    graph->arr = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        graph->arr[i] = (int *) malloc(sizeof(int) * n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            graph->arr[i][j] = 0;
    }
    graph->label = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        graph->label[i] = 0;


    graph->verNum = n;

    return graph;
}

void addIncidence(ArrGraph* graph, int start, int end){
    graph->arr[start - 1][end - 1] = 1;
    graph->arr[end - 1][start - 1] = 1;
}

void rprint(ArrGraph* graph, int s){
    if (graph->label[s - 1] == 0) {
        printf("%d\n", s);
        graph->label[s - 1] = 1;
    }

    for (int i = 0; i < graph->verNum; i++) {
        if (graph->arr[s - 1][i] == 1 && graph->label[i] == 0) {
            printf("%d\n", i + 1);
        }
    }

    for (int i = 0; i < graph->verNum; i++) {
        if (graph->arr[s - 1][i] == 1) {
            graph->label[i] = 1;
            rprint(graph, i + 1);
        }
    }
}

void print(ArrGraph* graph, int s){
    printf("%d\n", s);
    graph->label[s - 1] = 1;

    rprint(graph, s);
}


int main() {
    ArrGraph *graph = initGraph(6);

    for (int i = 0; i < 6; i++)
        printf("%d ", graph->label[i]);

   addIncidence(graph, 3, 5);
    addIncidence(graph, 1, 3);
    addIncidence(graph, 4, 1);
    addIncidence(graph, 2, 3);
    addIncidence(graph, 3, 4);
    addIncidence(graph, 6, 4);
    addIncidence(graph, 3, 6);
    addIncidence(graph, 1, 2);
    addIncidence(graph, 2, 5);

    print(graph, 1);

    for (int i = 0; i < 6; i++)
        printf("%d ", graph->label[i]);
=======
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
>>>>>>> f8704e2f3f8f600efee9a22aa5afe214bc89df31
    return 0;
}