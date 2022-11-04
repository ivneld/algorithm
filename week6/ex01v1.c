#include <stdio.h>
#include <stdlib.h>

int n;
int *A;

int findElement(int k, int l, int r){

    if (l > r) {
        return r;
    }
    if (k > A[n - 1]) {
        return n-1;
    }
    if (k < A[0]) {
        return -1;
    }

    int mid = (l + r) / 2;
    if (k == A[mid]) {
        return mid;
    }
    else if (k > A[mid]) {
        return findElement(k, mid + 1, r);
    }
    else {
        return findElement(k, l, mid - 1);
    }
}

int main() {
    int k;
    scanf("%d %d", &n, &k);
    A = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int idx = findElement(k, 0, n - 1);
    printf(" %d", idx);

    return 0;
}

//8 -100
//-92 -31 -7 4 14 20 29 44