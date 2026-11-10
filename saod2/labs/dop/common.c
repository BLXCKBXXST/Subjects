#include <stdlib.h>
#include "dop.h"

static int compare(const void *a, const void *b)
{
    return ((Item *)a)->Data - ((Item *)b)->Data;
}

void generate(void)
{
    int a[MAX_KEY];
    for (int i = 0; i < MAX_KEY; i++)
        a[i] = i + 1;

    for (int i = MAX_KEY - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    for (int i = 1; i <= N; i++)
    {
        A[i].Data = a[i - 1];
        A[i].Weight = rand() % 100 + 1;
    }

    qsort(A + 1, N, sizeof(Item), compare);
}
