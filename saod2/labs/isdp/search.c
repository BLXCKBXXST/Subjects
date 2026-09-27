#include <stdio.h>
#include "search.h"

struct Node
{
    int Data;
    struct Node *Left;
    struct Node *Right;
};

struct Node *searchRecursive(struct Node *root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->Data == key)
        return root;

    if (key < root->Data)
        return searchRecursive(root->Left, key);
    else
        return searchRecursive(root->Right, key);
}

void searchMultiple(struct Node *root)
{
    int count;

    printf("\nПоиск по ключам\n");
    printf("Количество ключей: ");
    if (scanf("%d", &count) != 1 || count < 0) {
        fprintf(stderr, "Некорректное количество ключей\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int key;

        printf("Ключ %d: ", i + 1);
        if (scanf("%d", &key) != 1) {
            fprintf(stderr, "Не удалось прочитать ключ\n");
            return;
        }

        struct Node *found = searchRecursive(root, key);

        if (found != NULL)
            printf("Ключ %d найден\n", key);
        else
            printf("Ключ %d не найден\n", key);
    }
}
