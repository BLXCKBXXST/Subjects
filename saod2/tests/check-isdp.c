#include <assert.h>
#include <stdlib.h>
#include "../labs/3.2-isdp/3.2-isdp.h"
static int verify(struct Node *p, int low, int high)
{
    if (!p) return 0;
    assert(p->Data > low && p->Data < high);
    int a = verify(p->Left, low, p->Data);
    int b = verify(p->Right, p->Data, high);
    assert(abs(a - b) <= 1);
    return 1 + (a > b ? a : b);
}
int main(void)
{
    for (int n = 0; n <= 500; n++)
    {
        int a[500];
        for (int i = 0; i < n; i++) a[i] = n - i;
        sortArray(a, 0, n - 1);
        struct Node *p = ISDP(a, 0, n - 1);
        assert(size(p) == n);
        assert(checkSum(p) == n * (n + 1) / 2);
        assert(verify(p, 0, n + 1) == height(p));
        for (int key = 1; key <= n; key++) assert(searchRecursive(p, key));
        assert(!searchRecursive(p, n + 1));
        freeTree(p);
    }
    int equal[] = {2,2,2,1,3,1,3};
    sortArray(equal, 0, 6);
    for (int i = 1; i < 7; i++) assert(equal[i - 1] <= equal[i]);
}
