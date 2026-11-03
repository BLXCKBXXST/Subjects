#include <stdlib.h>
#include "dbd.h"

int VR, HR;

void B2INSERT(int D, struct Node **p)
{
    struct Node *q;

    if (*p == NULL)
    {
        *p = malloc(sizeof(struct Node));
        if (*p == NULL)
            exit(1);

        (*p)->Data = D;
        (*p)->Left = (*p)->Right = NULL;
        (*p)->Bal = 0;
        VR = 1;
    }
    else if ((*p)->Data > D)
    {
        B2INSERT(D, &(*p)->Left);

        if (VR == 1)
        {
            if ((*p)->Bal == 0)
            {
                q = (*p)->Left;
                (*p)->Left = q->Right;
                q->Right = *p;
                *p = q;
                q->Bal = 1;
                VR = 0;
                HR = 1;
            }
            else
            {
                (*p)->Bal = 0;
                VR = 1;
                HR = 0;
            }
        }
        else
            HR = 0;
    }
    else if ((*p)->Data < D)
    {
        B2INSERT(D, &(*p)->Right);

        if (VR == 1)
        {
            (*p)->Bal = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR == 1)
        {
            if ((*p)->Bal == 1)
            {
                q = (*p)->Right;
                (*p)->Bal = 0;
                q->Bal = 0;
                (*p)->Right = q->Left;
                q->Left = *p;
                *p = q;
                VR = 1;
                HR = 0;
            }
            else
                HR = 0;
        }
    }
}

int pageLevels(struct Node *p)
{
    int h = 0;

    while (p != NULL)
    {
        h++;
        p = p->Left;
    }

    return h;
}
