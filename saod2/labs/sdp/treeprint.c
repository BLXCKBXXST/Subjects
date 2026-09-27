#include <stdio.h>
#include "sdp.h"

static void printBranches(struct Node *root, int level, int side, int lines[])
{
    if (root == NULL)
        return;

    if (root->Right != NULL)
    {
        lines[level] = root->Left != NULL;
        printBranches(root->Right, level + 1, 1, lines);
    }

    for (int i = 0; i < level - 1; i++)
        printf("%s", lines[i] ? "│       " : "        ");

    if (level > 0)
        printf("%s", side == 1 ? "┌────── " : "└────── ");
    printf("%d\n", root->Data);

    if (root->Left != NULL)
    {
        lines[level] = 0;
        printBranches(root->Left, level + 1, -1, lines);
    }
}

void printTreeVisual(struct Node *root)
{
    int lines[100] = {0};
    printBranches(root, 0, 0, lines);
}
