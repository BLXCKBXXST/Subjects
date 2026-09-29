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
    int count;

    printf("\nПоиск по ключам\n");
    printf("Количество ключей (0 - выход): ");

    if (scanf("%d", &count) != 1 || count <= 0)
        return;

    for (int i = 0; i < count; i++)
    {
        int key;
        struct Node *recursiveResult;
        struct Node *iterativeResult;

        printf("Ключ %d: ", i + 1);

        if (scanf("%d", &key) != 1)
            return;

        recursiveResult = searchRecursive(sdp1, key);
        iterativeResult = searchIterative(sdp2, key);

        printf("  рекурсивный поиск: %s\n",
               recursiveResult != NULL ? "найден" : "не найден");
        printf("  нерекурсивный поиск: %s\n",
               iterativeResult != NULL ? "найден" : "не найден");
    }
}
