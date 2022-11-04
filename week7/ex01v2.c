#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* lChild;
    struct node* rChild;
    struct node* parent;
    int key;
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
                else
                    printf("%d\n", e);
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

    if(!isExternal(sp)) {
        puts("duplicated!");
        return NULL;
    }
    else {
        sp->key = k;
        expandExternal(sp);
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
int removeElement(NODE* root, int k){
    NODE *np = treeSearch(root, k);
    int result = np->key;

    if(isExternal(np))
        return -1;

    if (isInternal(np->lChild) && isInternal(np->rChild)) {
        NODE *sp = inOrderSucc(np);
        np->key = sp->key;

        if (isLeftChild(sp))
            sp->parent->lChild = sp->rChild;
        else
            sp->parent->rChild = sp->rChild;
    }
    else if (!isInternal(np->lChild)) {
        if(isLeftChild(np))
            np->parent->lChild = np->rChild;
        else
            np->parent->rChild = np->rChild;

        free(np->lChild);
        free(np);
    }
    else{
        if(isLeftChild(np))
            np->parent->lChild = np->lChild;
        else
            np->parent->rChild = np->lChild;

        free(np->rChild);
        free(np);
    }
    return result;
}
bool isExternal(NODE* np){
    if(np->lChild == NULL && np->rChild == NULL)
        return true;
    else
        return false;
}
bool isInternal(NODE* np){
    if(np->lChild != NULL || np->rChild != NULL)
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
        return NULL;
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











