#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    int data;
}NODE;
typedef struct list{
    NODE *head;
    int size;
}LIST;

NODE* makenode(int data);
LIST* makeList(int size);
int isEmpty(LIST* list);
int removeFirst(LIST* list);
void addLast(LIST* list, int inData);
void mergeSort(LIST* list);
LIST* merge(LIST* list1, LIST* list2);
void partition(LIST* L, LIST *L1, LIST *L2);
void testList(LIST *list){
    NODE *cur = list->head;
    for (int i = 0; i < list->size; i++) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    puts("");
}
int main() {

    int n;
    scanf("%d", &n);
    LIST *list = makeList(n);

    mergeSort(list);

    return 0;
}

NODE* makenode(int data) {
    //make a new_node
    NODE* new = malloc(sizeof(NODE));
    new->data = data;
    new->next = NULL;

    return new;
}
LIST* makeList(int size){
    LIST *new = malloc(sizeof(LIST));
    new->size = size;

    int indata;
    scanf("%d", &indata);
    new->head = makenode(indata);
    NODE *cur = new->head;

    for (int i = 1; i < size; i++) {
        NODE *node = (NODE *) malloc(sizeof(NODE));
        scanf("%d", &indata);
        node->data = indata;
        cur->next = node;
        cur = node;
    }
    return new;
}
int isEmpty(LIST* list){
    if (list->size == 0) {
        return 1;
    }
    else
        return 0;
}
int removeFirst(LIST* list){
    int data = list->head->data;
    NODE *cur = list->head;
    list->head = list->head->next;
    free(cur);
    list->size--;
    return data;
}
void addLast(LIST* list, int inData){

    if(list->size == 0){
        list->head = makenode(inData);
    }
    else{
        NODE *cur = list->head;
        for (int i = 1; i < list->size; i++) {
            cur = cur->next;
        }
        NODE *new = makenode(inData);
        cur->next = new;
    }
    list->size++;
}
void mergeSort(LIST* list){

    LIST *L1 = (LIST *) malloc(sizeof(LIST));
    L1->size = 0;
    LIST *L2 = (LIST *) malloc(sizeof(LIST));
    L2->size = 0;

    if (list->size > 1) {
        partition(list, L1, L2);

        mergeSort(L1);
        mergeSort(L2);

        list = merge(L1, L2);
    }
    printf("%d", list->size);
}
LIST* merge(LIST* list1, LIST* list2){
    LIST *L = (LIST *) malloc(sizeof(LIST));
    L->size = 0;

    while (!isEmpty(list1) && !isEmpty(list2)) {
        if(list1->head->data <= list2->head->data)
            addLast(L, removeFirst(list1));
        else
            addLast(L, removeFirst(list2));
    }
    while (!isEmpty(list1)) {
        addLast(L, removeFirst(list1));
    }
    while (!isEmpty(list2)) {
        addLast(L, removeFirst(list2));
    }
    return L;
}
void partition(LIST* L, LIST *L1, LIST *L2){

    int size1 = L->size / 2;
    int size2 = L->size - L->size / 2;


    for (int i = 0; i < size1; i++) {
        addLast(L1, removeFirst(L));
    }
    for (int i = 0; i < size2; i++) {
        addLast(L2, removeFirst(L));
    }
}
