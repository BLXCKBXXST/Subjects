#include "3.1-trees.h"

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return newNode(data);
    if (data < root->Data)
        root->Left = insert(root->Left, data);
    else
        root->Right = insert(root->Right, data);
    return root;
}

