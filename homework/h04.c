#include <stdio.h>
#include <stdlib.h>
#define MAX 30
#define BIG_INT 10000000

int *A, *H;

int min(int a, int b){
    return a > b ? b : a;
}
//A = {0, 1, 5, 8, 14, 21, 25, 28, 34, 41
//H = {0, 5, 8, 3, 8, 5, 3, 2, 2, 3, 5, 8, ...}
int rAirtel(int s, int d){
    if(s == d)
        return 0;

    int minCost = BIG_INT;
    for (int k = s; k < d; k++) {
        int stayCost;
        if(s == k) stayCost = 0;
        else stayCost = H[k];

        int cost = rAirtel(s, k) + stayCost + A[d - k];
        minCost = min(minCost, cost);
    }
    return minCost;
}
int airtelDC(int s, int d){
    return rAirtel(s, d);
}
int airtelDP(int s, int n){
    int *m = (int *) malloc(sizeof(int) * (n+1));
    m[s] = 0;

    for (int d = s + 1; d <= n; d++) {
        m[d] = BIG_INT;
        for (int k = s; k < d; k++) {
            int stayCost;

            if(k == s) stayCost = 0;
            else stayCost = H[k];

            int cost = m[k] + stayCost + A[d - k];
            m[d] = min(m[d], cost);
        }
    }

    for (int i = 0; i < n; i++)
        printf("m : %d ", m[i]);
    puts("");

    return m[n];
}

void printResult(int n, int s, int d){
    puts("n       s       d       mincost       version       cputime");
    printf("%d       %d       %d        %d        DC        %.12f",n,s,d, airtelDC(s,d), airtelDP(s,d),)
}
int main() {

    A = (int *) malloc(sizeof(int) * MAX);
    H = (int *) malloc(sizeof(int) * MAX);

    A[0] = 0;
    A[1] = 1;
    for (int i = 2; i < MAX; i++) {
        A[i] = A[i - 1] + A[i - 1] % 5 + 3;
    }

    H[0] = 0;
    H[1] = 5;
    for (int i = 2; i < MAX; i++) {
        H[i] = (H[i - 1] + i) % 9 + 1;
    }

    int s = 1;
    int d = 28;
    puts("n       s       d       mincost       version       cputime");
    printf("%d %d", airtelDC(s, d), airtelDP(s, d));

    return 0;
}