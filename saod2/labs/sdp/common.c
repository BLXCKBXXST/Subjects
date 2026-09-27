#include <stdio.h>
#include <stdlib.h>
#include "sdp.h"

void generateNumbers(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int value, repeat;
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

void inorder(struct Node *root)
{
    if (root == NULL)
        return;
    inorder(root->Left);
    printf("%d ", root->Data);
    inorder(root->Right);
}

int size(struct Node *root)
{
    if (root == NULL)
        return 0;
    return 1 + size(root->Left) + size(root->Right);
}

int checkSum(struct Node *root)
{
    if (root == NULL)
        return 0;
    return root->Data + checkSum(root->Left) + checkSum(root->Right);
}

int height(struct Node *root)
{
    if (root == NULL)
        return 0;
    int left = height(root->Left);
    int right = height(root->Right);
    return 1 + (left > right ? left : right);
}

int sumHeight(struct Node *root, int level)
{
    if (root == NULL)
        return 0;
    return level + sumHeight(root->Left, level + 1)
                 + sumHeight(root->Right, level + 1);
}

void printStats(struct Node *root)
{
    int n = size(root);
    printf("Размер дерева: %d\n", n);
    printf("Контрольная сумма: %d\n", checkSum(root));
    printf("Высота дерева: %d\n", height(root));
    printf("Средняя высота: %.2f\n", n ? (double)sumHeight(root, 1) / n : 0);
}

void freeTree(struct Node *root)
{
    if (root == NULL)
        return;
    freeTree(root->Left);
    freeTree(root->Right);
    free(root);
}
