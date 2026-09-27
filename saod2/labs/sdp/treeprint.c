#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdp.h"

struct Position
{
    struct Node *node;
    int x;
    int level;
    int left;
    int right;
};

static int place(struct Node *root, int level, int *next, struct Position P[])
{
    if (root == NULL)
        return -1;

    int left = place(root->Left, level + 1, next, P);
    int current = (*next)++;
    P[current].node = root;
    P[current].x = current * 6 + 3;
    P[current].level = level;
    P[current].left = left;
    P[current].right = place(root->Right, level + 1, next, P);
    return current;
}

static int countNodes(struct Node *root)
{
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->Left) + countNodes(root->Right);
}

static int treeHeight(struct Node *root)
{
    if (root == NULL)
        return 0;
    int left = treeHeight(root->Left);
    int right = treeHeight(root->Right);
    return 1 + (left > right ? left : right);
}

void printTreeVisual(struct Node *root)
{
    if (root == NULL)
    {
        printf("(пустое дерево)\n");
        return;
    }

    int n = countNodes(root);
    int levels = treeHeight(root);
    struct Position *P = malloc((size_t)n * sizeof(*P));
    if (P == NULL)
        exit(1);

    int next = 0;
    int rootIndex = place(root, 0, &next, P);
    int rootX = P[rootIndex].x;
    int leftWidth = rootX;
    int rightWidth = P[n - 1].x - rootX;
    int half = (leftWidth > rightWidth ? leftWidth : rightWidth) + 5;
    int width = 2 * half + 1;
    int shift = half - rootX;
    int rows = levels * 2 - 1;

    char **canvas = malloc((size_t)rows * sizeof(*canvas));
    if (canvas == NULL)
        exit(1);

    for (int row = 0; row < rows; row++)
    {
        canvas[row] = malloc((size_t)width + 1);
        if (canvas[row] == NULL)
            exit(1);
        memset(canvas[row], ' ', (size_t)width);
        canvas[row][width] = '\0';
    }

    for (int i = 0; i < n; i++)
    {
        int x = P[i].x + shift;
        int row = P[i].level * 2;
        char number[24];
        snprintf(number, sizeof(number), "%d", P[i].node->Data);
        int start = x - (int)strlen(number) / 2;
        memcpy(canvas[row] + start, number, strlen(number));

        if (P[i].left >= 0)
        {
            int childX = P[P[i].left].x + shift;
            canvas[row + 1][(x + childX) / 2] = '/';
        }
        if (P[i].right >= 0)
        {
            int childX = P[P[i].right].x + shift;
            canvas[row + 1][(x + childX) / 2] = '\\';
        }
    }

    for (int row = 0; row < rows; row++)
    {
        int end = width;
        while (end > 0 && canvas[row][end - 1] == ' ')
            end--;
        canvas[row][end] = '\0';
        printf("%s\n", canvas[row]);
        free(canvas[row]);
    }

    free(canvas);
    free(P);
}
