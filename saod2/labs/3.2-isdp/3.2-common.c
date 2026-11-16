#include <stdio.h>
#include <stdlib.h>
#include "3.2-isdp.h"

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

void freeTree(struct Node *p)
{
    if (p == NULL) return;
    freeTree(p->Left);
    freeTree(p->Right);
    free(p);
}

void sortArray(int A[], int left, int right)
{
    if (left >= right) return;
    int i = left, j = right, pivot = A[left + (right - left) / 2];
    while (i <= j)
    {
        while (A[i] < pivot) i++;
        while (A[j] > pivot) j--;
        if (i <= j)
        {
            int t = A[i]; A[i] = A[j]; A[j] = t;
            i++; j--;
        }
    }
    sortArray(A, left, j);
    sortArray(A, i, right);
}
