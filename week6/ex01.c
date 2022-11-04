#include <stdio.h>
#include <stdlib.h>

int n;
int *A;

int rFE(int k, int l, int r){
    if(k < A[0]) return 0;
    if(k > A[n-1]) return -1;

    if (l > r) {
        return r;
    }

    int mid = (l + r) / 2;
    if(k == A[mid])
        return mid;
    else if(A[mid] < k)
        return rFE(k, mid + 1, r);
    else
        return rFE(k, l, mid - 1);

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
