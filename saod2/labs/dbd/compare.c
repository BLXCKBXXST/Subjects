#include <stdio.h>
#include "dbd.h"

static int textWidth(const char *s)
{
    int length = 0;

    for (const unsigned char *p = (const unsigned char *)s; *p; p++)
        if ((*p & 0xc0) != 0x80)
            length++;

    return length;
}

static void printCell(const char *value, int width)
{
    int spaces = width - textWidth(value);
    if (spaces < 0)
        spaces = 0;

    int left = spaces / 2;
    int right = spaces - left;
    printf("%*s%s%*s│", left, "", value, right, "");
}

static void printRow(int n, int showN, const char *name, struct Node *root)
{
    char cell[64];
    int count = size(root);
    double average = count ? (double)sumHeight(root, 1) / count : 0;

    printf("│");
    if (showN)
        snprintf(cell, sizeof(cell), "%d", n);
    else
        cell[0] = '\0';
    printCell(cell, 5);
    printCell(name, 7);

    snprintf(cell, sizeof(cell), "%d", count);
    printCell(cell, 8);
    snprintf(cell, sizeof(cell), "%d", checkSum(root));
    printCell(cell, 19);
    snprintf(cell, sizeof(cell), "%d", height(root));
    printCell(cell, 8);
    snprintf(cell, sizeof(cell), "%.2f", average);
    printCell(cell, 17);
    printf("\n");
}

void printDBDComparison(struct Node *dbd, struct Node *avl, int n)
{
    printf("Сравнение АВЛ и ДБД:\n");
    printf("┌─────┬───────┬────────┬───────────────────┬────────┬─────────────────┐\n");
    printf("│");
    printCell("N", 5);
    printCell("Дерево", 7);
    printCell("Размер", 8);
    printCell("Контрольная сумма", 19);
    printCell("Высота", 8);
    printCell("Средняя высота", 17);
    printf("\n");
    printf("├─────┼───────┼────────┼───────────────────┼────────┼─────────────────┤\n");
    printRow(n, 1, "АВЛ", avl);
    printRow(n, 0, "ДБД", dbd);
    printf("└─────┴───────┴────────┴───────────────────┴────────┴─────────────────┘\n");
}
