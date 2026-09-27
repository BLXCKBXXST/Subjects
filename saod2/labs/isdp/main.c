#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "compare.h"
#include "treeprint.h"
#include "search.h"

struct Node
{
    int Data;
    struct Node *Left;
    struct Node *Right;
};

struct Node *ISDP(int A[], int L, int R)
{
    if (L > R)
        return NULL;

    int m = (L + R) / 2;

    struct Node *p = malloc(sizeof(struct Node));

    p->Data = A[m];
    p->Left = ISDP(A, L, m - 1);
    p->Right = ISDP(A, m + 1, R);

    return p;
}

void printTree(struct Node *p)
{
    if (p != NULL)
    {
        printTree(p->Left);
        printf("%d ", p->Data);
        printTree(p->Right);
    }
}

int size(struct Node *p)
{
    if (p == NULL)
        return 0;

    int left = size(p->Left);
    int right = size(p->Right);
    int result = 1 + left + right;

    return result;
}

int checkSum(struct Node *p)
{
    if (p == NULL)
        return 0;

    return p->Data + checkSum(p->Left) + checkSum(p->Right);
}

int height(struct Node *p)
{
    if (p == NULL)
        return 0;

    int left = height(p->Left);
    int right = height(p->Right);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

int sumHeight(struct Node *p, int level)
{
    if (p == NULL)
        return 0;

    int left = sumHeight(p->Left, level + 1);
    int right = sumHeight(p->Right, level + 1);
    int sum = level + left + right;

    return sum;
}

int main()
{
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

    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }

    struct Node *root = ISDP(A, 0, 99);

    printf("обход слева направо:\n");
    printTree(root);

    printComparisonTable(root);

    printTreeVisual(root);

    int n = size(root);
    int sum = checkSum(root);
    int h = height(root);

    float averageHeight = (float)sumHeight(root, 1) / n;

    printf("\nразмер дерева: %d", n);
    printf("\nконтрольная сумма: %d", sum);
    printf("\nвысота дерева: %d", h);
    printf("\nсредняя высота: %.2f\n", averageHeight);

    searchMultiple(root);

    return 0;
}