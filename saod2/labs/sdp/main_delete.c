#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"
#include "delete_input.h"
#include "delete_preview.h"

#define MAX_N 1000

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

int main(void)
{
    int A[MAX_N];
    int n, deleteCount;
    struct Node *root = NULL;

    n = readCount("Количество вершин", MAX_N);
    if (n == 0)
    {
        printf("Неверное количество вершин.\n");
        return 1;
    }

    deleteCount = readCount("Сколько вершин удалить", n);
    if (deleteCount == 0)
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
    showTreeImage(root);
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
        showTreeImage(root);
    }

    freeTree(root);
    return 0;
}
