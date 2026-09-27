#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
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
    printf("       4\n");
    printf("      / \\\n");
    printf("     9   11\n");
    printf("    /   / \\\n");
    printf("   2   7   6\n");
    printf("          /\n");
    printf("         13\n");
    struct Node* root = newNode(4);
    root->left = newNode(9);
    root->right = newNode(11);
    root->right->left = newNode(7);
    root->left->left = newNode(2);
    root->right->right = newNode(6);
    root->right->right->left = newNode(13);

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