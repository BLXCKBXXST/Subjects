#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dbd.h"

#define TREE_N 100
#define MAX_N 500

int main(void)
{
    int A[MAX_N];
    struct Node *dbd = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, MAX_N);

    for (int i = 0; i < TREE_N; i++)
    {
        VR = HR = 0;
        B2INSERT(A[i], &dbd);
    }

    printf("Обход ДБД из %d вершин слева направо:\n", TREE_N);
    inorder(dbd);
    printf("\n\n");

    printDBDComparison(A, MAX_N);
    printf("Количество уровней страниц ДБД: %d\n", pageLevels(dbd));
    showDBDImage(dbd);

    freeTree(dbd);
    return 0;
}
