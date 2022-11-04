#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int n = 100000;
int limits[4] = {1, 100, 500, 1000};

int findIndexOfMedianOfThree(int *A, int a, int b, int c);
void swap(int *a, int *b);
int* createArray();
int findPivot(int *A, int l, int r, int mode);
void inPlacePartition(int *A, int l, int r, int k, int *a, int *b);
void rQuickSort(int *A, int l,int r, int mode, int limit);
void quickSort(int* A, int mode, int limit);
int* copyList(int *A);
void insertionSort(int *A);

int main() {

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start,end,diff;

    int *A = createArray();

    for (int i = 0; i < 4; i++) {
        printf("limit : %d, ", limits[i]);
        for (int j = 1; j <= 4; j++) {
            int *cList = copyList(A);
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            quickSort(cList, j, limits[i]);
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("mode : %d => time : %.12f   ", j, (double) diff.QuadPart / (double) ticksPerSec.QuadPart);
        }
        puts("");
    }

    return 0;
}

// A[a], A[b], A[c] 중 두번째로 큰 값을 찾아 그 인덱스를 반환해주는 함수
int findIndexOfMedianOfThree(int *A, int a, int b, int c) {

    if ((A[a] >= A[b] && A[b] > A[c]) || (A[c] >= A[b] && A[b] >= A[a])) {
        return b;
    } else if ((A[b] >= A[a] && A[a] >= A[c]) || (A[c] >= A[a] && A[a] >= A[b])) {
        return a;
    } else if ((A[a] >= A[c] && A[c] >= A[b]) || (A[b] >= A[c] && A[c] >= A[a])) {
        return c;
    }
}

// 배열의 두 값의 위치를 바꿔주는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// n 크기 만큼의 랜덤한 값을 갖는 배열을 반환해주는 함수
int* createArray() {
    int *list = (int *) malloc(sizeof(int) * n);
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int x = rand() % n + 1;
        list[i] = x;
    }

    return list;
}

// 인자로 mode를 전달 받아 mode 값에 해당하는 방법으로 pivot의 인덱스를 반환해 주는 함수
// mode 1 : deterministic1, mode 2 : randomized1, mode 3 : deterministic3, mode 4 : randomized3
int findPivot(int *A, int l, int r, int mode) {

    srand(time(NULL));

    if(mode == 1) {
        return r;
    }
    // l과 r 사이의 값 반환
    if (mode == 2) {
        return rand() % (r - l + 1) + l;
    }
    if (r - l == 1) {
        return l;
    }

    int a,b,c;

    switch(mode) {
        case 3:
            a = l;
            b = (l + r) / 2;
            c = r;
            break;
        case 4:     // a,b,c 는 모두 l과r 사이의 랜덤한 값
            a = rand() % (r - l + 1) + l;
            b = rand() % (r - l + 1) + l;
            c = rand() % (r - l + 1) + l;
            break;
    }

    return findIndexOfMedianOfThree(A, a, b, c);    //두번째로 큰 값의 인덱스 반환
}

// 인덱스 l부터 r까지 파티션을 수행하고 a,b 값을 반환
// l부터 a-1 까지는 A[k]보다 작은값 b+1부터 r까지는 A[k]보다 큰 값
void inPlacePartition(int *A, int l, int r, int k, int *a, int *b) {
    int p = A[k];       //피벗 설정
    swap(&A[k], &A[r]);     //배열의 마지막 원소와 교환
    int i = l;
    int j = r-1;

    while (i <= j) {
        while (i <= j && A[i] < p) {
            ++i;            // p 보다 크거나 같은 값을 찾은 후 멈춤
        }
        while (j >= i && A[j] >= p) {
            --j;            // p 보다 작은 값을 찾은 후 멈춤
        }
        if (i < j) {
            swap(&A[i], &A[j]);
        }       // 값을 교환하여 정렬
    }
    swap(&A[i], &A[r]);     // 숨겨뒀던 값을 다시 제자리로 위치시킴
    *a = i;
    *b = i;
}

// quickSort 함수 안에서 실행되며
// 정렬 버전을 입력 받아 재귀적으로 정렬을 수행하는 함수
void rQuickSort(int *A, int l,int r, int mode, int limit) {
    if(r-l >= limit)
        return;     // base case
    int k = findPivot(A, l, r, mode);  // 버전에 맞게 피벗을 설정
    int a, b;
    inPlacePartition(A, l, r, k, &a, &b);      // 파티션을 통해 피벗보다 작은 구간 큰 구간을 반환
    rQuickSort(A, l, a - 1, mode,limit);
    rQuickSort(A, b + 1, r, mode, limit);
}

// mode, limit을 인자로 받아 rQuickSort 함수로 호출해주고
// limit 값이 1 보다 크다면 삽입정렬을 수행한다.
void quickSort(int *A, int mode, int limit){
    rQuickSort(A, 0, n - 1,mode,limit);
    if (limit > 1) {
        insertionSort(A);
    }
}

// 배열을 인자로 받아 똑같은 배열을 반환해 주는 함수
int* copyList(int *A){
    int *cList = (int *) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        cList[i] = A[i];
    }
    return cList;
}

// 삽입정렬
void insertionSort(int *A) {

    int save;
    int i, j;

    for (i = 1; i < n; i++) {
        save = A[i];    // 배열의 두번째 부터 시작

        // 이전 인덱스 배열의 값과 비교해 가며 save보다 더 큰 값이면 앞으로 이동
        for (j = i - 1; j >= 0 && A[j] > save; j--) {
            A[j + 1] = A[j];
        }

        // 빈 자리에 save 다시 저장
        A[j + 1] = save;
    }
}