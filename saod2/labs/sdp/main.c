#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"

int main(void)
{
    int A[100];
    struct Node *sdp1 = NULL;
    struct Node *sdp2 = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, 100);

    for (int i = 0; i < 100; i++)
    {
        insertRecursive(&sdp1, A[i]);
        insertDouble(&sdp2, A[i]);
    }

    printf("Обход СДП1 слева направо:\n");
    inorder(sdp1);
    printf("\nОбход СДП2 слева направо:\n");
    inorder(sdp2);
    printf("\n");
    printExtras(A, 100, sdp1, sdp2);

    freeTree(sdp1);
    freeTree(sdp2);
    return 0;
}
