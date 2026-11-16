#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "3.4-sdp-delete.h"
#include "../lab-viewer.h"

#define MAX_N 1000

int main(int argc, char **argv)
{
    (void)argc;
    if (!initLabPaths(argv[0])) return 1;
    int deletedKeys[MAX_N] = {0};
    int ok = 1;
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
        insertDouble(&root, A[i]);

    printf("Исходное СДП (%d вершин), обход слева направо:\n", n);
    inorder(root);
    printf("\n");
    if (!saveDeleteStep(root, 0) || !showDeletePreview(deletedKeys, 0))
    {
        freeTree(root);
        return 1;
    }
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

        if (!deleteNodeMove(&root, key))
        {
            printf("Ключ %d не найден. Выберите другой.\n", key);
            continue;
        }

        deletedKeys[i++] = key;
        printf("После удаления %d, обход слева направо:\n", key);
        inorder(root);
        printf("\n");
        if (!saveDeleteStep(root, i) || !showDeletePreview(deletedKeys, i))
        {
            ok = 0;
            break;
        }
    }

    freeTree(root);
    return ok ? 0 : 1;
}
