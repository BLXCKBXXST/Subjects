#include "sdp.h"

struct Node *searchIterative(struct Node *p, int key)
{
    while (p != NULL)
    {
        if (p->Data == key)
            return p;

        if (key < p->Data)
            p = p->Left;
        else
            p = p->Right;
    }

    return NULL;
}
