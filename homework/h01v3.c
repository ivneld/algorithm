#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int *buildList(int n, int min, int max);
void writeList(int* list, int n);
int findKthSmallest(int *list, int n, int k);
void buildHeap(int *list, int n);
void downHeap(int* list, int i);
void swap(int *a, int *b);

int main() {

    int n = 10;
    int *list = buildList(n, 1, 1000000);

    int k = findKthSmallest(list, n, 3);
    writeList(list, n);
    buildHeap(list, n);
    writeList(list, n);
    return 0;
}

int *buildList(int n, int min, int max){
    srand(time(NULL));
    int *list = (int *) calloc(n+1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        list[i] = rand() % max + min;
    }

    return list;
}
void writeList(int* list, int n) {

    for (int i = 1; i <= n; i++) {
        printf("%d ", list[i]);
    }
    puts("");
}
int findKthSmallest(int *list, int n, int k){

    int data;

    int *findList = (int *) calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        findList[i] = list[i];
    }

    buildHeap(findList, n);
    for (int i = 0; i < k; i++) {
        data = findList[1];
        swap(&findList[1], &findList[n]);
        findList[n] = 0;
        downHeap(findList, 1);
    }

    return data;
}
void buildHeap(int *list, int n){
    for (int i = n / 2; i >= 1; i--) {
        downHeap(list, i);
    }
}
void downHeap(int* list, int i){

    int left = i * 2;
    int right = i * 2 + 1;

    if (list[left] == 0 && list[right] == 0) {
        return;
    }
    if (list[left] >= list[i] && list[right] >= list[i]) {
        return;
    }

    int cur = left;
    if (list[left] > list[right]) {
        cur = right;
    }

    swap(&list[i], &list[cur]);
    downHeap(list, cur);
}
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}