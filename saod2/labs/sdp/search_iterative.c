#include <stdio.h>
#include "sdp.h"

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
    printf("Количество ключей: ");

    if (scanf("%d", &count) != 1 || count <= 0)
        return;

    for (int i = 0; i < count; i++)
    {
        int key;

        printf("Ключ %d: ", i + 1);

        if (scanf("%d", &key) != 1)
            return;

        struct Node *found = searchIterative(root, key);

        if (found != NULL)
            printf("Ключ %d найден\n", key);
        else
            printf("Ключ %d не найден\n", key);
    }
}
