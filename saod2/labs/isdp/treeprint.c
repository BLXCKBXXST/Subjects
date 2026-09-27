#include <stdio.h>
#include "treeprint.h"

struct Node
{
    int Data;
    struct Node *Left;
    struct Node *Right;
};

static void printBranches(struct Node *p, int level, int branch, int lines[])
{
    if (p == NULL)
        return;

    if (p->Right != NULL)
    {
        lines[level] = (p->Left != NULL);

        printBranches(p->Right, level + 1, 1, lines);
    }

    for (int i = 0; i < level - 1; i++)
    {
        if (lines[i])
            printf("│       ");
        else
            printf("        ");
    }

    if (level > 0)
    {
        if (branch == 1)
            printf("┌────── ");
        else
            printf("└────── ");
    }

    printf("%d\n", p->Data);

    if (p->Left != NULL)
    {
        lines[level] = 0;

        printBranches(p->Left, level + 1, -1, lines);
    }
}

void printTreeVisual(struct Node *root)
{
    int lines[100] = {0};

    printf("\nПостроенное ИСДП (N = 100):\n\n");

    printBranches(root, 0, 0, lines);
}