#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

static void sortArray(int A[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (A[j] > A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
}

static struct Node *ISDP(int A[], int left, int right)
{
    struct Node *p;
    int middle;

    if (left > right)
        return NULL;

    middle = (left + right) / 2;

    p = malloc(sizeof(struct Node));
    if (p == NULL)
        exit(1);

    p->Data = A[middle];
    p->Bal = 0;
    p->Left = ISDP(A, left, middle - 1);
    p->Right = ISDP(A, middle + 1, right);

    return p;
}

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

static void printRow(int N, int showN, const char *name, struct Node *root)
{
    char cell[64];
    int count = size(root);
    double average = 0;

    if (count != 0)
        average = (double)sumHeight(root, 1) / count;

    printf("│");

    if (showN)
        snprintf(cell, sizeof(cell), "%d", N);
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

void printComparison(const int A[], int maxN)
{
    int *sorted = malloc((size_t)maxN * sizeof(int));
    struct Node *avl = NULL;

    if (sorted == NULL)
        exit(1);

    printf("\nСравнение ИСДП и АВЛ:\n");
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

    for (int n = 100; n <= maxN; n += 100)
    {
        for (int i = n - 100; i < n; i++)
            addAVL(A[i], &avl);

        for (int i = 0; i < n; i++)
            sorted[i] = A[i];

        sortArray(sorted, n);
        struct Node *isdp = ISDP(sorted, 0, n - 1);

        printRow(n, 1, "ИСДП", isdp);
        printRow(n, 0, "АВЛ", avl);

        freeTree(isdp);

        if (n < maxN)
            printf("├─────┼───────┼────────┼───────────────────┼────────┼─────────────────┤\n");
    }

    printf("└─────┴───────┴────────┴───────────────────┴────────┴─────────────────┘\n");

    freeTree(avl);
    free(sorted);
}
