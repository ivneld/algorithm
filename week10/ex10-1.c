#include <stdio.h>
#include <stdlib.h>
#define VERTICESNUM 6
#define EDGESNUM 21
typedef struct incidence INCIDENCE;

typedef struct vertices{
    int data;
    INCIDENCE *head;
    struct vertices* next;
    int inSize;         // connect incidence size
}VERTICES;

typedef struct edges{
    int weight;
    VERTICES *start;
    VERTICES *end;
    struct edges* next;
}EDGES;

struct incidence{
    EDGES *edge;
    struct incidence* next;
};

typedef struct graph{
    VERTICES *verList;
    EDGES *edgeList;
    int edgNum;
}GRAPH;

INCIDENCE *newIncidence(EDGES* edges){
    INCIDENCE *new = (INCIDENCE *) malloc(sizeof(INCIDENCE));
    new->edge = edges;
    new->next = NULL;

    return new;
}

VERTICES *newVertices(int data){
    VERTICES *new = (VERTICES *) malloc(sizeof(VERTICES));
    new->data = data;
    new->head = newIncidence(NULL);
    new->next = NULL;
    new->inSize = 0;

    return new;
}

EDGES *newEdges(int weight, VERTICES *start, VERTICES *end){
    EDGES *new = (EDGES *) malloc(sizeof(EDGES));
    new->weight = weight;
    new->start = start;
    new->end = end;
    new->next = NULL;
    return new;
}

void newConnect(GRAPH *graph, int weight, VERTICES *start, VERTICES* end){
    if(graph->edgNum >= EDGESNUM)
        return;

    EDGES *ne = newEdges(weight, start, end);
    EDGES *cur = graph->edgeList;   // list head node
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = ne;

    INCIDENCE *startIp = start->head;
    while (startIp->next != NULL) {
        startIp = startIp->next;
    }
    INCIDENCE *new = newIncidence(ne);
    startIp->next = new;
    start->inSize++;

    if(start != end) {
        INCIDENCE *endIp = end->head;
        while (endIp->next != NULL) {
            endIp = endIp->next;
        }
        new = newIncidence(ne);
        endIp->next = new;
        end->inSize++;
    }
}

GRAPH *initGraph(){
    GRAPH *new = (GRAPH *) malloc(sizeof(GRAPH));
    new->edgNum = 0;
    new->edgeList = newEdges(0, NULL, NULL);    //edge list head node create
    new->verList = newVertices(0);

    VERTICES *cur = new->verList;

    VERTICES *list[VERTICESNUM];
    for (int i = 1; i <= VERTICESNUM; i++) {
        VERTICES *nv = newVertices(i);
        cur->next = nv;
        cur = cur->next;
        list[i - 1] = nv;
    }

    newConnect(new, 1, list[0], list[1]);
    newConnect(new, 2, list[0], list[5]);
    newConnect(new, 1, list[0], list[2]);
    newConnect(new, 1, list[0], list[3]);

    newConnect(new, 1, list[1], list[2]);

    newConnect(new, 4, list[2], list[4]);

    newConnect(new, 4, list[4], list[4]);
    newConnect(new, 3, list[4], list[5]);

    return new;
}

VERTICES *searchVertices(GRAPH* graph, int num){
    VERTICES *cur;
    VERTICES *ver = NULL;

    cur = graph->verList;
    while (cur->next != NULL) {
        cur = cur->next;
        if(cur->data == num) {
            ver = cur;
            break;
        }
    }

    return ver;
}

EDGES *searchEdges(GRAPH* graph, int a, int b){
    EDGES *edges = NULL;
    EDGES *cur = graph->edgeList;

    while (cur->next != NULL) {
        cur = cur->next;

        if(cur->start->data == a && cur->end->data == b)
            edges = cur;
        else if(cur->end->data == a && cur->start->data == b)
            edges = cur;
    }
    return edges;
}

void removeEdges(EDGES* edges){

    INCIDENCE *cur = edges->start->head;
    while (cur->next != NULL) {
        INCIDENCE *p = cur;
        cur = cur->next;

        if(cur->edge == edges) {
            p->next = cur->next;
            free(cur);
            break;
        }
    }

    cur = edges->end->head;
    while (cur->next != NULL) {
        INCIDENCE *p = cur;
        cur = cur->next;

        if(cur->edge == edges) {
            p->next = cur->next;
            free(cur);
            break;
        }
    }

    edges->start->inSize--;
    edges->end->inSize--;
    free(edges);
}

void addEdges(GRAPH* graph, int a, int b, int w){

    if(searchVertices(graph,a) == NULL || searchVertices(graph,b) == NULL) {
        puts("-1");
        return;
    }

    EDGES *edges = searchEdges(graph, a, b);
    if (w == 0) {
        removeEdges(edges);
    }
    else {
        if(edges == NULL)
            newConnect(graph, w, searchVertices(graph, a), searchVertices(graph, b));
        else
            edges->weight = w;
    }
}

void print(GRAPH *graph, int num){

    VERTICES *ver = searchVertices(graph, num);
    if (ver == NULL) {
        puts("-1");
        return;
    }


    INCIDENCE *inList = ver->head;
    int size = ver->inSize;
    VERTICES *verList[size];
    int weight[size];
    int idx = 0;

    while (inList->next != NULL) {
        inList = inList->next;

        if (inList->edge->start->data == num)
            verList[idx] = inList->edge->end;
        else
            verList[idx] = inList->edge->start;

        weight[idx] = inList->edge->weight;
        ++idx;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (verList[i]->data > verList[j]->data) {
                VERTICES *tmp = verList[i];
                verList[i] = verList[j];
                verList[j] = tmp;

                int wtmp = weight[i];
                weight[i] = weight[j];
                weight[j] = wtmp;
            }
        }
    }


    for (int i = 0; i < size; i++) {
        printf(" %d %d", verList[i]->data, weight[i]);
    }
    puts("");
}

int main(){
    GRAPH *graph = initGraph();

   /* print(graph, 2);
    addEdges(graph, 4, 2, 3);
    print(graph, 2);*/

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
                addEdges(graph, a, b, w);
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














