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

static void LL1(struct Node **p)
{
    struct Node *q = (*p)->Left;

    (*p)->Bal = -1;
    q->Bal = 1;
    (*p)->Left = q->Right;
    q->Right = *p;
    *p = q;
}

static void RR1(struct Node **p)
{
    struct Node *q = (*p)->Right;

    (*p)->Bal = 1;
    q->Bal = -1;
    (*p)->Right = q->Left;
    q->Left = *p;
    *p = q;
}

static void leftDecreased(struct Node **p, int *Umen)
{
    if ((*p)->Bal == -1)
        (*p)->Bal = 0;
    else if ((*p)->Bal == 0)
    {
        (*p)->Bal = 1;
        *Umen = 0;
    }
    else if ((*p)->Right->Bal == 0)
    {
        RR1(p);
        *Umen = 0;
    }
    else if ((*p)->Right->Bal > 0)
        RR(p);
    else
        RL(p);
}

static void rightDecreased(struct Node **p, int *Umen)
{
    if ((*p)->Bal == 1)
        (*p)->Bal = 0;
    else if ((*p)->Bal == 0)
    {
        (*p)->Bal = -1;
        *Umen = 0;
    }
    else if ((*p)->Left->Bal == 0)
    {
        LL1(p);
        *Umen = 0;
    }
    else if ((*p)->Left->Bal < 0)
        LL(p);
    else
        LR(p);
}

static int removeMax(struct Node **p, int *Umen)
{
    if ((*p)->Right != NULL)
    {
        int value = removeMax(&(*p)->Right, Umen);
        if (*Umen)
            rightDecreased(p, Umen);
        return value;
    }

    struct Node *q = *p;
    int value = q->Data;
    *p = q->Left;
    free(q);
    *Umen = 1;
    return value;
}

static int deleteNode(int D, struct Node **p, int *Umen)
{
    if (*p == NULL)
        return 0;

    if (D < (*p)->Data)
    {
        if (!deleteNode(D, &(*p)->Left, Umen))
            return 0;
        if (*Umen)
            leftDecreased(p, Umen);
    }
    else if (D > (*p)->Data)
    {
        if (!deleteNode(D, &(*p)->Right, Umen))
            return 0;
        if (*Umen)
            rightDecreased(p, Umen);
    }
    else if ((*p)->Left != NULL && (*p)->Right != NULL)
    {
        (*p)->Data = removeMax(&(*p)->Left, Umen);
        if (*Umen)
            leftDecreased(p, Umen);
    }
    else
    {
        struct Node *q = *p;
        *p = q->Left != NULL ? q->Left : q->Right;
        free(q);
        *Umen = 1;
    }

    return 1;
}

int deleteAVL(int D, struct Node **p)
{
    int Umen = 0;
    return deleteNode(D, p, &Umen);
}
