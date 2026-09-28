#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"

void insertRecursive(struct Node **root, int value)
{
    if (*root == NULL)
    {
        *root = malloc(sizeof(struct Node));
        if (*root == NULL)
            exit(1);
        (*root)->Data = value;
        (*root)->Left = NULL;
        (*root)->Right = NULL;
        return;
    }

    if (value < (*root)->Data)
        insertRecursive(&(*root)->Left, value);
    else if (value > (*root)->Data)
        insertRecursive(&(*root)->Right, value);
}

void insertDouble(struct Node **root, int value)
{
    while (*root != NULL)
    {
        if (value < (*root)->Data)
            root = &(*root)->Left;
        else if (value > (*root)->Data)
            root = &(*root)->Right;
        else
            return;
    }

    *root = malloc(sizeof(struct Node));
    if (*root == NULL)
        exit(1);
    (*root)->Data = value;
    (*root)->Left = NULL;
    (*root)->Right = NULL;
}

#define MAX_N 500

int main(void)
{
    int A[MAX_N];
    struct Node *sdp1 = NULL;
    struct Node *sdp2 = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, MAX_N);

    for (int i = 0; i < 100; i++)
    {
        insertRecursive(&sdp1, A[i]);
        insertDouble(&sdp2, A[i]);
    }

    printf("Обход ИСДП, СДП1 и СДП2 слева направо:\n");
    inorder(sdp1);
    printf("\n");
    printSummary(A, MAX_N);
    printExtras(A, 100, sdp1, sdp2);

    freeTree(sdp1);
    freeTree(sdp2);
    return 0;
}
