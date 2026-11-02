#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dbd.h"

#define TREE_N 100

int main(void)
{
    int A[TREE_N];
    struct Node *dbd = NULL;
    struct Node *avl = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, TREE_N);

    for (int i = 0; i < TREE_N; i++)
    {
        VR = HR = 0;
        B2INSERT(A[i], &dbd);
        addAVL(A[i], &avl);
    }

    printf("Обход ДБД из %d вершин слева направо:\n", TREE_N);
    inorder(dbd);
    printf("\n\n");

    printComparison(dbd, avl, TREE_N);
    printf("Количество уровней страниц ДБД: %d\n", pageLevels(dbd));
    showDBDImage(dbd);

    freeTree(dbd);
    freeTree(avl);
    return 0;
}
