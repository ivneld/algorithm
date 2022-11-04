#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int n;
    struct node *next;
}NODE;

typedef struct {
    NODE *L1;
    NODE *L2;
}TMP;

NODE *addNode(int n);
void mergeSort(NODE **, int);
NODE* merge(NODE *, NODE *);
TMP partition(NODE *, int);
void printAll(NODE *node);

int main() {

    NODE *head;

    int n;
    int i;
    NODE *tmp;
    int t;

    head = (NODE *) malloc(sizeof(NODE));
    head->next = NULL;

    scanf("%d", &n);

    for (i = 0, tmp = head; i < n; i++) {
        scanf("%d", &t);
        tmp->next = addNode(t);
        tmp = tmp->next;
    }

    mergeSort(&head->next, n);
    printAll(head->next);
    return 0;
}

NODE *addNode(int n){
    NODE *new_node;
    new_node = (NODE *) malloc(sizeof(NODE));
    new_node->n = n;
    new_node->next = NULL;

    return new_node;
}

void mergeSort(NODE **L, int k){
    NODE *L1 = NULL, *L2 = NULL;
    TMP tmp;

    NODE *i;

    if (k > 1 && *L != NULL) {
        tmp = partition(*L, k / 2);
        L1 = tmp.L1;
        L2 = tmp.L2;

        mergeSort(&L1, k / 2);
        mergeSort(&L2, (int) ((k / 2.0) + 0.5));

        *L = merge(L1, L2);
    }
}

NODE *merge(NODE *L1, NODE *L2){
    NODE *result = NULL;

    if(L1 == NULL) return L2;
    else if(L2 == NULL) return L1;

    if (L1->n < L2->n) {
        result = L1;
        result->next = merge(L1->next, L2);
    }
    else {
        result = L2;
        result->next = merge(L1, L2->next);
    }

    return result;
}

TMP partition(NODE *L, int k){
    NODE *p;
    TMP result;
    NODE *L1,*L2;

    int i;

    p = L;
    L1 = L;

    for (i = 0; i < k - 1; i++) {
        p = p->next;
    }

    L2 = p->next;

    p->next = NULL;

    result.L1 = L1;
    result.L2 = L2;

    return result;
}

void printAll(NODE *node){
    NODE *i = node;

    while (i != NULL) {
        printf(" %d", i->n);
        i = i->next;
    }
    printf("\n");
}