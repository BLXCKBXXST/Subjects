#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void generateNumbers(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int value;
        int repeat;

        do
        {
            value = rand() % 1000 + 1;
            repeat = 0;

            for (int j = 0; j < i; j++)
                if (A[j] == value)
                    repeat = 1;
        } while (repeat);

        A[i] = value;
    }
}

void inorder(struct Node *p)
{
    if (p != NULL)
    {
        inorder(p->Left);
        printf("%d ", p->Data);
        inorder(p->Right);
    }
}

int size(struct Node *p)
{
    if (p == NULL)
        return 0;

    return 1 + size(p->Left) + size(p->Right);
}

int checkSum(struct Node *p)
{
    if (p == NULL)
        return 0;

    return p->Data + checkSum(p->Left) + checkSum(p->Right);
}

int height(struct Node *p)
{
    int left;
    int right;

    if (p == NULL)
        return 0;

    left = height(p->Left);
    right = height(p->Right);

    if (left > right)
        return left + 1;

    return right + 1;
}

int sumHeight(struct Node *p, int level)
{
    if (p == NULL)
        return 0;

    return level + sumHeight(p->Left, level + 1)
                 + sumHeight(p->Right, level + 1);
}

void freeTree(struct Node *p)
{
    if (p == NULL)
        return;

    freeTree(p->Left);
    freeTree(p->Right);
    free(p);
}
