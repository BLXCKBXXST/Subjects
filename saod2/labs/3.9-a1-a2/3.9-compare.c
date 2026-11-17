#include <stdio.h>
#include "3.9-a1-a2.h"
#include "../lab-table.h"

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
    tableCell(name, 6);
    tableInt(size(p), 6);
    tableInt(checksum(p), 13);
    tableInt(height(p), 6);
    tableDouble((double)weightedSum(p, 1) / total, 18);
    printf("│\n");
}

int printComparison(void)
{
    int ok = 1;
    int counts[] = {100, 200, 300, 400, 500};

    for (int t = 0; t < 5; t++)
    {
        int n = counts[t];
        buildMatrices(n);

        Vertex *dop = NULL;
        CreateTree(0, n, &dop);
        WeightedItem V1[N + 1], V2[N + 1];
        for (int i = 1; i <= n; i++)
        {
            V1[i] = (WeightedItem){A[i].Data, A[i].Weight, i};
            V2[i] = V1[i];
        }
        Vertex *first = NULL, *second = NULL;
        A1(V1, n, &first);
        A2(V2, 1, n, &second);

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
            const char *files[] = {"3.9-dop.svg", "3.9-a1.svg", "3.9-a2.svg"};
            Vertex *trees[] = {dop, first, second};
            for (int i = 0; i < 3; i++)
                if (!saveSVG(files[i], trees[i], n))
                {
                    fprintf(stderr, "Не удалось сохранить %s\n", files[i]);
                    ok = 0;
                }
        }

        printf("\nN = %d\n", n);
        const int widths[] = {6, 6, 13, 6, 18};
        const char *headers[] = {"Дерево", "Размер", "Контр. сумма", "Высота", "Средневзв. высота"};
        tableBorder(widths, 5, "┌", "┬", "┐");
        for (int i = 0; i < 5; i++) tableCell(headers[i], widths[i]);
        printf("│\n");
        tableBorder(widths, 5, "├", "┼", "┤");
        printRow("ДОП", dop, AW[0][n]);
        tableBorder(widths, 5, "├", "┼", "┤");
        printRow("А1", first, AW[0][n]);
        tableBorder(widths, 5, "├", "┼", "┤");
        printRow("А2", second, AW[0][n]);
        tableBorder(widths, 5, "└", "┴", "┘");
        printf("Проверка ДОП AP/AW: %.3f\n",
               (double)AP[0][n] / AW[0][n]);

        freeTree(dop);
        freeTree(first);
        freeTree(second);
    }

    printf("\nSVG: 3.9-dop.svg, 3.9-a1.svg, 3.9-a2.svg\n");
    return ok;
}
