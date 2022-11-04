#include <stdio.h>
#include <stdlib.h>

void inPlaceQuickSort(int* L, int l, int r);
int findPivot(int* L, int l, int r);
int inPlacePartition(int *L, int l, int r, int k);
void swap(int* a, int* b);

int main() {

    return 0;
}

int inPlacePartition(int *L, int l, int r, int k){
    int p = L[k];
    swap(&L[k], &L[r]);
    int i = l;
    int j = r-1;

    while (i <= j) {
        while (i <= j && L[i] <= p) {
            ++i;
        }
        while (j >= i && L[j] >= p) {
            --j;
        }
        if(i < j)
            swap(&L[i], &L[j]);
    }
    swap(&L[i], &L[r]);
    return i;
}
void inPlaceQuickSort(int *L, int l, int r){

    if(l>=r)
        return;
    int k = findPivot(L, l, r);
    int i = inPlacePartition(L, l, r, k);
    inPlaceQuickSort(L, l, i - 1);
    inPlaceQuickSort(L, i + 1, r);
}
int findPivot(int* L, int l, int r) {

}