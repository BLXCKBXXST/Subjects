#include "3.9-a1-a2.h"

void QuickSort(WeightedItem V[], int L, int R)
{
    if (L >= R) return;
    int i = L, j = R;
    int x = V[(L + R) / 2].Weight;

    do
    {
        while (V[i].Weight > x) i++;
        while (V[j].Weight < x) j--;
        if (i <= j)
        {
            WeightedItem temp = V[i];
            V[i] = V[j];
            V[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if (L < j) QuickSort(V, L, j);
    if (i < R) QuickSort(V, i, R);
}

void QuickSortKeys(Item V[], int L, int R)
{
    if (L >= R) return;
    int i = L, j = R;
    int x = V[(L + R) / 2].Data;

    do
    {
        while (V[i].Data < x) i++;
        while (V[j].Data > x) j--;
        if (i <= j)
        {
            Item temp = V[i];
            V[i] = V[j];
            V[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if (L < j) QuickSortKeys(V, L, j);
    if (i < R) QuickSortKeys(V, i, R);
}
