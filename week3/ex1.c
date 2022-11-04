#include <stdio.h>

int H[99];  //heap list
int n;  //size

void insertItem(int key);
int removeMax();
void upHeap(int i);     //i -> index
void downHeap(int i);
void printHeap();
void swap(int* a, int *b);

int main() {

    while (1) {
        char cmd;
        int key, data;

        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d", &key);
                insertItem(key);
                break;
            case 'd':
                key = removeMax();
                printf("%d\n", key);
                break;
            case 'p':
                printHeap();
                break;
            case 'q':
                return 5;
        }
        getchar();
    }
    return 0;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertItem(int key){
    n++;
    H[n] = key;
    upHeap(n);

    puts("0");
}

int removeMax(){

    int key = H[1];
    swap(&H[1], &H[n]);
    H[n] = 0;

    downHeap(1);
    n--;

    return key;
}

void upHeap(int i){

    if (i == 1) {
        return;
    }
    if (H[i] <= H[i / 2]) {
        return;
    }

    swap(&H[i], &H[i / 2]);
    upHeap(i / 2);
}

void downHeap(int i){

    if (H[i * 2] == 0 && H[i * 2 + 1] == 0) {
        return;
    }
    if (H[i] >= H[i * 2] && H[i] >= H[i * 2 + 1]) {
        return;
    }
    int cur;
    if (H[i * 2] > H[i * 2 + 1]) {
        cur = i * 2;
    } else {
        cur = i * 2 + 1;
    }

    swap(&H[i], &H[cur]);
    downHeap(cur);
}

void printHeap(){

    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
    puts("");
}