#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"

int main(int argc, char *argv[])
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

    if (argc > 1 && argv[1][0] == '+')
        printExtras(A, 100, root);

    freeTree(root);
    return 0;
}
