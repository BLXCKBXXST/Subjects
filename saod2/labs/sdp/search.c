#include <stdio.h>
#include "sdp.h"

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

void searchMultiple(struct Node *sdp1, struct Node *sdp2)
{
    int variant;

    while (1)
    {
        printf("\nПоиск по ключам\n");
        printf("1 - рекурсивный поиск\n");
        printf("2 - нерекурсивный поиск\n");
        printf("0 - выход\n");
        printf("> ");

        if (scanf("%d", &variant) != 1)
            return;

        if (variant == 0)
            return;

        if (variant != 1 && variant != 2)
        {
            printf("Нет такого варианта.\n");
            continue;
        }

        int count;

        printf("Количество ключей (0 - назад): ");

        if (scanf("%d", &count) != 1)
            return;

        if (count == 0)
            continue;

        if (count < 0)
        {
            printf("Количество ключей должно быть положительным.\n");
            continue;
        }

        for (int i = 0; i < count; i++)
        {
            int key;
            struct Node *result;

            printf("Ключ %d: ", i + 1);

            if (scanf("%d", &key) != 1)
                return;

            if (variant == 1)
                result = searchRecursive(sdp1, key);
            else
                result = searchIterative(sdp2, key);

            if (result != NULL)
                printf("Ключ %d найден\n", key);
            else
                printf("Ключ %d не найден\n", key);
        }
    }
}
