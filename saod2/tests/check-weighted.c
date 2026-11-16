#include <assert.h>
#include <stdlib.h>
#include "../labs/3.9-a1-a2/3.9-a1-a2.h"

Item A[N + 1];

static int ordered(Vertex *p, int lo, int hi)
{
    if (!p) return 0;
    assert(lo < p->Data && p->Data < hi);
    return 1 + ordered(p->Left, lo, p->Data) + ordered(p->Right, p->Data, hi);
}

int main(void)
{
    for (int n = 1; n <= 100; n++)
    {
        for (int i = 1; i <= n; i++)
        {
            A[i].Data = i;
            A[i].Weight = rand() % 100 + 1;
        }
        buildMatrices(n);
        Vertex *exact = createTree(0, n);
        Vertex *first = a1(n), *second = a2(1, n);
        assert(ordered(exact, 0, 1001) == n);
        assert(ordered(first, 0, 1001) == n);
        assert(ordered(second, 0, 1001) == n);
        assert(weightedSum(exact, 1) == AP[0][n]);
        assert(weightedSum(first, 1) >= AP[0][n]);
        assert(weightedSum(second, 1) >= AP[0][n]);
        freeTree(exact); freeTree(first); freeTree(second);
    }
    for (int i = 1; i <= N; i++)
    {
        A[i].Data = i;
        A[i].Weight = 1;
    }
    Vertex *tie = a1(N);
    assert(tie->Data == 1);
    assert(ordered(tie, 0, 1001) == N);
    freeTree(tie);
    return 0;
}
