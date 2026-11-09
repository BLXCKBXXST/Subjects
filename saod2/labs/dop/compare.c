#include <stdio.h>
#include "dop.h"

int size(Vertex *p)
{
    if (p == NULL)
        return 0;
    return 1 + size(p->Left) + size(p->Right);
}

int checksum(Vertex *p)
{
    if (p == NULL)
        return 0;
    return p->Data + checksum(p->Left) + checksum(p->Right);
}

int height(Vertex *p)
{
    if (p == NULL)
        return 0;
    int l = height(p->Left);
    int r = height(p->Right);
    return 1 + (l > r ? l : r);
}

int weightedSum(Vertex *p, int level)
{
    if (p == NULL)
        return 0;
    return p->Weight * level + weightedSum(p->Left, level + 1)
           + weightedSum(p->Right, level + 1);
}

void printMatrix(const char *name, int M[N + 1][N + 1], int n)
{
    printf("\n%s\n", name);
    printf("      ");
    for (int j = 0; j <= n; j++)
        printf("%6d", j);
    printf("\n");

    for (int i = 0; i <= n; i++)
    {
        printf("%5d ", i);
        for (int j = 0; j <= n; j++)
            if (j < i)
                printf("%6s", "-");
            else
                printf("%6d", M[i][j]);
        printf("\n");
    }
}
void showDOPMatrices(int show)
{
    {
        buildMatrices(show);
        Vertex *root = createTree(0, show);

        printf("Ключи и веса (n=%d):\n", show);
        for (int i = 1; i <= show; i++)
        {
            printf("%d:%d  ", A[i].Data, A[i].Weight);
            if (i % 10 == 0)
                printf("\n");
        }
        printf("\n");
        printMatrix("AW - матрица весов", AW, show);
        printMatrix("AP - матрица взвешенных высот", AP, show);
        printMatrix("AR - матрица корней", AR, show);
        printf("\nПроверка n=%d: %.3f = %.3f\n", show,
               (double)AP[0][show] / AW[0][show],
               (double)weightedSum(root, 1) / AW[0][show]);

        if (show == 10)
            saveSVG("dop10.svg", root, show);
        freeTree(root);
    }

}

void printDOPComparison(void)
{
    int sizes[] = {100, 200, 300, 400, 500};
    int resultSize[5], resultSum[5], resultHeight[5];
    double resultAvg[5], resultCheck[5];

    for (int t = 0; t < 5; t++)
    {
        int n = sizes[t];
        buildMatrices(n);
        Vertex *root = createTree(0, n);
        int sum = weightedSum(root, 1);
        double avg = (double)sum / AW[0][n];

        if (n == 100)
        {
            int count = 0;
            printf("\nОбход дерева из 100 вершин слева направо:\n");
            inorder(root, &count);
            printf("\n");
            saveSVG("dop.svg", root, n);
        }

        resultSize[t] = size(root);
        resultSum[t] = checksum(root);
        resultHeight[t] = height(root);
        resultAvg[t] = avg;
        resultCheck[t] = (double)AP[0][n] / AW[0][n];

        if (sum != AP[0][n])
            printf("Ошибка: вычисленные высоты не совпадают!\n");

        freeTree(root);
    }

    printf("\nИтоговая таблица:\n");
    printf("%-6s %8s %15s %9s %20s %12s\n",
           "N", "Размер", "Контр. сумма", "Высота", "Средневзв. высота", "AP / AW");
    for (int t = 0; t < 5; t++)
        printf("%-6d %8d %15d %9d %20.3f %12.3f\n",
               sizes[t], resultSize[t], resultSum[t], resultHeight[t],
               resultAvg[t], resultCheck[t]);

    printf("\nSVG: dop.svg, dop10.svg (если был вывод матриц для n=10)\n");
    printf("Просмотр: labs/dop/preview.html\n");
}
