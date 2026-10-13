#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

#define N 100

int main(void)
{
    int A[N];
    struct Node *root = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, N);

    for (int i = 0; i < N; i++)
        addAVL(A[i], &root);

    printf("Обход АВЛ-дерева слева направо:\n");
    inorder(root);
    printf("\n");

    printComparison(A, N, root);

    freeTree(root);
    return 0;
}
