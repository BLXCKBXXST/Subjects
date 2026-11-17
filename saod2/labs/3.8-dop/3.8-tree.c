#include <stdio.h>
#include <stdlib.h>
#include "3.8-dop.h"

void CreateTree(int L, int R, Vertex **Root)
{
    if (L < R)
    {
        int k = AR[L][R];
        addDOP(Root, k);
        CreateTree(L, k - 1, Root);
        CreateTree(k, R, Root);
    }
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
