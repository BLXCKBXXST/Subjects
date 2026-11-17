#include "3.9-a1-a2.h"

void A1(WeightedItem V[], int n, Vertex **root)
{
    QuickSort(V, 1, n);
    for (int i = 1; i <= n; i++)
        add(root, V[i]);
}

void A2(WeightedItem V[], int L, int R, Vertex **root)
{
    int wes = 0, sum = 0, i;

    if (L <= R)
    {
        for (i = L; i <= R; i++)
            wes = wes + V[i].Weight;

        for (i = L; i <= R; i++)
        {
            if (2 * sum < wes && 2 * (sum + V[i].Weight) >= wes)
                break;
            sum = sum + V[i].Weight;
        }

        add(root, V[i]);
        A2(V, L, i - 1, root);
        A2(V, i + 1, R, root);
    }
}
