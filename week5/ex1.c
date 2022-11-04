#include <stdio.h>

#include <stdlib.h>



struct node{

    int data;

    struct node *next;

};



void partition(struct node *L, struct node **L1, struct node **L2, int n) {

    struct node *p = L;

    *L1 = L;

    for (int i = 0; i < (n / 2) - 1; i++) {

        p = p->next;

    }

    *L2 = p->next;

    p->next = NULL;

}



struct node *merge(struct node **L1, struct node **L2){

    struct node *p, *L;

    struct node *A = *L1;

    struct node *B = *L2;

    if (A->data <= B->data){

        L = A;

        A = A->next;

        p = L;

    }

    else{

        L = B;

        B = B->next;

        p = L;

    }

    while ((A != NULL) && (B != NULL)){

        if (A->data <= B->data){

            p->next = A;

            A = A->next;

            p = p->next;

        }

        else{

            p->next = B;

            B = B->next;

            p = p->next;

        }

    }

    while (A != NULL){

        p->next = A;

        p = A;

        A = A->next;

    }

    while (B != NULL){

        p->next = B;

        p = B;

        B = B->next;

    }

    return L;

}



void mergeSort(struct node **L, int n){

    struct node *L1, *L2, *p = *L;

    if (n > 1){

        partition(p, &L1, &L2, n);

        if ((n % 2) == 0){

            mergeSort(&L1, n / 2);

            mergeSort(&L2, n / 2);

        }

        else{

            mergeSort(&L1, n / 2);

            mergeSort(&L2, (n / 2) + 1);

        }

        *L = merge(&L1, &L2);

    }

}



void addList(struct node **L, int value) {

    struct node *p = *L;

    struct node *newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = value;

    newnode->next = NULL;

    if (*L == NULL) {

        *L = newnode;

    }

    else {

        while (p->next != NULL) {

            p = p->next;

        }

        p->next = newnode;

    }

}



void printList(struct node *L) {

    struct node *p = L;

    while (p != NULL) {

        printf(" %d", p->data);

        p = p->next;

    }

    printf("\n");

}



void deleteList(struct node *L) {

    struct node *p = L;

    while (p != NULL) {

        L = L->next;

        free(p);

        p = L;

    }

}



int main(){

    int n, value;

    struct node *L = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++){

        scanf("%d", &value);

        addList(&L, value);

    }

    mergeSort(&L, n);

    printList(L);

    deleteList(L);

}