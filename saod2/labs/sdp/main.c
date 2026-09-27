#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"

int main(void)
{
    int A[100];
    struct Node *root = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, 100);

    for (int i = 0; i < 100; i++)
        insert(&root, A[i]);

    printf("Обход слева направо:\n");
    inorder(root);
    printf("\n");
    printStats(root);
    printExtras(A, 100);

    freeTree(root);
    return 0;
}
