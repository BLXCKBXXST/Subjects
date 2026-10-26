#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h"

#define TREE_N 100
#define DELETE_N 10
#define MANUAL_N 12

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
    int values[TREE_N];
    int manual = argc > 1 && strcmp(argv[1], "--manual") == 0;
    int count = manual ? MANUAL_N : TREE_N;
    struct Node *root = NULL;

    if (manual)
    {
        printf("Введите %d разных кодов символов в порядке ручного задания:\n", MANUAL_N);
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

    int deletes = manual ? MANUAL_N : DELETE_N;
    for (int i = 0; i < deletes;)
    {
        int key;
        if (manual)
            key = values[i];
        else
        {
            printf("Ключ для удаления %d/%d: ", i + 1, deletes);
            fflush(stdout);
            if (scanf("%d", &key) != 1)
                break;
        }

        if (!deleteAVL(key, &root))
        {
            printf("Ключ %d не найден.\n", key);
            continue;
        }

        i++;
        printf("После удаления %d, обход слева направо:\n", key);
        printTree(root);
    }

    freeTree(root);
    return 0;
}
