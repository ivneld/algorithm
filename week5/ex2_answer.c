#include <stdio.h>

#include <stdlib.h>

#include <time.h>



int findPivotIndex(int *L, int l, int r){

    int randomValue1, randomValue2, randomValue3;

    if (r - l <= 1){

        return l;

    }

    srand((unsigned)time(NULL));

    randomValue1 = (rand() % (r - l)) + l;

    randomValue2 = (rand() % (r - l)) + l;

    randomValue3 = (rand() % (r - l)) + l;



    if ((L[randomValue1] >= L[randomValue2] && L[randomValue1] <= L[randomValue3]) || (L[randomValue1] <= L[randomValue2] && L[randomValue1] >= L[randomValue3])) {

        return randomValue1;

    }

    else if (((L[randomValue2] >= L[randomValue1]) && (L[randomValue2] <= L[randomValue3])) || ((L[randomValue2] <= L[randomValue1]) && (L[randomValue2] >= L[randomValue3]))) {

        return randomValue2;

    }

    else {

        return randomValue3;

    }

}



int inPlacePartition(int *L, int l, int r, int k){

    int temp, i = l, j = r - 1, p = L[k];

    temp = L[k];

    L[k] = L[r];

    L[r] = temp;



    while (i <= j){

        while (i <= j && L[i] < p) {

            i = i + 1;

        }

        while (j >= i && L[j] >= p) {

            j = j - 1;

        }

        if (i < j){

            temp = L[i];

            L[i] = L[j];

            L[j] = temp;

        }

    }

    temp = L[i];

    L[i] = L[r];

    L[r] = temp;

    j = r - 1;

    while (i <= j){

        while (i <= j && L[i] == p) {

            j = j - 1;

        }

        if (i < j && L[i] == p){

            temp = L[i];

            L[i++] = L[j];

            L[j] = temp;

        }

    }

    return i;

}



void inPlaceQuickSort(int *L, int l, int r){

    int k, a, b, c;

    k = findPivotIndex(L, l, r);

    c = b = inPlacePartition(L, l, r, k);

    if (l >= r) {

        return;

    }

    while (1){

        if (L[c] != L[b]){

            a = c + 1;

            break;

        }

        c--;

    }

    inPlaceQuickSort(L, l, a - 1);

    inPlaceQuickSort(L, b + 1, r);

}



void printList(int *L, int n) {

    for (int i = 0; i < n; i++) {

        printf(" %d", L[i]);

    }

}



int main(){

    int *L, n;

    scanf("%d", &n);

    L = (int*)malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++){

        scanf("%d", &L[i]);

    }

    inPlaceQuickSort(L, 0, n - 1);

    printList(L, n);

    free(L);

}