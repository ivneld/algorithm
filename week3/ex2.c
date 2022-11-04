#include <stdio.h>

int H[99];
int n;

void rBuildHeap(int i);
void buildHeap();
void downHeap(int i);
void printHeap();
void swap();

int main() {

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }

    rBuildHeap(1);
    printHeap();

    return 0;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rBuildHeap(int i){

    if (i > n) {
        return;
    }

    rBuildHeap(2 * i);
    rBuildHeap(2 * i + 1);
    downHeap(i);
}

void buildHeap(){

    for (int i = n / 2; i >= 1; i--) {
        downHeap(i);
    }

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

