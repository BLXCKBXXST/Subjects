#include <assert.h>
#include <stdlib.h>
#include "../labs/3.6-avl-delete/3.6-avl-delete.h"

static int check(struct Node *p, int lo, int hi)
{
    if (!p) return 0;
    assert(lo < p->Data && p->Data < hi);
    int l = check(p->Left, lo, p->Data);
    int r = check(p->Right, p->Data, hi);
    assert(p->Bal == r - l);
    assert(abs(r - l) <= 1);
    return 1 + (l > r ? l : r);
}

int main(void)
{
    for (int run = 0; run < 20; run++)
    {
        int a[300];
        struct Node *root = NULL;
        for (int i = 0; i < 300; i++) a[i] = i + 1;
        for (int i = 299; i > 0; i--)
        {
            int j = rand() % (i + 1), t = a[i];
            a[i] = a[j]; a[j] = t;
        }
        for (int i = 0; i < 300; i++)
        {
            addAVL(a[i], &root);
            check(root, 0, 1001);
            assert(size(root) == i + 1);
        }
        assert(!deleteAVL(999, &root));
        for (int i = 0; i < 300; i++)
        {
            assert(deleteAVL(a[i], &root));
            check(root, 0, 1001);
            assert(size(root) == 299 - i);
        }
        assert(!root);
    }
    return 0;
}
