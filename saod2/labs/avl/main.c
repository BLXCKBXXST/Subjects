#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

#define MAX_N 500
#define TREE_N 100

int main(void)
{
    int A[MAX_N];
    struct Node *root = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, MAX_N);

    for (int i = 0; i < TREE_N; i++)
        addAVL(A[i], &root);

    printf("Обход АВЛ-дерева из %d вершин слева направо:\n", TREE_N);
    inorder(root);
    printf("\n");

    printComparison(A, MAX_N);
    showTreeImage(root);
    searchMultiple(root);

    freeTree(root);
    return 0;
}
