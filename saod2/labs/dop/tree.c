#include <stdio.h>
#include <stdlib.h>
#include "dop.h"

Vertex *createTree(int L, int R)
{
    if (L >= R)
        return NULL;

    int k = AR[L][R];
    Vertex *p = malloc(sizeof(Vertex));
    p->Data = A[k].Data;
    p->Weight = A[k].Weight;
    p->Index = k;
    p->Left = createTree(L, k - 1);
    p->Right = createTree(k, R);
    return p;
}

void inorder(Vertex *p, int *count)
{
    if (p == NULL)
        return;

    inorder(p->Left, count);
    printf("%4d ", p->Data);
    (*count)++;
    if (*count % 20 == 0)
        printf("\n");
    inorder(p->Right, count);
}

void freeTree(Vertex *p)
{
    if (p == NULL)
        return;
    freeTree(p->Left);
    freeTree(p->Right);
    free(p);
}
