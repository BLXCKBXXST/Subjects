#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"

#define MAX_N 1000
#define SVG_FILE "sdp-delete.svg"

static void insertNode(struct Node **root, int value)
{
    while (*root != NULL)
    {
        if (value < (*root)->Data)
            root = &(*root)->Left;
        else
            root = &(*root)->Right;
    }

    *root = malloc(sizeof(**root));
    if (*root == NULL)
        exit(1);
    (*root)->Data = value;
    (*root)->Left = NULL;
    (*root)->Right = NULL;
}

static void previewTree(struct Node *root)
{
    if (root == NULL)
    {
        remove(SVG_FILE);
        printf("Дерево пусто.\n");
        return;
    }

    if (!saveTreeSvg(SVG_FILE, root))
    {
        perror(SVG_FILE);
        return;
    }

    printf("Миниатюра дерева (полный рисунок: %s):\n", SVG_FILE);
    fflush(stdout);
    if (system("command -v chafa >/dev/null 2>&1") == 0)
    {
        if (system("chafa --format symbols --colors none --invert --size 78x24 " SVG_FILE) != 0)
            printf("Не удалось показать миниатюру.\n");
    }
    else
        printf("Для миниатюры нужна программа chafa.\n");
}

int main(void)
{
    int A[MAX_N];
    int n, deleteCount;
    struct Node *root = NULL;

    printf("Количество вершин (1..%d): ", MAX_N);
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N)
    {
        printf("Неверное количество вершин.\n");
        return 1;
    }

    printf("Сколько вершин удалить (1..%d): ", n);
    fflush(stdout);
    if (scanf("%d", &deleteCount) != 1 || deleteCount < 1 || deleteCount > n)
    {
        printf("Неверное количество удалений.\n");
        return 1;
    }

    srand((unsigned)time(NULL));
    generateNumbers(A, n);
    for (int i = 0; i < n; i++)
        insertNode(&root, A[i]);

    printf("Исходное СДП (%d вершин), обход слева направо:\n", n);
    inorder(root);
    printf("\n");
    previewTree(root);
    printf("Выберите %d ключей из списка выше.\n", deleteCount);

    for (int i = 0; i < deleteCount;)
    {
        int key;
        printf("Ключ для удаления %d/%d: ", i + 1, deleteCount);
        fflush(stdout);
        if (scanf("%d", &key) != 1)
        {
            printf("\nВвод завершён.\n");
            break;
        }

        if (!deleteNode(&root, key))
        {
            printf("Ключ %d не найден. Выберите другой.\n", key);
            continue;
        }

        i++;
        printf("После удаления %d, обход слева направо:\n", key);
        inorder(root);
        printf("\n");
        previewTree(root);
    }

    freeTree(root);
    return 0;
}
