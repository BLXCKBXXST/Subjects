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

static void printRow(int n, const char *name, struct Node *root)
{
    int count = size(root);
    double average = 0;

    if (count != 0)
        average = (double)sumHeight(root, 1) / count;

    printf("| %3d | %-4s | %6d | %13d | %6d | %14.2f |\n",
           n, name, count, checkSum(root), height(root), average);
}

void printComparison(const int A[], int maxN)
{
    int *sorted = malloc((size_t)maxN * sizeof(int));
    struct Node *avl = NULL;

    if (sorted == NULL)
        exit(1);

    printf("\nСравнение ИСДП и АВЛ:\n");
    printf("+-----+------+--------+---------------+--------+----------------+\n");
    printf("|  N  |      | Размер | Контр. сумма  | Высота | Средн. высота  |\n");
    printf("+-----+------+--------+---------------+--------+----------------+\n");

    for (int n = 100; n <= maxN; n += 100)
    {
        for (int i = n - 100; i < n; i++)
            addAVL(A[i], &avl);

        for (int i = 0; i < n; i++)
            sorted[i] = A[i];

        sortArray(sorted, n);
        struct Node *isdp = ISDP(sorted, 0, n - 1);

        printRow(n, "ИСДП", isdp);
        printRow(n, "АВЛ", avl);

        freeTree(isdp);

        if (n < maxN)
            printf("+-----+------+--------+---------------+--------+----------------+\n");
    }

    printf("+-----+------+--------+---------------+--------+----------------+\n");

    freeTree(avl);
    free(sorted);
}
