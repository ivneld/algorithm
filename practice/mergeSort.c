#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}NODE;

typedef struct list {
    NODE *head;
    int size;
} LIST;

NODE* getNode() {
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new->next = NULL;

    return new;
}

LIST* initList(int size){
    LIST *L = (LIST *) malloc(sizeof(LIST));
    L->head = getNode();
    L->size = size;

    return L;
}
int getData(LIST *L){
    int data = L->head->next->data;

    NODE *cur = L->head->next;
    L->head->next = L->head->next->next;
    free(cur);

    L->size--;
    return data;
}
void insert(LIST *L, int data){
    NODE *new = getNode();
    new->data = data;

    if (L->head->next == NULL) {
        L->head->next = new;
    }
    else{
        new->next = L->head->next;
        L->head->next = new;
    }
}
void addLast(LIST *L, int data){
    NODE *cur = L->head;

    for (int i = 0; i < L->size; i++) {
        cur = cur->next;
    }

    NODE *new = getNode();
    new->data = data;
    cur->next = new;

    L->size++;
}
LIST* partition(LIST *L, int size){
    LIST *list = initList(size);

    for (int i = 0; i < size; i++) {
        int data = getData(L);
        insert(list, data);
    }
    return list;
}
void merge(LIST *L, LIST *L1, LIST *L2){
    while (L1->size != 0 && L2->size != 0) {
        if (L1->head->next->data <= L2->head->next->data) {
            addLast(L, getData(L1));
        }
        else
            addLast(L, getData(L2));
    }
    while (L1->size != 0) {
        addLast(L, getData(L1));
    }
    while (L2->size != 0) {
        addLast(L, getData(L2));
    }
}
void mergeSort(LIST* L){

    if (L->size > 1) {
        int size1 = L->size / 2;
        int size2 = L->size - L->size / 2;
        LIST *L1 = partition(L, size1);
        LIST *L2 = partition(L, size2);
        mergeSort(L1);
        mergeSort(L2);

        merge(L, L1, L2);

    }
}
int main() {
    int n;
    scanf("%d", &n);

    LIST *list = initList(n);
    NODE *cur = list->head;
    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        NODE *new = getNode();
        new->data = data;
        cur->next = new;
        cur = new;
    }

    mergeSort(list);

    cur = list->head->next;
    for (int i = 0; i < list->size; i++) {
        printf(" %d", cur->data);
        cur = cur->next;
    }
    return 0;
}