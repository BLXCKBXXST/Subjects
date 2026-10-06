#include <stdlib.h>
#include "sdp.h"

int deleteNode(struct Node **root, int key)
{
    while (*root != NULL && (*root)->Data != key)
    {
        if (key < (*root)->Data)
            root = &(*root)->Left;
        else
            root = &(*root)->Right;
    }

    if (*root == NULL)
        return 0;

    struct Node *node = *root;
    if (node->Left != NULL && node->Right != NULL)
    {
        /* На место удаляемой вершины ставим максимум левого поддерева. */
        struct Node **maxLeft = &node->Left;
        while ((*maxLeft)->Right != NULL)
            maxLeft = &(*maxLeft)->Right;

        node->Data = (*maxLeft)->Data;
        struct Node *old = *maxLeft;
        *maxLeft = old->Left;
        free(old);
    }
    else
    {
        *root = node->Left != NULL ? node->Left : node->Right;
        free(node);
    }

    return 1;
}
