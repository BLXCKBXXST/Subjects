#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lab-viewer.h"
#include "3.3-sdp.h"

static int compareInts(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static struct Node *ISDP(const int A[], int left, int right)
{
    if (left > right)
        return NULL;
    int mid = (left + right) / 2;
    struct Node *root = malloc(sizeof(*root));
    if (root == NULL)
        exit(1);
    root->Data = A[mid];
    root->Left = ISDP(A, left, mid - 1);
    root->Right = ISDP(A, mid + 1, right);
    return root;
}

/* printf считает байты UTF-8, а не ширину русских букв в терминале. */
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

int printExtras(const int A[], int n, struct Node *sdp1, struct Node *sdp2)
{
    int *sorted = malloc((size_t)n * sizeof(int));
    if (sorted == NULL)
        exit(1);
    memcpy(sorted, A, (size_t)n * sizeof(int));
    qsort(sorted, (size_t)n, sizeof(int), compareInts);
    struct Node *isdp = ISDP(sorted, 0, n - 1);

    int ok = saveTreeSvg("3.3-isdp.svg", isdp);
    if (!ok) perror("3.3-isdp.svg");
    if (!saveTreeSvg("3.3-sdp-recursive.svg", sdp1))
    {
        perror("3.3-sdp-recursive.svg");
        ok = 0;
    }
    if (!saveTreeSvg("3.3-sdp-double.svg", sdp2))
    {
        perror("3.3-sdp-double.svg");
        ok = 0;
    }
    if (ok) openLabPage("labs/3.3-sdp/3.3-view.html");

    freeTree(isdp);
    free(sorted);
    return ok;
}

static void summaryRow(int N, int showN, const char *name, struct Node *root)
{
    char cell[64];
    int n = size(root);

    printf("│");

    if (showN)
        snprintf(cell, sizeof(cell), "%d", N);
    else
        cell[0] = '\0';

    printCell(cell, 5);
    printCell(name, 7);

    snprintf(cell, sizeof(cell), "%d", checkSum(root));
    printCell(cell, 19);

    snprintf(cell, sizeof(cell), "%d", height(root));
    printCell(cell, 8);

    snprintf(cell, sizeof(cell), "%.2f",
             n ? (double)sumHeight(root, 1) / n : 0);
    printCell(cell, 17);

    printf("\n");
}

void printSummary(const int A[], int maxN)
{
    int *sorted = malloc((size_t)maxN * sizeof(int));
    if (sorted == NULL)
        exit(1);
    struct Node *sdp1 = NULL;
    struct Node *sdp2 = NULL;

    printf("\nСводная таблица по всем N:\n");
    printf("┌─────┬───────┬───────────────────┬────────┬─────────────────┐\n");
    printf("│");
    printCell("N", 5);
    printCell("Дерево", 7);
    printCell("Контрольная сумма", 19);
    printCell("Высота", 8);
    printCell("Средняя высота", 17);
    printf("\n");
    printf("├─────┼───────┼───────────────────┼────────┼─────────────────┤\n");

    for (int n = 100; n <= maxN; n += 100)
    {
        for (int i = n - 100; i < n; i++)
        {
            insertRecursive(&sdp1, A[i]);
            insertDouble(&sdp2, A[i]);
        }

        memcpy(sorted, A, (size_t)n * sizeof(int));
        qsort(sorted, (size_t)n, sizeof(int), compareInts);
        struct Node *isdp = ISDP(sorted, 0, n - 1);

        summaryRow(n, 0, "ИСДП", isdp);
        summaryRow(n, 1, "СДП1", sdp1);
        summaryRow(n, 0, "СДП2", sdp2);
        freeTree(isdp);

        if (n < maxN)
            printf("├─────┼───────┼───────────────────┼────────┼─────────────────┤\n");
    }
    printf("└─────┴───────┴───────────────────┴────────┴─────────────────┘\n");
    freeTree(sdp1);
    freeTree(sdp2);
    free(sorted);
}
