#include <stdio.h>
#include <stdlib.h>
#include "compare.h"

struct Node
{
    int Data;
    struct Node *Left;
    struct Node *Right;
};

struct Node *ISDP(int A[], int L, int R);
int size(struct Node *p);
int checkSum(struct Node *p);
int height(struct Node *p);
int sumHeight(struct Node *p, int level);

static void fillArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int x;
        int repeat;

        do
        {
            x = rand() % 10000 + 1;
            repeat = 0;

            for (int j = 0; j < i; j++)
            {
                if (A[j] == x)
                    repeat = 1;
            }

        } while (repeat == 1);

        A[i] = x;
    }
}

static void sortArray(int A[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

static void freeTree(struct Node *p)
{
    if (p == NULL)
        return;

    freeTree(p->Left);
    freeTree(p->Right);

    free(p);
}

static void printRow(int n, struct Node *root)
{
    int treeSize = size(root);
    int sum = checkSum(root);
    int h = height(root);

    float averageHeight =
        (float)sumHeight(root, 1) / treeSize;

    printf("│ %3d │ %6d │ %17d │ %6d │ %15.2f │\n",
           n,
           treeSize,
           sum,
           h,
           averageHeight);
}

void printComparisonTable(struct Node *root)
{
    int N[] = {200, 300, 400, 500};

    printf("\n\nХарактеристики ИСДП\n\n");

    printf("┌─────┬────────┬───────────────────┬────────┬─────────────────┐\n");
    printf("│  N  │ Размер │ Контрольная сумма │ Высота │ Средняя высота  │\n");
    printf("├─────┼────────┼───────────────────┼────────┼─────────────────┤\n");

    // Исходное дерево из main
    printRow(100, root);

    for (int t = 0; t < 4; t++)
    {
        int n = N[t];

        int *A = malloc(n * sizeof(int));

        fillArray(A, n);
        sortArray(A, n);

        struct Node *tree = ISDP(A, 0, n - 1);

        printRow(n, tree);

        freeTree(tree);
        free(A);
    }

    printf("└─────┴────────┴───────────────────┴────────┴─────────────────┘\n");
}