#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TREE_SIZE 100
#define MAX_VALUE 100

#include "treeprint.h"

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int size(struct Node* root) {
    if (root == NULL) return 0;
    return 1 + size(root->left) + size(root->right);
}

int checksum(struct Node* root) {
    if (root == NULL) return 0;
    return root->data + checksum(root->left) + checksum(root->right);
}

int height(struct Node* root) {
    if (root == NULL) return 0;
    int hLeft = height(root->left);
    int hRight = height(root->right);
    if (hLeft > hRight)
        return hLeft + 1;
    else
        return hRight + 1;
}

void sumHeights(struct Node* root, int level, int *sum) {
    if (root == NULL) return;
    *sum = *sum + level;
    sumHeights(root->left, level + 1, sum);
    sumHeights(root->right, level + 1, sum);
}

int main() {
    srand(time(NULL));

    struct Node* root = NULL;
    for (int i = 0; i < TREE_SIZE; i++)
        root = insert(root, rand() % MAX_VALUE);

    printf("Дерево (корень слева, правое поддерево сверху):\n");
    printTree(root, 0);
    printf("\n");

    printf("Обход сверху вниз:  ");
    preorder(root);
    printf("\n");

    printf("Обход слева направо: ");
    inorder(root);
    printf("\n");

    printf("Обход снизу вверх:  ");
    postorder(root);
    printf("\n");

    int n = size(root);
    int sum = 0;

    printf("Размер дерева: %d\n", n);
    printf("Контрольная сумма: %d\n", checksum(root));
    printf("Высота дерева: %d\n", height(root));

    sumHeights(root, 1, &sum);   /* считаем сумму уровней, у корня уровень 1 */
    printf("Средняя высота: %.2f\n", (float)sum / n);

    return 0;
}
