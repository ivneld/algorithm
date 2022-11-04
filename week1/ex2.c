#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}node;

void Newnode(node* L) {

    int Pnum, Lnum, Rnum;
    scanf("%d %d %d", &Pnum, &Lnum, &Rnum);
    getchar();
    if (L->data != Pnum)printf("error\n");

    node* leftson;
    leftson = (node*)malloc(sizeof(node));
    leftson->data = Lnum;
    L->left = leftson;


    node* rightson;
    rightson = (node*)malloc(sizeof(node));
    rightson->data = Rnum;
    L->right = rightson;

    if (Lnum != 0) {
        Newnode(L->left);
    }
    if (Rnum != 0) {
        Newnode(L->right);
    }
    return;
}

void search(node* L) {

    node* temp = L;
    int j, length;
    char arry[100];
    scanf("%s", arry);
    getchar();
    length = strlen(arry);

    printf("%d ", temp->data);//루트노드를 출력

    for (j = 0; j < length; j++) {
        if (arry[j] == 'L'){
            temp = temp-> left;
            printf("%d ", temp->data);
        }
        if (arry[j] == 'R') {
            temp = temp->right;
            printf("%d ", temp->data);
        }
    }


    printf("\n");
    return;
}

int main() {
    node* tree;
    int cmdnum, cmdseacrh;

    scanf("%d", &cmdnum);
    getchar();

    int Lnum, Rnum, Onum;
    scanf("%d %d %d", &Onum, &Lnum, &Rnum);
    getchar();

    node* rootnode;
    rootnode = (node*)malloc(sizeof(node));
    rootnode->data = Onum;
    tree = rootnode;

    node* leftson;
    leftson = (node*)malloc(sizeof(node));
    leftson->data = Lnum;
    rootnode->left = leftson;
    if (Lnum != 0) Newnode(tree->left);

    node* rightson;
    rightson = (node*)malloc(sizeof(node));
    rightson->data = Rnum;
    rootnode->right = rightson;
    if (Rnum != 0) Newnode(tree->right);


    scanf("%d", &cmdseacrh);
    getchar();
    for (int i = 0; i < cmdseacrh; i++) search(tree);
    return 0;
}

/*
#define MAX_SIZE 10000

// 노드와 노드의 자리를 바꿔주는 함수
void nodeChange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 우선순위 큐 를 구조체 형태로 제작
typedef struct priorityQueue
{
    int heap[MAX_SIZE];
    // heap 의 배열형태

    int count;
    // heap 의 갯수 and 위치값 을 나타내는 값 (index 값이라 보면 된다.)
} priorityQueue;

// 우선순위 큐 삽입 PUSH
void push(priorityQueue *root, int data)
{
    if(root->count >= MAX_SIZE) return;
    // 만약 priorityQueue 의 노드의 갯수가 설정한 최대값보다 크다면 더이상 값을 추가할 수 없도록 합니다.

    root->heap[root->count] = data;
    // data값을 heap의 맨 마지막 트리에 저장
    // 예를 들면 트리가 총 3개가 존재한다면 count값 또한 3 이다.
    // 트리의 index 0 1 2 에 값을 PUSH 한다면
    // heap[count] = heap[3] 이기 때문에 무조건 마지막에 값이 저장된다.
    // 마지막에 값을 저장하면 index 0 1 2 3 이고 count 값 또한 증가되면서 4 가 된다.

    int now = root->count;
    // 추가한 data의 위치값 (index)

    int parent = (root->count - 1) / 2;
    // 추가한 data의 부모값
    // 부모값의 위치는 ( 현재 추가한 data 위치값 - 1 ) / 2 를 하면 찾을 수 있습니다.

    // 새 원소를 삽입한 이후에 상향식으로 최상단 루트까지 data 값을  힙을 구성합니다.
    while(now > 0 && root->heap[now] > root->heap[parent])
        // now > 0 비교하는 값의 위치가 최상단 루트가 될때까지 반복
        // heap[now] > heap[parent] 부모의 data 값보다 현재의 값이 더 크면 실행
    {
        nodeChange(&root->heap[now], &root->heap[parent]);
        // 부모값과 현재 값의 자리를 바꿔준다.
        now = parent;
        // 상향식으로 다시 위 부모 노드와 비교하기 위해서 부모값은 현재가 된다.
        parent = (parent - 1) / 2;
        // 부모값의 위치또한 다음 검사할 부모값의 위치를 저장한다.
    }

    root->count++;
    // PUSH 로 값을 추가하였으니 count 또한 1 증가 시킵니다.
}*/
