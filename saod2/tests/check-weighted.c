#include <assert.h>
#include <stdlib.h>
#include "../labs/3.9-a1-a2/3.9-a1-a2.h"

Item A[N + 1];

static int ordered(Vertex *p, int lo, int hi)
{
    if (!p) return 0;
    assert(lo <= p->Data && p->Data < hi);
    assert(p->Index >= 1 && p->Index <= N);
    assert(p->Data == A[p->Index].Data);
    assert(p->Weight == A[p->Index].Weight);
    return 1 + ordered(p->Left, lo, p->Data) + ordered(p->Right, p->Data, hi);
}

static void input(WeightedItem V[], int n)
{
    for (int i = 1; i <= n; i++)
        V[i] = (WeightedItem){A[i].Data, A[i].Weight, i};
}

static void once(Vertex *p, int seen[])
{
    if (!p) return;
    assert(seen[p->Index]++ == 0);
    once(p->Left, seen);
    once(p->Right, seen);
}

static void duplicates(void)
{
    int keys[] = {0, 1, 1, 2, 2, 2, 3, 3};
    int weights[] = {0, 1, 3, 2, 9, 2, 1, 4};
    WeightedItem V1[N + 1], V2[N + 1];
    for (int i = 1; i <= 7; i++)
        A[i] = (Item){keys[i], weights[i]};
    input(V1, 7); input(V2, 7);
    Vertex *first = NULL, *second = NULL;
    A1(V1, 7, &first);
    A2(V2, 1, 7, &second);
    assert(ordered(first, 0, 1001) == 7);
    assert(ordered(second, 0, 1001) == 7);
    int seen1[N + 1] = {0}, seen2[N + 1] = {0};
    once(first, seen1); once(second, seen2);
    for (int i = 1; i <= 7; i++) assert(seen1[i] == 1 && seen2[i] == 1);
    freeTree(first); freeTree(second);

    for (int i = 1; i <= 3; i++) A[i] = (Item){5, 1};
    input(V2, 3);
    second = NULL;
    A2(V2, 1, 3, &second);
    assert(second->Index == 2 && second->Left == NULL);
    assert(second->Right->Index == 1 && second->Right->Left == NULL);
    assert(second->Right->Right->Index == 3);
    assert(ordered(second, 0, 1001) == 3);
    freeTree(second);
}

int main(void)
{
    Vertex *empty = NULL;
    A1(NULL, 0, &empty);
    A2(NULL, 1, 0, &empty);
    QuickSortKeys(NULL, 1, 0);
    assert(empty == NULL);
    for (int n = 1; n <= 100; n++)
    {
        WeightedItem V1[N + 1], V2[N + 1];
        int maxWeight = 0;
        for (int i = 1; i <= n; i++)
        {
            A[i].Data = i;
            A[i].Weight = rand() % 100 + 1;
            if (A[i].Weight > maxWeight) maxWeight = A[i].Weight;
        }
        input(V1, n); input(V2, n);
        buildMatrices(n);
        Vertex *exact = createTree(0, n);
        Vertex *first = NULL, *second = NULL;
        A1(V1, n, &first);
        A2(V2, 1, n, &second);
        assert(first->Weight == maxWeight);
        for (int i = 2; i <= n; i++) assert(V1[i - 1].Weight >= V1[i].Weight);
        for (int i = 1; i <= n; i++) assert(V2[i].Data == i);
        assert(ordered(exact, 0, 1001) == n);
        assert(ordered(first, 0, 1001) == n);
        assert(ordered(second, 0, 1001) == n);
        assert(weightedSum(exact, 1) == AP[0][n]);
        assert(weightedSum(first, 1) >= AP[0][n]);
        assert(weightedSum(second, 1) >= AP[0][n]);
        freeTree(exact); freeTree(first); freeTree(second);
    }
    WeightedItem V[N + 1];
    for (int i = 1; i <= N; i++) A[i] = (Item){i, 1};
    input(V, N);
    Vertex *tie = NULL;
    A1(V, N, &tie);
    assert(tie->Weight == 1);
    assert(ordered(tie, 0, 1001) == N);
    freeTree(tie);

    int cases[][5] = {{2, 1, 2, 0, 0}, {10, 1, 1, 1, 1}, {1, 1, 1, 1, 10}};
    int sizes[] = {3, 5, 5}, roots[] = {2, 1, 5};
    for (int t = 0; t < 3; t++)
    {
        for (int i = 1; i <= sizes[t]; i++) A[i] = (Item){i, cases[t][i - 1]};
        input(V, sizes[t]);
        Vertex *tree = NULL;
        A2(V, 1, sizes[t], &tree);
        assert(tree->Data == roots[t]);
        assert(ordered(tree, 0, 1001) == sizes[t]);
        freeTree(tree);
    }
    duplicates();

    Item keys[] = {{0, 0}, {4, 41}, {1, 11}, {4, 42}, {2, 21}};
    QuickSortKeys(keys, 1, 4);
    assert(keys[1].Data == 1 && keys[1].Weight == 11);
    assert(keys[2].Data == 2 && keys[2].Weight == 21);
    assert(keys[3].Data == 4 && keys[4].Data == 4);
    assert(keys[3].Weight + keys[4].Weight == 83);
    generate();
    for (int i = 1; i <= N; i++)
    {
        assert(A[i].Data >= 1 && A[i].Data <= MAX_KEY);
        assert(A[i].Weight >= 1 && A[i].Weight <= 100);
        if (i > 1) assert(A[i - 1].Data < A[i].Data);
    }
    return 0;
}
