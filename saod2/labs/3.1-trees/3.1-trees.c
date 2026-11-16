#include <stdio.h>
#include <stdlib.h>
#include "3.1-trees.h"

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) exit(1);
    node->Data = data;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->Data);
    preorder(root->Left);
    preorder(root->Right);
}

void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->Left);
    printf("%d ", root->Data);
    inorder(root->Right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->Left);
    postorder(root->Right);
    printf("%d ", root->Data);
}

int size(struct Node* root) {
    if (root == NULL) return 0;
    return 1 + size(root->Left) + size(root->Right);
}

int checksum(struct Node* root) {
    if (root == NULL) return 0;
    return root->Data + checksum(root->Left) + checksum(root->Right);
}

int height(struct Node* root) {
    if (root == NULL) return 0;
    int hLeft = height(root->Left);
    int hRight = height(root->Right);
    if (hLeft > hRight)
        return hLeft + 1;
    else
        return hRight + 1;
}

void sumHeights(struct Node* root, int level, int *sum) {
    if (root == NULL) return;
    *sum = *sum + level;
    sumHeights(root->Left, level + 1, sum);
    sumHeights(root->Right, level + 1, sum);
}


void freeTree(struct Node *root)
{
    if (root == NULL) return;
    freeTree(root->Left);
    freeTree(root->Right);
    free(root);
}
