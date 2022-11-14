#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 32    //key 값의 최대 개수

int q = 11;     // hash value 를 계산하기 위한 변수

typedef struct NODE{
    struct NODE *next;
    int key;
}NODE;

//hash value
int hashValue(int k){
    return k % MAX;
}
int hashValueV2(int k){
    return q - (k % q);
}

// 각 hash value 값에 해당하는 테이블의 해드노드의 key 값을 가지고
//활성화되어 있는 셀인지 확인함
// head node 의 키 값이 0 이면 비활성화, -1 이면 활성화된 셀로 판단
void deactivate(NODE* node){
    node->key = 0;
}
void activate(NODE* node){
    node->key = -1;
}


// 각 해쉬 값에 해당하는 셀이 활성화된 셀인지 판단하는 함수
int inactive(NODE* node){
    if(node->key == 0)
        return TRUE;
    return FALSE;
}
int active(NODE* node){
    if (node->key == -1)
        return TRUE;
    return FALSE;
}


// 새로운 노드를 생성하고 반환하는 함수
NODE* getNode(){
    NODE *new = (NODE *) malloc(sizeof(NODE));
    new->next = NULL;

    return new;
}


// 0~31 번의 셀을 가지는 테이블을 생성 후 반환
// 각 셀의 헤드 노드를 생성한 상태로
NODE** initBucketArray(){
    NODE **new = (NODE **) malloc(sizeof(NODE *) * MAX);

    for (int i = 0; i < MAX; i++)
        new[i] = getNode();

    return new;
}


// 문제의 형식에 맞춰 테이블 내용을  출력하는 함수
void print(NODE** map){

    for (int i = 0; i < MAX; i++) {
        if(i < 10)
            printf("%d  ", i);
        else
            printf("%d ", i);
    }
    puts("");

    for (int i = 0; i < MAX; i++) {
        if (inactive(map[i])) {
            printf(".  ");
        }
        else if(map[i]->next->key < 10)
            printf("%d  ", map[i]->next->key);
        else
            printf("%d ", map[i]->next->key);
    }
    puts("");
}

// key 값과 i 를 인자로 받아 충돌을 피해 다음 셀을 찾아 반환해주는 함수
int getNextBucket(int v, int i){
    int b = hashValue(v);
    return (b + i * hashValueV2(v)) % MAX;
}


// 인자로 받은 k(key) 값으로 추가할 셀을 찾고
// head 노드의 next에 새로운 노드를 추가하고 거기에 e(element) 값을 저장
// head 노드를 active 셀로 바꿔줌
// 비어있는 셀이 없을 경우 overflow 예외 발생
void insertItem(NODE** map, int k, int e){
    int i = 0;

    while (i < MAX) {
        int b = getNextBucket(k, i);
        if(inactive(map[b])) {
            NODE *new = getNode();
            new->key = e;

            new->next = map[b]->next;
            map[b]->next = new;

            activate(map[b]);

            return;
        }
        i++;
    }
    // 비어있는 셀이 없는 경우
    if(i == MAX) puts("overflow!");
}


// 인자로 받은 key 값으로 셀을 찾은 후 그 셀에 저장되어 있는 element를 반환 해 주는 함수
// 해당 key 값에 해당하는 셀들을 모두 탐색 후에도 찾지 못하였다면 NoSuchKey 예외 발생
void findElement(NODE** map, int k){

    int i = 0;

    while (i < MAX) {
        // 충돌이 일어났던 셀일 경우 k 값이 변경됨
        int b = getNextBucket(k, i);

        // 찾은 셀이 활성화된 셀인지 확인 후 element 출력
        if (active(map[b])) {
            printf("%d\n", map[b]->next->key);
            return;
        }
        i++;
    }
    puts("NoSuchKey");
}


// 인자로 받은 "element" 값이 저장되어 있는 셀을 찾아 그 노드를 삭제하고
// 해당 셀을 inactive 상태로 변환함
// 인자로 받은 element 값을 찾지 못하였을 경우 NoSuchKey 예외 발생
void removeElemet(NODE** map, int e){

    for (int i = 0; i < MAX; i++) {
        if(active(map[i]) && map[i]->next->key == e) {
            free(map[i]->next);
            deactivate(map[i]);
            return;
        }
    }
    puts("NoSuchKey");
}


// 문제 조건에 해당하는 0~19 번 셀에 1~20 의 element 값을 저장함
void set20Element(NODE** map){

    for (int i = 0; i < 20; i++) {
        insertItem(map, i, i + 1);
    }
}



int main() {
    NODE **hashMap = initBucketArray();
    set20Element(hashMap);          // element 20 개 삽입

    while (1) {
        char cmd;
        int x,e;
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d %d", &x, &e);
                insertItem(hashMap, x,e);
                print(hashMap);
                break;
            case 'f':
                scanf("%d", &x);
                findElement(hashMap, x);
                break;
            case 'p':
                print(hashMap);
                break;
            case 'r':
                scanf("%d", &e);
                removeElemet(hashMap, e);
                print(hashMap);
                break;
            case 'q':
                return -1;
            default:
                break;
        }
        getchar();
    }
    return 0;
}

/*
 * (입력) \n (출력)
p
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 .  .  .  .  .  .  .  .  .  .  .  .

 i 10 21
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 .  .  .  .  .  .  .  .  .  .  .

 i 100 22
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 .  .  .  22 .  .  .  .  .  .  .

 f 24
22

 r 22
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 .  .  .  .  .  .  .  .  .  .  .

q
 */
