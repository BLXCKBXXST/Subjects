#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdp.h"

#define N 100
#define DELETE_COUNT 10

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
    int A[N];
    struct Node *root = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(A, N);
    for (int i = 0; i < N; i++)
        insertNode(&root, A[i]);

    printf("Исходное СДП (%d вершин), обход слева направо:\n", N);
    inorder(root);
    printf("\nВыберите 10 ключей из списка выше.\n");

    for (int i = 0; i < DELETE_COUNT;)
    {
        int key;
        printf("Ключ для удаления %d/%d: ", i + 1, DELETE_COUNT);
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
    }

    freeTree(root);
    return 0;
}
