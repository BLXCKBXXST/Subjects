#include <stdlib.h>
#include "3.9-a1-a2.h"

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

static int before(int i, int j)
{
    if (A[i].Weight != A[j].Weight)
        return A[i].Weight > A[j].Weight;
    return A[i].Data < A[j].Data;
}

static void quickSort(int order[], int L, int R)
{
    if (L >= R) return;
    int i = L, j = R;
    int pivot = order[L + (R - L) / 2];
    while (i <= j)
    {
        while (before(order[i], pivot)) i++;
        while (before(pivot, order[j])) j--;
        if (i <= j)
        {
            int t = order[i];
            order[i++] = order[j];
            order[j--] = t;
        }
    }
    if (L < j) quickSort(order, L, j);
    if (i < R) quickSort(order, i, R);
}

Vertex *a1(int n)
{
    int order[N + 1];
    Vertex *root = NULL;

    for (int i = 1; i <= n; i++)
        order[i] = i;

    quickSort(order, 1, n);

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
