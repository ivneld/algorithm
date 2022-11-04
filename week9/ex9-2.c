#include <stdio.h>
#include <stdlib.h>

int M,q;

typedef struct NODE{
    struct NODE *next;
    int key;
}NODE;

int hashValue(int k){
    return k % M;
}
int hashValueV2(int k){
    return q - (k % q);
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
int getNextBucket(int v, int i){
    int b = hashValue(v);
    return (b + i * hashValueV2(v)) % M;
}
void insertItem(NODE** map, int k){
    int v = hashValue(k);
    int i = 0;

    while (i < M) {
        int b = getNextBucket(v, i);
        if(map[b] ->next == NULL) {
            NODE *new = getNode();
            new->key = k;

            new->next = map[b]->next;
            map[b]->next = new;
            printf("%d\n", b);
            return;
        }
        i++;
        printf("C");
    }
}
void findElement(NODE** map, int k){
    for (int i = 0; i < M; i++) {
        if(map[i]->next != NULL && map[i]->next->key == k) {
            printf("%d %d\n", i, k);
            return;
        }
    }
    printf("-1\n");
}

int main() {
    int n;
    scanf("%d %d %d", &M, &n, &q);
    getchar();
    NODE **hashMap = initBucketArray();

    while (1) {
        char cmd;
        int x;
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d", &x);
                insertItem(hashMap, x);
                break;
            case 's':
                scanf("%d", &x);
                findElement(hashMap, x);
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