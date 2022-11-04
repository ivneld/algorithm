#include <stdio.h>

int H[99];
int n;

void insertItem(int key);
void upHeap(int i);     //i -> index
void downHeap(int i, int last);
void swap(int* a, int *b);
void inPlaceHeapSort();
void buildHeap();
void printArray();

int main() {

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }

    inPlaceHeapSort();
    printArray();

    return 0;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void downHeap(int i, int last){

    int left = i * 2;
    int right = i * 2 + 1;
    if (left > last) {
        return;
    }

    int greater = left;
    if (right <= last) {
        if (H[right] > H[greater]) {
            greater = right;
        }
    }

    if (H[i] >= H[greater]) {
        return;
    }
    swap(&H[i], &H[greater]);
    downHeap(greater, last);
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

void buildHeap() {

    for (int i = n / 2; i >= 1; i--) {
        downHeap(i,n);
    }
}
void inPlaceHeapSort(){

    buildHeap();
    for (int i = n; i >= 2; i--) {
        swap(&H[1], &H[i]);
        downHeap(1, i - 1);
    }
}

void printArray() {

    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
}