#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "3.3-sdp.h"
#include "../lab-viewer.h"

#define MAX_N 500

int main(int argc, char **argv)
{
    (void)argc;
    if (!initLabPaths(argv[0])) return 1;
    int A[MAX_N];
    struct Node *sdp1 = NULL;
    struct Node *sdp2 = NULL;

    srand((unsigned)time(NULL));

    for (int i = 0; i < MAX_N; i++)
        A[i] = rand() % 1000 + 1;

    A[1] = A[0];

    printf("Гарантированный повтор: %d %d\n", A[0], A[1]);

    for (int i = 0; i < 100; i++)
    {
        insertRecursive(&sdp1, A[i]);
        insertDouble(&sdp2, A[i]);
    }

    printf("Обход ИСДП, СДП1 и СДП2 слева направо:\n");
    inorder(sdp1);
    printf("\n");

    printSummary(A, MAX_N);
    int ok = printExtras(A, 100, sdp1, sdp2);

    searchMultiple(sdp1);

    freeTree(sdp1);
    freeTree(sdp2);
    return ok ? 0 : 1;
}
