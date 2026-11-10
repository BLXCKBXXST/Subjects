#include <stdlib.h>
#include "a1a2.h"

static void insertA1(Vertex **p, int k)
{
    if (*p == NULL)
    {
        *p = malloc(sizeof(Vertex));
        (*p)->Data = A[k].Data;
        (*p)->Weight = A[k].Weight;
        (*p)->Index = k;
        (*p)->Left = (*p)->Right = NULL;
        return;
    }

    if (A[k].Data < (*p)->Data)
        insertA1(&(*p)->Left, k);
    else
        insertA1(&(*p)->Right, k);
}

Vertex *a1(int n)
{
    int order[N + 1];
    Vertex *root = NULL;

    for (int i = 1; i <= n; i++)
        order[i] = i;

    for (int i = 1; i < n; i++)
        for (int j = 1; j <= n - i; j++)
            if (A[order[j]].Weight < A[order[j + 1]].Weight)
            {
                int t = order[j];
                order[j] = order[j + 1];
                order[j + 1] = t;
            }

    for (int i = 1; i <= n; i++)
        insertA1(&root, order[i]);

    return root;
}

Vertex *a2(int L, int R)
{
    if (L > R) return NULL;

    int total = 0, sum = 0, i;
    for (i = L; i <= R; i++) total += A[i].Weight;

    for (i = L; i < R; i++)
    {
        if (2 * (sum + A[i].Weight) >= total) break;
        sum += A[i].Weight;
    }

    Vertex *p = malloc(sizeof(Vertex));
    p->Data = A[i].Data;
    p->Weight = A[i].Weight;
    p->Index = i;
    p->Left = a2(L, i - 1);
    p->Right = a2(i + 1, R);
    return p;
}
