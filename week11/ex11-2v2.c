#include <stdio.h>
#include <stdlib.h>
//queue 구현용 전역변수들
#define MAXSIZE 100000
int front = -1, rear = -1;
int queue[MAXSIZE];

int** root;
int N, M, V;

//QUEUE 구현
int putqueue(int val) {
    if ((rear + 1) % MAXSIZE == front) {    // 큐가 꽉 찼는지 확인
        return -1;
    }
    queue[rear] = val;     // rear가 큐의 끝 다음의 빈공간이므로 바로 저장
    rear = ++rear % MAXSIZE; // rear를 다음 빈공간으로 변경
    return val;
}
int getqueue(void) {
    int i;
    if (front == rear) {                  // 큐가 비어 있는지 확인
        return (-1);
    }
    i = queue[front];    // front의 값을 가져옴
    front = ++front % MAXSIZE;   // front를 다음 데이터 요소로
    return i;
}
void init_queue(void) {
    front = rear = 0;
}
void clear_queue(void) {
    front = rear;
}

//BFS 구현
void BFSsearch() {
    int point;
    int pathcheck = 0;

    int *path = (int*)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        path[i] = 0;
    }

    putqueue(V-1);
    path[V-1] = 1;
    printf("%d\n", V);

    //queue 구현시에 rear = front 면 queue가 비어있는걸로 함.
    while (rear != front) {
        point = getqueue();
        for (int i = 0; i < N; i++) {
            if ((path[i] != 1) && (root[point][i] == 1)) {
                putqueue(i);
                printf("%d\n", i+1);
                path[i] = 1;
            }
        }
    }
    free(path);

    return;
}
int main(void) {
    int i, y,x;

    scanf("%d %d %d", &N,&M,&V);
    getchar(); //\n 받기

    //2차원 배열들 동적할당
    root = (int**)calloc(N,sizeof(int*));
    for (i = 0; i < N; i++) {
        root[i] = (int*)calloc(N, sizeof(int));
    }

    for (i = 0; i < M; i++) {
        scanf("%d %d",&y,&x);
        root[y-1][x-1] = 1;
        root[x-1][y-1] = 1;
    }

    BFSsearch();

    return 0;
}