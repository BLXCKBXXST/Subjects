#include <stdlib.h>
#include "3.2-isdp.h"

struct Node *ISDP(int A[], int L, int R)
{
    if (L > R)
        return NULL;

    int m = (L + R) / 2;

    struct Node *p = malloc(sizeof(struct Node));

    if (p == NULL) exit(1);
    p->Data = A[m];
    p->Left = ISDP(A, L, m - 1);
    p->Right = ISDP(A, m + 1, R);

    return p;
}

