#include <stdlib.h>
#include "avl.h"

static int Rost = 0;

static void LL(struct Node **p)
{
    struct Node *q = (*p)->Left;

    (*p)->Bal = 0;
    q->Bal = 0;
    (*p)->Left = q->Right;
    q->Right = *p;
    *p = q;
}

static void RR(struct Node **p)
{
    struct Node *q = (*p)->Right;

    (*p)->Bal = 0;
    q->Bal = 0;
    (*p)->Right = q->Left;
    q->Left = *p;
    *p = q;
}

static void LR(struct Node **p)
{
    struct Node *q = (*p)->Left;
    struct Node *r = q->Right;

    if (r->Bal < 0)
        (*p)->Bal = 1;
    else
        (*p)->Bal = 0;

    if (r->Bal > 0)
        q->Bal = -1;
    else
        q->Bal = 0;

    r->Bal = 0;
    q->Right = r->Left;
    (*p)->Left = r->Right;
    r->Left = q;
    r->Right = *p;
    *p = r;
}

static void RL(struct Node **p)
{
    struct Node *q = (*p)->Right;
    struct Node *r = q->Left;

    if (r->Bal > 0)
        (*p)->Bal = -1;
    else
        (*p)->Bal = 0;

    if (r->Bal < 0)
        q->Bal = 1;
    else
        q->Bal = 0;

    r->Bal = 0;
    q->Left = r->Right;
    (*p)->Right = r->Left;
    r->Right = q;
    r->Left = *p;
    *p = r;
}

void addAVL(int D, struct Node **p)
{
    if (*p == NULL)
    {
        *p = malloc(sizeof(struct Node));
        if (*p == NULL)
            exit(1);

        (*p)->Data = D;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
        (*p)->Bal = 0;
        Rost = 1;
    }
    else if ((*p)->Data > D)
    {
        addAVL(D, &(*p)->Left);

        if (Rost)
        {
            if ((*p)->Bal > 0)
            {
                (*p)->Bal = 0;
                Rost = 0;
            }
            else if ((*p)->Bal == 0)
            {
                (*p)->Bal = -1;
                Rost = 1;
            }
            else
            {
                if ((*p)->Left->Bal < 0)
                    LL(p);
                else
                    LR(p);

                Rost = 0;
            }
        }
    }
    else if ((*p)->Data < D)
    {
        addAVL(D, &(*p)->Right);

        if (Rost)
        {
            if ((*p)->Bal < 0)
            {
                (*p)->Bal = 0;
                Rost = 0;
            }
            else if ((*p)->Bal == 0)
            {
                (*p)->Bal = 1;
                Rost = 1;
            }
            else
            {
                if ((*p)->Right->Bal > 0)
                    RR(p);
                else
                    RL(p);

                Rost = 0;
            }
        }
    }
    else
    {
        Rost = 0;
    }
}
