#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* Parent, *Left, *Right;
}Node;

int GetHeight(Node* node){
    if(node == NULL) return 0;

    int leftDepth = GetHeight(node->Left);
    int rightDepth = GetHeight(node->Right);

    return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}

int CalculateBalanceFactor(Node* node){
    return GetHeight(node->Left) - GetHeight(node->Right);
}

Node* LL(Node* node){
    Node *childNode = node->Left;
    node->Left = childNode->Right;
    if (childNode->Right != NULL)
        childNode->Right->Parent = node;

    childNode->Right = node;
    childNode->Parent = node->Parent;
    node->Parent = childNode;

    return childNode;
}

Node* RR(Node* node){
    Node *childNode = node->Right;
    node->Right = childNode->Left;
    if(childNode->Left != NULL)
        childNode->Left->Parent = node;

    childNode->Left = node;
    childNode->Parent = node->Parent;
    node->Parent = childNode;

    return childNode;
}

Node* LR(Node* node){
    node->Left = RR(node->Left);
    return LL(node);
}

Node* RL(Node* node){
    node->Right = LL(node->Right);
    return RR(node);
}

Node* AVLSet(Node* node){
    int depth = CalculateBalanceFactor(node);
    if (depth >= 2) {
        depth = CalculateBalanceFactor(node->Left);
        if (depth >= 1) {
            node = LL(node);
        }
        else{
            node = LR(node);
        }
    }
    else if (depth <= -2) {
        depth = CalculateBalanceFactor(node->Right);
        if (depth <= -1) {
            node = RR(node);
        }
        else{
            node = RL(node);
        }
    }
    return node;
}

Node* Insert(Node* node, int data){
    if (node == NULL) {
        node = (Node *) malloc(sizeof(Node));
        node->Left = NULL;
        node->Right = NULL;
        node->Parent = NULL;
        node->data = data;

        return node;
    }
    else if (data < node->data) {
        node->Left = Insert(node->Left, data);
        node->Left->Parent = node;
        node = AVLSet(node);
    }
    else if(data > node->data){
        node->Right = Insert(node->Right, data);
        node->Right->Parent = node;
        node = AVLSet(node);
    }
    else{

    }
    return node;
}

Node* GetMinNode(Node* node, Node* parent){
    if(node->Left == NULL){
        if(node->Parent != NULL){
            if(parent != node->Parent){
                node->Parent->Left = node->Right;
            }
            else{
                node->Parent->Right = node->Right;
            }
            if(node->Right != NULL){
                node->Right->Parent = node->Parent;
            }
        }
        return node;
    }
    else{
        return GetMinNode(node->Left, parent);
    }
}

Node* Delete(Node* node, int data)
{
    if (node == NULL) return NULL;

    if (data < node->data)
    {
        node->Left = Delete(node->Left, data);
        node = AVLSet(node);
    }
    else if (data > node->data)
    {
        node->Right = Delete(node->Right, data);
        node = AVLSet(node);
    }
    else
    {
        if (node->Left == NULL && node->Right == NULL)
        {
            node = NULL;
        }
        else if (node->Left != NULL && node->Right == NULL)
        {
            node->Left->Parent = node->Parent;
            node = node->Left;
        }
        else if (node->Left == NULL && node->Right != NULL)
        {
            node->Right->Parent = node->Parent;
            node = node->Right;
        }
        else
        {
            Node* deleteNode = node;
            Node* minNode = GetMinNode(node->Right, deleteNode);

            minNode->Parent = node->Parent;

            minNode->Left = deleteNode->Left;
            if (deleteNode->Left != NULL)
            {
                deleteNode->Left->Parent = minNode;
            }

            minNode->Right = deleteNode->Right;
            if (deleteNode->Right != NULL)
            {
                deleteNode->Right->Parent = minNode;
            }

            node = minNode;
            free(deleteNode);
        }
    }

    return node;
}

void Inorder(Node* node)
{
    if (node == NULL) return;

    printf(" %d", node->data);
    Inorder(node->Left);
    Inorder(node->Right);
}

int findElement(Node* node, int key){
    if(node == NULL)
        return -1;
    if(node->data == key) {
        return key;
    }
    else if(node->data > key)
        return findElement(node->Left, key);
    else
        return findElement(node->Right, key);
}
int main() {
    Node *root = NULL;

    char cmd;
    int e, data;

    while(1){
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d",&data);
                root = Insert(root, data);
                getchar();
                break;
            case 's':
                scanf("%d", &data);
                e = findElement(root, data);
                if(e == -1) printf("X\n");
                else printf("%d\n", e);
                getchar();
                break;
            case 'p':
                Inorder(root);
                puts("");
                break;
            case 'd':
                scanf("%d", &data);
                Node *tmp = Delete(root, data);
                if (tmp == NULL) {
                    printf("X\n");
                }
                else {
                    root = tmp;
                    printf("%d\n", data);
                }
                break;
            case 'q':
                return -1;
            default:
                break;
        }

    }
    return 0;
}


