#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// list는 0번부터 n-1까지의 인덱스
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int findPivot(int l, int r) {
    srand(time(NULL));
    int k = rand() % (r - l);
    return k+l;
}
void inPlacePartition(int *L, int l, int r, int k, int* a, int *b) {
    int p = L[k];
    swap(&L[k], &L[r]);
    int i = l;
    int j = r-1;
    int cnt = 0;

    while (i <= j) {
        while (i <= j && L[i] < p) {
            i++;
        }
        while (j >= i && L[j] >= p) {
            j--;
            if(j > i && L[j] == p) ++cnt;
        }
        if(L[i] == p) ++cnt;

        if (i < j)
            swap(&L[i], &L[j]);
    }
    swap(&L[i], &L[r]);
    *a = i;
    *b = i+cnt;
}
void inPlaceQuickSort(int *L, int l, int r) {
    if(l>=r) {
        return;
    }
    if(l < 0 || r < 0)
        return;
    srand(time(NULL));
    int k = rand() % r + 1;
    int a,b;
    inPlacePartition(L, l, r, k, &a, &b);
    for (int i = l; i <= r; i++) printf("%d ", L[i]);
    printf("k : %d, a : %d, b: %d, l : %d, r : %d\n", k, a, b, l, r);

    inPlaceQuickSort(L, l, a - 1);
    inPlaceQuickSort(L, b + 1, r);
}
int main() {
    int *list;
    int n;
    scanf("%d", &n);
    list = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }

    inPlaceQuickSort(list, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf(" %d", list[i]);
    }

    return 0;
}

//8
//73 65 48 31 29 20 8 3

