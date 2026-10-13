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

static void printRow(const char *name, struct Node *root)
{
    int n = size(root);
    double average = 0;

    if (n != 0)
        average = (double)sumHeight(root, 1) / n;

    printf("| %-4s | %6d | %13d | %6d | %14.2f |\n",
           name, n, checkSum(root), height(root), average);
}

void printComparison(const int A[], int n, struct Node *avl)
{
    int *sorted = malloc((size_t)n * sizeof(int));
    struct Node *isdp;

    if (sorted == NULL)
        exit(1);

    for (int i = 0; i < n; i++)
        sorted[i] = A[i];

    sortArray(sorted, n);
    isdp = ISDP(sorted, 0, n - 1);

    printf("\nСравнение ИСДП и АВЛ:\n");
    printf("+------+--------+---------------+--------+----------------+\n");
    printf("|      | Размер | Контр. сумма  | Высота | Средн. высота  |\n");
    printf("+------+--------+---------------+--------+----------------+\n");
    printRow("ИСДП", isdp);
    printRow("АВЛ", avl);
    printf("+------+--------+---------------+--------+----------------+\n");

    freeTree(isdp);
    free(sorted);
}
