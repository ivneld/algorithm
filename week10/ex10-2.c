#include <stdio.h>
#include <stdlib.h>
#define NODENUM 6

typedef struct Graph{
    int Map[NODENUM][NODENUM];
}Graph;

Graph *init() {
    Graph *new = (Graph *) malloc(sizeof(Graph));

    new->Map[0][1] = 1;
    new->Map[0][2] = 1;
    new->Map[0][3] = 1;
    new->Map[0][5] = 2;
    new->Map[1][2] = 1;
    new->Map[2][4] = 4;
    new->Map[4][4] = 4;
    new->Map[4][5] = 3;

    new->Map[1][0] =1;
    new->Map[2][0] =1;
    new->Map[3][0] =1;
    new->Map[5][0] =2;
    new->Map[2][1] =1;
    new->Map[4][2] =4;
    new->Map[5][4] =3;
    return new;
}
void print(Graph* graph, int num){
    if (num > NODENUM) {
        puts("-1");
        return;
    }
    for (int i = 0; i < NODENUM; i++) {
        if(graph->Map[num-1][i] != 0) {
            printf(" %d %d", i+1, graph->Map[num - 1][i]);
        }
    }
    puts("");
}
void editGraph(Graph* graph, int a, int b , int m){
    if (a > NODENUM || b > NODENUM) {
        puts("-1");
        return;
    }

    graph->Map[a - 1][b - 1] = m;
    graph->Map[b - 1][a - 1] = m;
}

int main() {
    Graph *graph = init();

    char cmd;
    int a, b, w;

    while(1) {
        scanf("%c", &cmd);

        switch (cmd) {
            case 'a':
                scanf("%d", &a);
                print(graph, a);
                break;
            case 'm':
                scanf("%d %d %d", &a, &b, &w);
                editGraph(graph, a, b, w);
                break;
            case 'q':
                return -1;
            default:
                break;
        }
        getchar();
    }
    return 0;
}