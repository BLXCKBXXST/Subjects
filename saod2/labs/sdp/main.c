#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"

#define MAX_N 500

int main(void)
{
    int A[MAX_N];
    struct Node *sdp1 = NULL;
    struct Node *sdp2 = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, MAX_N);

    for (int n = 100; n <= MAX_N; n += 100)
    {
        for (int i = n - 100; i < n; i++)
        {
            insertRecursive(&sdp1, A[i]);
            insertDouble(&sdp2, A[i]);
        }

        printf("\n========== Вывод %d (n = %d) ==========\n", n / 100, n);
        printf("Обход ИСДП, СДП1 и СДП2 слева направо:\n");
        inorder(sdp1);
        printf("\n");
        printExtras(A, n, sdp1, sdp2);
    }

    freeTree(sdp1);
    freeTree(sdp2);
    return 0;
}
