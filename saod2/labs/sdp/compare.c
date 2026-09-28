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

static void printRow(const char *name, struct Node *root)
{
    char number[64];
    int n = size(root);

    printf("│");
    printCell(name, 7);
    snprintf(number, sizeof(number), "%d", n);
    printCell(number, 8);
    snprintf(number, sizeof(number), "%d", checkSum(root));
    printCell(number, 19);
    snprintf(number, sizeof(number), "%d", height(root));
    printCell(number, 8);
    snprintf(number, sizeof(number), "%.2f",
             n ? (double)sumHeight(root, 1) / n : 0);
    printCell(number, 17);
    printf("\n");
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

static void saveAndPreview(const char *filename, struct Node *root, int hasChafa)
{
    if (!saveTreeSvg(filename, root))
    {
        perror(filename);
        return;
    }

    printLink(filename);
    printf("\n");
    fflush(stdout);

    if (hasChafa)
    {
        char command[160];
        snprintf(command, sizeof(command),
                 "chafa --format symbols --size 78x18 %s", filename);
        if (system(command) != 0)
            printf("Не удалось показать превью %s\n", filename);
    }
    printf("\n");
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
    printf("│");
    printCell("Дерево", 7);
    printCell("Размер", 8);
    printCell("Контрольная сумма", 19);
    printCell("Высота", 8);
    printCell("Средняя высота", 17);
    printf("\n");
    printf("├───────┼────────┼───────────────────┼────────┼─────────────────┤\n");
    printRow("ИСДП", isdp);
    printRow("СДП1", sdp1);
    printRow("СДП2", sdp2);
    printf("└───────┴────────┴───────────────────┴────────┴─────────────────┘\n");

    static int hasChafa = -1;
    if (hasChafa == -1)
        hasChafa = system("command -v chafa >/dev/null 2>&1") == 0;

    char file1[64], file2[64], file3[64];
    if (n == 100)
    {
        snprintf(file1, sizeof(file1), "sdp-isdp.svg");
        snprintf(file2, sizeof(file2), "sdp-sdp.svg");
        snprintf(file3, sizeof(file3), "sdp-sdp2.svg");
    }
    else
    {
        snprintf(file1, sizeof(file1), "sdp-isdp-%d.svg", n);
        snprintf(file2, sizeof(file2), "sdp-sdp-%d.svg", n);
        snprintf(file3, sizeof(file3), "sdp-sdp2-%d.svg", n);
    }

    saveAndPreview(file1, isdp, hasChafa);
    saveAndPreview(file2, sdp1, hasChafa);
    saveAndPreview(file3, sdp2, hasChafa);

    freeTree(isdp);
    free(sorted);
}
