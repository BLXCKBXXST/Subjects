#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

#define TREE_N 100
#define DELETE_N 10

static void printTree(struct Node *root)
{
    if (root == NULL)
        printf("(пусто)");
    else
        inorder(root);
    printf("\n");
}

int main(void)
{
    if (TREE_N < 1 || TREE_N > 1000)
    {
        printf("Число вершин должно быть от 1 до 1000.\n");
        return 1;
    }
    int values[TREE_N];
    int deletedKeys[DELETE_N];
    struct Node *root = NULL;

    srand((unsigned)time(NULL));
    generateNumbers(values, TREE_N);
    for (int i = 0; i < TREE_N; i++)
        addAVL(values[i], &root);

    printf("Исходное АВЛ-дерево, обход слева направо:\n");
    printTree(root);
    if (!saveDeleteStep(root, 0))
        fprintf(stderr, "Не удалось сохранить исходный рисунок дерева.\n");
    showDeletePreview(deletedKeys, 0);

    int deletes = TREE_N < DELETE_N ? TREE_N : DELETE_N;
    int removed = 0;
    while (removed < deletes)
    {
        int key;
        printf("Ключ для удаления %d/%d: ", removed + 1, deletes);
        fflush(stdout);
        if (scanf("%d", &key) != 1)
            break;

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
        showDeletePreview(deletedKeys, removed);
    }

    freeTree(root);
    return 0;
}
