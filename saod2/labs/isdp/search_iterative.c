#include <stdio.h>
#include "search.h"

struct Node
{
    int Data;
    struct Node *Left;
    struct Node *Right;
};

static struct Node *searchIterative(struct Node *p, int key)
{
    while (p != NULL)
    {
        if (key == p->Data)
            return p;

        if (key < p->Data)
            p = p->Left;
        else
            p = p->Right;
    }

    return NULL;
}

void searchMultiple(struct Node *root)
{
    int count;

    printf("\nНерекурсивный поиск\n");
    printf("Сколько элементов найти: ");
    if (scanf("%d", &count) != 1 || count < 0) {
        fprintf(stderr, "Некорректное количество ключей\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int key;

        printf("Введите ключ %d: ", i + 1);
        if (scanf("%d", &key) != 1) {
            fprintf(stderr, "Не удалось прочитать ключ\n");
            return;
        }

        struct Node *result = searchIterative(root, key);

        if (result != NULL)
            printf("Элемент %d найден\n", key);
        else
            printf("Элемент %d не найден\n", key);
    }
}
