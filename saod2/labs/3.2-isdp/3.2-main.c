#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "3.2-isdp.h"
#include "../lab-viewer.h"

int main(int argc, char **argv)
{
    (void)argc;
    if (!initLabPaths(argv[0])) return 1;
    int A[100];

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        int x;
        int repeat;

        do
        {
            x = rand() % 1000 + 1;
            repeat = 0;

            for (int j = 0; j < i; j++)
            {
                if (A[j] == x)
                    repeat = 1;
            }

        } while (repeat == 1);

        A[i] = x;
    }

    sortArray(A, 0, 99);

    struct Node *root = ISDP(A, 0, 99);

    printf("обход слева направо:\n");
    printTree(root);

    printComparisonTable(root);

    if (!saveTreeSvg("3.2-isdp.svg", root))
    {
        perror("3.2-isdp.svg");
        freeTree(root);
        return 1;
    }
    openLabPage("labs/3.2-isdp/3.2-view.html");

    int n = size(root);
    int sum = checkSum(root);
    int h = height(root);

    float averageHeight = (float)sumHeight(root, 1) / n;

    printf("\nразмер дерева: %d", n);
    printf("\nконтрольная сумма: %d", sum);
    printf("\nвысота дерева: %d", h);
    printf("\nсредняя высота: %.2f\n", averageHeight);

    searchMultiple(root);

    freeTree(root);
    return 0;
}