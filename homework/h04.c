#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX 30
#define BIG_INT 10000000        // 최소값을 구하기 위한 값

int *A, *H;

int MIN(int a, int b){
    return a > b ? b : a;
}


int rAirtel(int s, int d){
    if(s == d)
        return 0;       //시작 지점 과 도착 지점이 같은 경우

    int minCost = BIG_INT;      // 최소 값을 구하기 위한 값
    for (int k = s; k < d; k++) {
        int stayCost;
        if(s == k) stayCost = 0;    // 시작 지점에서의 숙박비는 없다.
        else stayCost = H[k];

        int cost = rAirtel(s, k) + stayCost + A[d - k]; // 반복적인 재귀 호출을 통해 원하는 지점까지 가는 최소 비용을 구함
        minCost = MIN(minCost, cost);       // 최소 값을 저장
    }
    return minCost;
}
int airtelDC(int s, int d){
    return rAirtel(s, d);       // 재귀 함수 호출
}
int airtelDP(int s, int n){
    int *m = (int *) malloc(sizeof(int) * (n+1));   // 도착지점 n 까지 가는데 각 지점 마다의 최소 비용을 저장할 배열
    m[s] = 0;   // 시작지점 s 부터의 값만 계산하면 되므로 s번째 배열의 값을 0
    // 재귀 호출 함수의 s == d 부분과 같은 의미

    for (int d = s + 1; d <= n; d++) {
        m[d] = BIG_INT;
        for (int k = s; k < d; k++) {
            int stayCost;

            if(k == s) stayCost = 0;        // 출발 지점일 경우에는 숙박비가 없음
            else stayCost = H[k];

            int cost = m[k] + stayCost + A[d - k];      // 각 구간 마다의 최소 비용을 구함
            m[d] = min(m[d], cost);
        }
    }
    return m[n];        // 도착 지점까지의 최소 비용 반환
}

void printResult(int n, int s, int d){
    double cputime;
    int mincost;        // 각 방법에 따른 최소 비용을 저장

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start,end,diff;

    // 재귀버전
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    mincost = airtelDC(s, d);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputime = (double) diff.QuadPart / (double) ticksPerSec.QuadPart;

    printf("%d       %d       %d         %d           DC        %.12lf\n", n, s, d, mincost, cputime);


    // 배열버전
    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    mincost = airtelDP(s, d);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputime = (double) diff.QuadPart / (double) ticksPerSec.QuadPart;

    printf("%d       %d       %d         %d           DP        %.12lf\n", n, s, d, mincost, cputime);

}

int main() {

    A = (int *) malloc(sizeof(int) * MAX);
    H = (int *) malloc(sizeof(int) * MAX);

    A[0] = 0;
    A[1] = 1;
    for (int i = 2; i < MAX; i++) {
        A[i] = A[i - 1] + A[i - 1] % 5 + 3;
    }
    // 배열 A는 거리에 대한 비용

    H[0] = 0;
    H[1] = 5;
    for (int i = 2; i < MAX; i++) {
        H[i] = (H[i - 1] + i) % 9 + 1;
    }
    // 배열 H는 각 지점에서의 숙박 비용

    puts("n       s       d       mincost       version       cputime");

    printResult(6, 0, 4);
    printResult(6, 2, 5);
    printResult(6, 2, 4);
    printResult(30, 1, 28);

    return 0;
}