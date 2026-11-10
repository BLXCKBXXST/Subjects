#include <stdio.h>
#include "a1a2.h"

int size(Vertex *p)
{
    if (p == NULL) return 0;
    return 1 + size(p->Left) + size(p->Right);
}

int checksum(Vertex *p)
{
    if (p == NULL) return 0;
    return p->Data + checksum(p->Left) + checksum(p->Right);
}

int height(Vertex *p)
{
    if (p == NULL) return 0;
    int l = height(p->Left);
    int r = height(p->Right);
    return 1 + (l > r ? l : r);
}

int weightedSum(Vertex *p, int level)
{
    if (p == NULL) return 0;
    return p->Weight * level + weightedSum(p->Left, level + 1)
           + weightedSum(p->Right, level + 1);
}

static void printRow(const char *name, Vertex *p, int total)
{
    printf("%-6s %8d %15d %9d %20.3f\n", name,
           size(p), checksum(p), height(p),
           (double)weightedSum(p, 1) / total);
}

void printComparison(void)
{
    int counts[] = {100, 200, 300, 400, 500};

    for (int t = 0; t < 5; t++)
    {
        int n = counts[t];
        buildMatrices(n);

        Vertex *dop = createTree(0, n);
        Vertex *first = a1(n);
        Vertex *second = a2(1, n);

        if (n == 100)
        {
            int count = 0;
            printf("\nОбход ДОП (100 вершин):\n");
            inorder(dop, &count);
            count = 0;
            printf("\n\nОбход А1 (100 вершин):\n");
            inorder(first, &count);
            count = 0;
            printf("\n\nОбход А2 (100 вершин):\n");
            inorder(second, &count);
            printf("\n");
            saveSVG("a1a2_dop.svg", dop, n);
            saveSVG("a1a2_a1.svg", first, n);
            saveSVG("a1a2_a2.svg", second, n);
        }

        printf("\nN = %d\n", n);
        printf("%-6s %8s %15s %9s %20s\n",
               "Дерево", "Размер", "Контр. сумма", "Высота", "Средневзв. высота");
        printRow("ДОП", dop, AW[0][n]);
        printRow("А1", first, AW[0][n]);
        printRow("А2", second, AW[0][n]);
        printf("Проверка ДОП AP/AW: %.3f\n",
               (double)AP[0][n] / AW[0][n]);

        freeTree(dop);
        freeTree(first);
        freeTree(second);
    }

    printf("\nSVG: a1a2_dop.svg, a1a2_a1.svg, a1a2_a2.svg\n");
}
