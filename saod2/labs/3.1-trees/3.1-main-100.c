#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "3.1-trees.h"
#include "../lab-viewer.h"
#define TREE_SIZE 100
#define MAX_VALUE 100
struct Node *insert(struct Node *root, int data);

int main(int argc, char **argv) {
    (void)argc;
    if (!initLabPaths(argv[0])) return 1;
    srand(time(NULL));

    struct Node* root = NULL;
    for (int i = 0; i < TREE_SIZE; i++)
        root = insert(root, rand() % MAX_VALUE);


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

    int ok = showTree(root, 1);
    freeTree(root);
    return ok ? 0 : 1;
}
