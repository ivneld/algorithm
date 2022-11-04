#include <stdio.h>
#include <stdlib.h>

int n;
int *A;

int rFE(int k, int l, int r){
    if(k < A[0]) return 0;
    if(k > A[n-1]) return n;

    int start = l;
    int end = r;

    while (start <= end) {
        int mid = (start + end) / 2;
        if (k == A[mid]) {
            return mid;
        }
        else if(A[mid] < k) {
            start = mid + 1;
        }
        else
            end = mid - 1;
    }
    return end;
}

int findElement(int k){
    return rFE(k, 0, n - 1);
}

int main() {
    int k;
    scanf("%d %d", &n, &k);

    A = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int index = findElement(k);
    printf(" %d", index);

    return 0;
}
