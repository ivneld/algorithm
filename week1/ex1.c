#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node Node;
struct node {
    char elem;
    Node *prev;
    Node *next;
};

typedef struct list{
    Node *head;
    Node *tail;
    int size;
}List;

Node* createNode() {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void init(List *lp) {
    if(lp == NULL) {
        return;
    }

    lp->head = createNode();
    lp->tail = createNode();
    lp->head->next = lp->tail;
    lp->head->prev = NULL;
    lp->tail->prev = lp->head;
    lp->tail->next = NULL;

    lp->size = 0;
}

void add(List* lp, int rank, char inData) {
    if (lp == NULL) {
        return;
    }

    Node *np = lp->head;
    for (int i = 1; i < rank; i++) {
        np = np->next;
    }

    Node *newNode = createNode();
    newNode->elem = inData;
    newNode->prev = np;
    newNode->next = np->next;
    np->next->prev = newNode;
    np->next = newNode;

    ++lp->size;
}

void delete(List* lp, int rank) {
    if (lp == NULL) {
        return;
    }

    Node *np = lp->head;
    for (int i = 0; i < rank; i++) {
        np = np->next;
    }

    Node *prevNode = np->prev;
    Node *nextNode = np->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    free(np);

    --lp->size;
}

void get(List* lp, int rank) {
    if (lp == NULL) {
        return;
    }
    if (rank > lp->size || rank < 1) {
        puts("invalid position");
        return;
    }

    Node* np = lp->head;
    for (int i = 0; i < rank; i++) {
        np = np->next;
    }

    printf("%c\n", np->elem);
}

void print(List* lp) {
    if (lp == NULL) {
        return;
    }

    Node* np = lp->head;
    for (int i = 0; i < lp->size; i++) {
        np = np->next;
        printf("%c", np->elem);
    }
    puts("");
}

int main() {

    int N;
    scanf("%d", &N);
    getchar();
    List *list = (List *) malloc(sizeof(List));
    init(list);

    for (int i = 0; i < N; i++) {
        char cmd, elem;
        int rank;

        scanf("%c", &cmd);
        switch (cmd) {
            case 'A':
                scanf("%d %c", &rank, &elem);
                getchar();
                add(list, rank, elem);
                break;
            case 'D':
                scanf("%d", &rank);
                getchar();
                delete(list, rank);
                break;
            case 'G':
                scanf("%d", &rank);
                getchar();
                get(list, rank);
                break;
            case 'P':
                print(list);
                getchar();
                break;
            default:
                break;
        }
    }
    return 0;
}