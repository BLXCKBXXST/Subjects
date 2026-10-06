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

int deleteNodeMove(struct Node **root, int key)
{
    struct Node **p = root;
    struct Node *q;
    struct Node *r;
    struct Node *s;

    while (*p != NULL && (*p)->Data != key)
    {
        if (key < (*p)->Data)
            p = &(*p)->Left;
        else
            p = &(*p)->Right;
    }

    if (*p == NULL)
        return 0;

    q = *p;

    if (q->Left == NULL)
    {
        *p = q->Right;
    }
    else if (q->Right == NULL)
    {
        *p = q->Left;
    }
    else
    {
        r = q->Left;
        s = q;

        if (r->Right == NULL)
        {
            r->Right = q->Right;
            *p = r;
        }
        else
        {
            while (r->Right != NULL)
            {
                s = r;
                r = r->Right;
            }

            s->Right = r->Left;
            r->Left = q->Left;
            r->Right = q->Right;
            *p = r;
        }
    }

    free(q);
    return 1;
}
