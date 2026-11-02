#include <stdio.h>
#include "dbd.h"

static void printRow(const char *name, struct Node *root)
{
    int count = size(root);
    double average = count ? (double)sumHeight(root, 1) / count : 0;

    printf("%-6s | %6d | %16d | %6d | %14.2f\n",
           name, count, checkSum(root), height(root), average);
}

void printComparison(struct Node *dbd, struct Node *avl, int n)
{
    printf("Сравнение АВЛ и ДБД (n = %d):\n", n);
    printf("Дерево | Размер | Контрольная сумма | Высота | Средняя высота\n");
    printRow("АВЛ", avl);
    printRow("ДБД", dbd);
}
