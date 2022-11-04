#include <stdio.h>
#include <stdlib.h>

int M;

typedef struct NODE{
    struct NODE *next;
    int key;
}NODE;

int hashValue(int k){
    return k % M;
}
NODE* getNode(){
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new->next = NULL;

    return new;
}
NODE** initBucketArray(){
    NODE **new = (NODE **) malloc(sizeof(NODE *) * M);

    for (int i = 0; i < M; i++)
        new[i] = getNode();

    return new;
}
void insertItem(NODE** map, int k){

}