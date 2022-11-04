#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* lChild;
    struct node* rChild;
    struct node* parent;
    int key;
    int height;
}NODE;

typedef enum {
    false, true
} bool;

NODE* getNode();
int findElement(NODE* np, int k);
NODE* insertItem(NODE* np, int k);
NODE* treeSearch(NODE* np, int k);
int removeElement(NODE* np, int k);
bool isExternal(NODE* np);
bool isInternal(NODE* np);
bool isRoot(NODE* np);
bool isLeftChild(NODE* np);
NODE* inOrderSucc(NODE* np);
NODE* expandExternal(NODE* np);
NODE* reduceExternal(NODE* np);
void printTree(NODE* np);
void GetHeight(NODE* np){

    if(isExternal(np)){
        np->height = 0;
        return;
    }
    GetHeight(np->lChild);
    GetHeight(np->rChild);

    int leftDepth = np->lChild->height;
    int rightDepth = np->rChild->height;

    if(leftDepth > rightDepth)
        np->height = leftDepth + 1;
    else
        np->height = rightDepth + 1;
}
int CalculateBalanceFactor(NODE* np){
    return np->lChild->height - np->rChild->height;
}
// LL 일 경우 회전후 바뀐 루트 노드 반환
NODE* LL(NODE* np){
    NODE *child = np->lChild;
    np->lChild = child->rChild;
    child->rChild->parent = np;

    child->rChild = np;
    child->parent = np->parent;
    np->parent = child;

    return child;
}
// RR 일 경우
NODE* RR(NODE* np){
    NODE *child = np->rChild;
    np->rChild = child->lChild;
    child->lChild->parent = np;

    child->lChild = np;
    child->parent = np->parent;
    np->parent = child;

    return child;
}
NODE* RL(NODE* np){
    np->rChild = LL(np->rChild);
    return RR(np);
}
NODE* LR(NODE* np){
    np->lChild = RR(np->lChild);
    return LL(np);
}
NODE* AVLSet(NODE* np){
    int depth = CalculateBalanceFactor(np);
    if (depth >= 2) {
        depth = CalculateBalanceFactor(np->lChild);
        //np 의 왼쪽 노드의 불균형을 판단
        if(depth >= 1)      // LL
            np = LL(np);
        else
            np = LR(np);    //LR
    }
    else if (depth <= -2) {
        depth = CalculateBalanceFactor(np->rChild);
        //np 의 오른쪽 노드가 불균형일 경우
        if(depth <= -1)
            np = RR(np);
        else
            np = RL(np);
    }
    //높이 재설정
    GetHeight(np);

    return np;
}

int main() {
    NODE *root = getNode();

    char cmd;
    int data, e;

    while(1) {
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d", &data);
                getchar();
                root = insertItem(root, data);
                break;
            case 'd':
                scanf("%d", &data);
                getchar();
                e = removeElement(root, data);
                if(e == -1)
                    printf("X\n");
                else {
                    GetHeight(root);
                    root = AVLSet(root);
                    printf("%d\n", e);
                }
                break;
            case 's':
                scanf("%d", &data);
                getchar();
                e = findElement(root, data);
                if(e == -1)
                    printf("X\n");
                else
                    printf("%d\n", e);
                break;
            case 'p':
                printTree(root);
                puts("");
                break;
            case 'q':
                return -1;
            default:
                break;
        }
    }

    return 0;
}


NODE* getNode(){
    NODE* new = (NODE*) malloc(sizeof(NODE));
    new->rChild = NULL;
    new->lChild = NULL;
    new->parent = NULL;
    new->height = 0;
    return new;
}
int findElement(NODE* np, int k){

    NODE *sp = treeSearch(np, k);
    if(isExternal(sp))
        return -1;
    else
        return sp->key;
}
NODE* insertItem(NODE* np, int k){
    NODE *sp = treeSearch(np, k);

    if(isExternal(sp)) {
        sp->key = k;
        expandExternal(sp);
        GetHeight(np);
        np = AVLSet(np);
    }

    return np;
}
NODE* treeSearch(NODE* np, int k){

    if(isExternal(np))
        return np;

    if(np->key == k)
        return np;
    else if(np->key > k)
        return treeSearch(np->lChild, k);
    else
        return treeSearch(np->rChild, k);
}
int removeElement(NODE* np, int key){
    NODE *sp = treeSearch(np, key);
    int result;
    if(isExternal(sp)) return -1;
    else
        result = sp->key;

    if (isExternal(sp->lChild) && isExternal(sp->rChild)) {
        result = sp->key;
        free(sp->lChild);
        free(sp->rChild);
        sp->lChild = NULL;
        sp->rChild = NULL;
    }
    else if (isInternal(sp->lChild) && isExternal(sp->rChild)) {
        free(sp->rChild);
        NODE *left = sp->lChild;
        sp->key = left->key;
        sp->lChild = left->lChild;
        left->lChild->parent = sp;
        sp->rChild = left->rChild;
        left->rChild->parent = sp;
        free(left);
    }
    else if (isExternal(sp->lChild) && isInternal(sp->rChild)) {
        free(sp->lChild);
        NODE *right = sp->rChild;
        sp->key = right->key;
        sp->lChild = right->lChild;
        right->lChild->parent = sp;
        sp->rChild = right->rChild;
        right->rChild->parent = sp;
        free(right);
    }
    else{
        NODE *cur = inOrderSucc(sp);
        sp->key = cur->key;
        if (isLeftChild(cur)) {
            cur->parent->lChild = cur->rChild;
            cur->rChild->parent = cur->parent;
        }
        else {
            cur->parent->rChild = cur->rChild;
            cur->rChild->parent = cur->parent;
        }
        free(cur->lChild);
        free(cur);
    }

    return result;
}
bool isInternal(NODE* np){
    if(np == NULL) return false;
    if(np->lChild != NULL || np->rChild != NULL)
        return true;
    else
        return false;
}
bool isExternal(NODE* np){
    if(np == NULL) return true;
    if(np->lChild == NULL && np->rChild == NULL)
        return true;
    else
        return false;
}
bool isLeftChild(NODE* np){
    if(np->parent->lChild == np)
        return true;
    else
        return false;
}
NODE* inOrderSucc(NODE* np){
    NODE *sp = np->rChild;

    while (isInternal(sp->lChild)) {
        sp = sp->lChild;
    }
    return sp;
}
NODE* expandExternal(NODE* np){
    if(!isExternal(np)){
        puts("expand error!");
        return np;
    }
    np->lChild = getNode();
    np->lChild->parent = np;
    np->rChild = getNode();
    np->rChild->parent = np;

    return np;
}

void printTree(NODE* np){
    if(isExternal(np))
        return;

    printf(" %d", np->key);
    printTree(np->lChild);
    printTree(np->rChild);
}











