#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sdp.h"

int size(struct Node *root);
int checkSum(struct Node *root);
int height(struct Node *root);
int sumHeight(struct Node *root, int level);

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

static void printRow(const char *name, struct Node *root)
{
    int n = size(root);
    printf("│ %-5s │ %6d │ %17d │ %6d │ %15.2f │\n",
           name, n, checkSum(root), height(root),
           n ? (double)sumHeight(root, 1) / n : 0);
}

static void printLink(const char *name)
{
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s: \033]8;;file://%s/%s\033\\file://%s/%s\033]8;;\033\\\n",
               name, cwd, name, cwd, name);
    else
        printf("%s\n", name);
}

void printExtras(const int A[], int n, struct Node *sdp1, struct Node *sdp2)
{
    int *sorted = malloc((size_t)n * sizeof(int));
    if (sorted == NULL)
        exit(1);
    memcpy(sorted, A, (size_t)n * sizeof(int));
    qsort(sorted, (size_t)n, sizeof(int), compareInts);
    struct Node *isdp = ISDP(sorted, 0, n - 1);

    printf("\nСравнение деревьев (n = %d):\n", n);
    printf("┌───────┬────────┬───────────────────┬────────┬─────────────────┐\n");
    printf("│ Дерево│ Размер │ Контрольная сумма │ Высота │ Средняя высота  │\n");
    printf("├───────┼────────┼───────────────────┼────────┼─────────────────┤\n");
    printRow("ИСДП", isdp);
    printRow("СДП1", sdp1);
    printRow("СДП2", sdp2);
    printf("└───────┴────────┴───────────────────┴────────┴─────────────────┘\n");

    if (saveTreeSvg("sdp-isdp.svg", isdp))
        printLink("sdp-isdp.svg");
    else
        perror("Не удалось сохранить sdp-isdp.svg");

    if (saveTreeSvg("sdp-sdp.svg", sdp1))
        printLink("sdp-sdp.svg");
    else
        perror("Не удалось сохранить sdp-sdp.svg");

    if (saveTreeSvg("sdp-sdp2.svg", sdp2))
        printLink("sdp-sdp2.svg");
    else
        perror("Не удалось сохранить sdp-sdp2.svg");

    freeTree(isdp);
    free(sorted);
}
