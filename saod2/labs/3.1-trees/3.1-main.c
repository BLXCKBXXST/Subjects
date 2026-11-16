#include <stdio.h>
#include "3.1-trees.h"
#include "../lab-viewer.h"

int main(int argc, char **argv) {
    (void)argc;
    if (!initLabPaths(argv[0])) return 1;
    struct Node* root = newNode(4);
    root->Left = newNode(9);
    root->Right = newNode(11);
    root->Right->Left = newNode(7);
    root->Left->Left = newNode(2);
    root->Right->Right = newNode(6);
    root->Right->Right->Left = newNode(13);

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

    int ok = showTree(root, 0);
    freeTree(root);
    return ok ? 0 : 1;
}