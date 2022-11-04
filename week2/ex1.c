#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void InplaceSelectionSort(int *list, int size){

    while(size > 0) {
        int max = list[0];
        int maxIndex = 0;

        for (int i = 1; i < size; i++) {
            if(list[i] > max){
                max = list[i];
                maxIndex = i;
            }
        }

        swap(&list[size - 1], &list[maxIndex]);
        --size;
    }
}
void InPlaceInsertionSort(int* list, int size){

    for (int i = 1; i < size; i++) {

        int j = i;
        while (j > 0) {
            if (list[j - 1] > list[j]) {
                swap(&list[j], &list[j - 1]);
            }
            --j;
        }
    }
}
void sortList(int* list, int size){

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (list[i] < list[j]) {
                swap(&list[i], &list[j]);
            }
        }
    }
}
void printList(int* list, int size){
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
}
int main() {

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start,end,diff;


    int n;
    scanf("%d", &n);

    int *selectList = (int *) malloc(sizeof(int) * n);
    int *insertList = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        int num1 = rand() % 10000;
        int num2 = rand() % 10000;

        selectList[i] = num1;
        insertList[i] = num2;
    }
    sortList(selectList, n);
    sortList(insertList, n);

    printList(selectList, n);
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    InplaceSelectionSort(selectList, n);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.12f\n", (double) diff.QuadPart / (double) ticksPerSec.QuadPart);

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    InPlaceInsertionSort(insertList, n);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.12f\n", (double) diff.QuadPart / (double) ticksPerSec.QuadPart);
    return 0;
}