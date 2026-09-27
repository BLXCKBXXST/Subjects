#include <stdio.h>
#include <string.h>
#include "sdp.h"

/* Корень сверху; дочерние вершины печатаются ниже. */
static void printBranch(struct Node *root, const char *prefix,
                        const char *label, int last)
{
    if (root == NULL)
        return;

    printf("%s%s%s%d\n", prefix, last ? "└── " : "├── ", label, root->Data);

    char next[512];
    snprintf(next, sizeof(next), "%s%s", prefix, last ? "    " : "│   ");

    if (root->Left != NULL)
        printBranch(root->Left, next, "L: ", root->Right == NULL);
    if (root->Right != NULL)
        printBranch(root->Right, next, "R: ", 1);
}

void printTreeVisual(struct Node *root)
{
    if (root == NULL)
    {
        printf("(пустое дерево)\n");
        return;
    }

    printf("%d\n", root->Data);
    if (root->Left != NULL)
        printBranch(root->Left, "", "L: ", root->Right == NULL);
    if (root->Right != NULL)
        printBranch(root->Right, "", "R: ", 1);
}
