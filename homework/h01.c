#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int findKthSmallest(int *L, int n, int k);
int* buildList(int n, int min, int max);
void downHeap(int *L, int i, int last);
void buildHeap(int* L, int n);
void swap(int* a, int *b);
void print(int *arr, int n);

int main() {

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start,end,diff;

    int* L;
    L = buildList(10, 1, 100);

    print(L, 10);

    int arr[3];
    for (int i = 0; i < 3; i++) {
        arr[i] = findKthSmallest(L, 10, i + 1);
    }

    for (int i = 0; i < 3; i++) {
        printf(" %d", arr[i]);
    }
    puts("");
    free(L);

    L = buildList(100000, 1, 1000000);

    int karray[4] = {1, 100, 99900, 99999};
    for (int k = 0; k < 4; k++) {
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int e = findKthSmallest(L, 100000, karray[k]);
        QueryPerformanceCounter(&end);

        diff.QuadPart = end.QuadPart - start.QuadPart;
        printf("%d, time : %.12f\n", e, (double) diff.QuadPart / (double) ticksPerSec.QuadPart);
    }
    return 0;
}

int findKthSmallest(int *L, int n, int k){
    int data;

    int *H = (int *) malloc(sizeof(int) * (n+1));
    for (int i = 1; i <= n; i++) {
        H[i] = L[i];
    }

    buildHeap(H,n );
    int size = n;
    data = H[1];
    for (int i = 1; i < k; i++) {
        swap(&H[1], &H[size]);
        --size;
        downHeap(H, 1, size);
        data = H[1];
    }

    return data;
}

int* buildList(int n, int min, int max){
    int *L = (int *) malloc(sizeof(int) * (n+1));

    for (int i = 1; i <= n; i++) {
        int x = rand() % max + min;
        L[i] = x;
    }

    return L;
}

void downHeap(int *L, int i, int last){

    int left = i * 2;
    int right = i * 2 + 1;
    if (left > last) {
        return;
    }

    int greater = left;
    if (right <= last) {
        if (L[right] < L[greater]) {
            greater = right;
        }
    }

    if (L[i] <= L[greater]) {
        return;
    }

    swap(&L[i], &L[greater]);
    downHeap(L, greater, last);
}

void buildHeap(int* L, int n) {

    for (int i = n / 2; i >= 1; i--) {
        downHeap(L, i, n);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print(int *arr, int n) {
    for (int i = 1; i <= n; i++) {
        printf(" %d", arr[i]);
    }
    puts("");
}