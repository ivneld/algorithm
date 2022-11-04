#include <stdio.h>
#include <stdlib.h>

int n;
int *A;

int findElement(int k, int l, int r){

    int s = l;
    int e = r;

    if (k > A[n - 1]) {
        return n;
    }
    if (k < A[0]) {
        return 0;
    }
    while (s <= e) {
        int mid = (s + e) / 2;

        if (A[mid] == k) {
            return mid;
        }
        else if (k > A[mid]) {
            s = mid + 1;
        }
        else{
            e = mid - 1;
        }
    }
    return s;
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

//8 -33
//-92 -31 -7 4 14 20 29 44