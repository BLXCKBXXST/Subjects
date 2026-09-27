#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdp.h"

int size(struct Node *root);
int checkSum(struct Node *root);
int height(struct Node *root);
int sumHeight(struct Node *root, int level);
void printTreeVisual(FILE *out, struct Node *root);

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
    struct Node *root = malloc(sizeof(struct Node));
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
    fprintf(stdout, "│ %s │ %6d │ %17d │ %6d │ %15.2f │\n",
            name, n, checkSum(root), height(root),
            n ? (double)sumHeight(root, 1) / n : 0);
}

static void printForest(FILE *out, struct Node *isdp,
                        struct Node *sdp1, struct Node *sdp2)
{
    fprintf(out, "\nИСДП:\n");
    printTreeVisual(out, isdp);
    fprintf(out, "\nСДП1 (рекурсивно):\n");
    printTreeVisual(out, sdp1);
    fprintf(out, "\nСДП2 (двойная косвенность):\n");
    printTreeVisual(out, sdp2);
}

void printExtras(const int A[], int n)
{
    int *sorted = malloc((size_t)n * sizeof(int));
    if (sorted == NULL)
        exit(1);
    memcpy(sorted, A, (size_t)n * sizeof(int));
    qsort(sorted, (size_t)n, sizeof(int), compareInts);

    struct Node *isdp = ISDP(sorted, 0, n - 1);
    struct Node *sdp1 = NULL;
    struct Node *sdp2 = NULL;
    for (int i = 0; i < n; i++)
    {
        insertRecursive(&sdp1, A[i]);
        insertDouble(&sdp2, A[i]);
    }

    printf("\nСравнение деревьев (n = %d):\n", n);
    printf("┌───────┬────────┬───────────────────┬────────┬─────────────────┐\n");
    printf("│ Дерево│ Размер │ Контрольная сумма │ Высота │ Средняя высота  │\n");
    printf("├───────┼────────┼───────────────────┼────────┼─────────────────┤\n");
    printRow("ИСДП ", isdp);
    printRow("СДП1 ", sdp1);
    printRow("СДП2 ", sdp2);
    printf("└───────┴────────┴───────────────────┴────────┴─────────────────┘\n");

    printf("\nОбход СДП1:\n");
    inorder(sdp1);
    printf("\nОбход СДП2:\n");
    inorder(sdp2);
    printf("\n");

    printForest(stdout, isdp, sdp1, sdp2);

    FILE *file = fopen("sdp-trees.txt", "w");
    if (file != NULL)
    {
        printForest(file, isdp, sdp1, sdp2);
        if (fclose(file) == 0)
            printf("\nДеревья сохранены в sdp-trees.txt\n");
        else
            perror("Ошибка сохранения sdp-trees.txt");
    }
    else
        perror("Не удалось создать sdp-trees.txt");

    freeTree(isdp);
    freeTree(sdp1);
    freeTree(sdp2);
    free(sorted);
}
