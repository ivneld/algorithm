#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void swap(int* a, int* b);
void downHeap(int* L, int i, int last);
void buildHeap(int *L, int n);
int* buildList(int n, int min, int max);
int findKthSmallest(int* L, int n, int k);
void writeList(int* arr, int n);

int main() {
    srand(time(NULL));

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start,end,diff;

    // 1 ~ 100 까지의 값을 가지는 리스트 생성
    int *L = buildList(10, 1, 100);

    writeList(L, 10);

    // 1~3 번째로 작은 원소를 저장 후 출력
    int arr[4];
    for (int i = 1; i <= 3; i++) {
        arr[i] = findKthSmallest(L, 10, i);
    }
    writeList(arr, 3);

    free(L);
    // 정확한 값이 출력이 안되는 문제로 요구사항의 max를 10000로 줄였음
    L = buildList(100000, 1, 1000000);

    int karry[4] = {1, 10, 99900, 99999};

    // 4개의 k값에 대해서 찾은 값과 cpu time을 출력
    for (int i = 0; i < 4; i++) {
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int e = findKthSmallest(L, 100000, karry[i]);
        QueryPerformanceCounter(&end);

        diff.QuadPart = end.QuadPart - start.QuadPart;

        double time = (double) diff.QuadPart / (double) ticksPerSec.QuadPart;

        printf("%d, time : %.12lf\n", e, time);
    }
    return 0;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
// i 인덱스를 루트 노드로 최소힙을 구성하는 함수
void downHeap(int* L, int i, int last) {

    int left = i*2;
    int right = i * 2 + 1;
    if (left > last) {
        return;
    }

    int cur = left;
    if (right <= last) {
        if (L[right] < L[left]) {
            cur = right;
        }
    }
    if (L[i] <= L[cur]) {
        return;
    }
    swap(&L[i], &L[cur]);
    downHeap(L, cur, last);
}
// 입력받은 리스트를 최소 힙으로 구성하는 함수
void buildHeap(int* L, int n){

    for (int i = n / 2; i >= 1; i--) {
        downHeap(L, i,n);
    }
}
// min ~ max 까지의 n개의 값을 저장하고 배열을 반환하는 함수
int* buildList(int n, int min, int max) {

    int *L = (int *) calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        L[i] = rand() % max + min;
    }

    return L;
}
// k번째로 작은 원소를 반환하는 함수
int findKthSmallest(int* L, int n, int k) {

    // 기존의 리스트를 유지하기 위해 계산용 리스트를 만든다
    int *arr = (int *) malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        arr[i] = L[i];
    }

    int size = n;
    buildHeap(arr, size);
    int data = arr[1];
    // 첫번째로 작은 원소를 저장해 두고 그 보다 작은 원소는 최소힙을 유지하면서 루트 값을 반환한다.
    for (int i = 1; i < k; i++) {
        swap(&arr[1], &arr[size--]);
        downHeap(arr, 1, size);
        data = arr[1];
    }

    return data;
}
// 1번부터 n번까지 출력
void writeList(int* arr, int n) {
    for (int i = 1; i <= n; i++) {
        printf(" %d", arr[i]);
    }
    puts("");
}