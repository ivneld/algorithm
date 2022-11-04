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
int findElement(NODE** map, int k){
    int v = hashValue(k);
    int rank=0;

    NODE *np = map[v];
    while (np->next != NULL) {
        ++rank;
        np = np->next;

        if(np->key == k)
            return rank;
    }

    return 0;
}
void insertItem(NODE** map, int e){
    int v = hashValue(e);

    NODE *new = getNode();
    new->key = e;

    new->next = map[v]->next;
    map[v]->next = new;
}
int removeElement(NODE** map, int k){
    int v = hashValue(k);
    int rank = 0;

    NODE *np = map[v];
    NODE* prev;
    while (np->next != NULL) {
        ++rank;
        prev = np;
        np = np->next;

        if (np->key == k) {
            prev->next = np->next;
            free(np);
            return rank;
        }
    }

    return 0;
}
void print(NODE** map){
    for (int i = 0; i < M; i++) {
        NODE *np = map[i];

        while(np->next != NULL){
            np = np->next;
            printf(" %d", np->key);
        }
    }
    puts("");
}

int main() {

    scanf("%d", &M);
    getchar();
    NODE **hashMap = initBucketArray();

    while (1) {
        char cmd;
        int x,e;
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d", &x);
                insertItem(hashMap, x);
                break;
            case 's':
                scanf("%d", &x);
                e = findElement(hashMap, x);
                printf("%d\n", e);
                break;
            case 'd':
                scanf("%d", &x);
                e = removeElement(hashMap, x);
                printf("%d\n", e);
                break;
            case 'p':
                print(hashMap);
                break;
            case 'e':
                return -1;
            default:
                break;
        }
        getchar();
    }
    return 0;
}