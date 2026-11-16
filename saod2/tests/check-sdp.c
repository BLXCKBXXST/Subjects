#include <assert.h>
#include <stdlib.h>
#include "../labs/3.4-sdp-delete/3.4-sdp-delete.h"
static void verify(struct Node *p, int low, int high)
{
    if (!p) return;
    assert(p->Data >= low && p->Data < high);
    verify(p->Left, low, p->Data);
    verify(p->Right, p->Data, high);
}
static int same(struct Node *a, struct Node *b)
{
    if (!a || !b) return a == b;
    return a->Data == b->Data && same(a->Left, b->Left) && same(a->Right, b->Right);
}
int main(void)
{
    for (int round = 0; round < 30; round++)
    {
        int a[300];
        for (int i = 0; i < 300; i++) a[i] = i + 1;
        for (int i = 299; i > 0; i--)
        {
            int j = rand() % (i + 1), t = a[i]; a[i] = a[j]; a[j] = t;
        }
        struct Node *p = NULL, *q = NULL;
        for (int i = 0; i < 300; i++) { insertRecursive(&p, a[i]); insertDouble(&q, a[i]); }
        assert(same(p, q));
        assert(size(p) == 300);
        assert(!deleteNodeMove(&p, 0));
        for (int i = 0; i < 300; i++)
        {
            assert(searchRecursive(p, a[i]));
            assert(deleteNodeMove(&p, a[i]));
            assert(deleteNode(&q, a[i]));
            verify(p, 1, 301);
            assert(same(p, q));
            assert(size(p) == 299 - i);
        }
        assert(!p && !q);
    }
    struct Node *p = NULL;
    int values[] = {20,10,30,5,15,12};
    for (int i = 0; i < 6; i++) insertDouble(&p, values[i]);
    struct Node *predecessor = p->Left->Right;
    assert(deleteNodeMove(&p, 20));
    assert(p == predecessor);
    assert(p->Left->Right->Data == 12);
    freeTree(p);
    p = NULL;
    insertRecursive(&p, 7); insertRecursive(&p, 7); insertDouble(&p, 7);
#ifdef REPEAT_KEYS
    assert(size(p) == 3);
#else
    assert(size(p) == 1);
#endif
    verify(p, 1, 301);
    freeTree(p);
}
