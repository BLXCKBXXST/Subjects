#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h"

#define DELETE_N 10

static void printTree(struct Node *root)
{
    if (root == NULL)
        printf("(пусто)");
    else
        inorder(root);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int manual = argc > 1 && strcmp(argv[1], "--manual") == 0;
    int vertexCount = manual ? 12 : 100; // Число вершин: 12 вручную, 100 случайно.
    if (vertexCount < 1 || vertexCount > 1000)
    {
        printf("Число вершин должно быть от 1 до 1000.\n");
        return 1;
    }
    int values[vertexCount];
    int deletedKeys[vertexCount];
    int count = vertexCount;
    struct Node *root = NULL;

    if (manual)
    {
        printf("Введите %d разных кодов символов в порядке ручного задания:\n", count);
        for (int i = 0; i < count; i++)
        {
            printf("Код %d: ", i + 1);
            fflush(stdout);
            if (scanf("%d", &values[i]) != 1)
            {
                freeTree(root);
                return 1;
            }
            if (searchNode(root, values[i]) != NULL)
            {
                printf("Код уже введён.\n");
                i--;
                continue;
            }
            addAVL(values[i], &root);
        }
    }
    else
    {
        srand((unsigned)time(NULL));
        generateNumbers(values, count);
        for (int i = 0; i < count; i++)
            addAVL(values[i], &root);
    }

    printf("Исходное АВЛ-дерево, обход слева направо:\n");
    printTree(root);
    if (!saveDeleteStep(root, 0))
        fprintf(stderr, "Не удалось сохранить исходный рисунок дерева.\n");

    int deletes = manual ? count : (count < DELETE_N ? count : DELETE_N);
    int removed = 0;
    while (removed < deletes)
    {
        int key;
        if (manual)
            key = values[removed];
        else
        {
            printf("Ключ для удаления %d/%d: ", removed + 1, deletes);
            fflush(stdout);
            if (scanf("%d", &key) != 1)
                break;
        }

        if (!deleteAVL(key, &root))
        {
            printf("Ключ %d не найден.\n", key);
            continue;
        }

        deletedKeys[removed] = key;
        removed++;
        printf("После удаления %d, обход слева направо:\n", key);
        printTree(root);
        if (!saveDeleteStep(root, removed))
            fprintf(stderr, "Не удалось сохранить рисунок после удаления %d.\n", key);
    }

    showDeletePreview(deletedKeys, removed);
    freeTree(root);
    return 0;
}
