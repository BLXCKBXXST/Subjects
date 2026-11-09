#include <stdlib.h>
#include "dop.h"

Item A[N + 1];
int AW[N + 1][N + 1], AP[N + 1][N + 1], AR[N + 1][N + 1];

int compare(const void *a, const void *b)
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

void buildMatrices(int n)
{
    for (int i = 0; i <= n; i++)
    {
        AW[i][i] = 0;
        AP[i][i] = 0;
        AR[i][i] = 0;
    }

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            AW[i][j] = AW[i][j - 1] + A[j].Weight;

    for (int i = 0; i < n; i++)
    {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }

    for (int h = 2; h <= n; h++)
        for (int i = 0; i <= n - h; i++)
        {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];

            for (int k = m + 1; k <= AR[i + 1][j]; k++)
            {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min)
                {
                    min = x;
                    m = k;
                }
            }

            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
}
