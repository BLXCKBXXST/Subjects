#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdp.h"

struct Layout
{
    struct Node *node;
    struct Layout *left, *right;
    int leftX, rightX;
    int depth;
    int *minX, *maxX;
};

static struct Layout *makeLayout(struct Node *node)
{
    if (node == NULL)
        return NULL;

    struct Layout *p = calloc(1, sizeof(*p));
    if (p == NULL)
        exit(1);
    p->node = node;
    p->left = makeLayout(node->Left);
    p->right = makeLayout(node->Right);

    int leftDepth = p->left ? p->left->depth : 0;
    int rightDepth = p->right ? p->right->depth : 0;
    p->depth = 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    p->minX = malloc((size_t)p->depth * sizeof(int));
    p->maxX = malloc((size_t)p->depth * sizeof(int));
    if (p->minX == NULL || p->maxX == NULL)
        exit(1);

    if (p->left && p->right)
    {
        int separation = 8;
        int overlap = leftDepth < rightDepth ? leftDepth : rightDepth;
        for (int d = 0; d < overlap; d++)
        {
            int need = p->left->maxX[d] - p->right->minX[d] + 6;
            if (need > separation)
                separation = need;
        }
        p->leftX = -separation / 2;
        p->rightX = p->leftX + separation;
    }
    else if (p->left)
        p->leftX = -4;
    else if (p->right)
        p->rightX = 4;

    char label[32];
    snprintf(label, sizeof(label), "%d", node->Data);
    int len = (int)strlen(label);
    p->minX[0] = -len / 2;
    p->maxX[0] = p->minX[0] + len - 1;

    for (int d = 1; d < p->depth; d++)
    {
        int min = 1000000000;
        int max = -1000000000;
        if (p->left && d <= leftDepth)
        {
            min = p->left->minX[d - 1] + p->leftX;
            max = p->left->maxX[d - 1] + p->leftX;
        }
        if (p->right && d <= rightDepth)
        {
            int a = p->right->minX[d - 1] + p->rightX;
            int b = p->right->maxX[d - 1] + p->rightX;
            if (a < min) min = a;
            if (b > max) max = b;
        }
        p->minX[d] = min;
        p->maxX[d] = max;
    }
    return p;
}

static void freeLayout(struct Layout *p)
{
    if (p == NULL)
        return;
    freeLayout(p->left);
    freeLayout(p->right);
    free(p->minX);
    free(p->maxX);
    free(p);
}

static void draw(struct Layout *p, int x, int level, char **lines)
{
    if (p == NULL)
        return;
    char label[32];
    snprintf(label, sizeof(label), "%d", p->node->Data);
    int len = (int)strlen(label);
    memcpy(lines[2 * level] + x - len / 2, label, (size_t)len);

    if (p->left)
    {
        int child = x + p->leftX;
        lines[2 * level + 1][(x + child) / 2] = '/';
        draw(p->left, child, level + 1, lines);
    }
    if (p->right)
    {
        int child = x + p->rightX;
        lines[2 * level + 1][(x + child) / 2] = '\\';
        draw(p->right, child, level + 1, lines);
    }
}

void printTreeVisual(FILE *out, struct Node *root)
{
    if (root == NULL)
    {
        fprintf(out, "(пустое дерево)\n");
        return;
    }

    struct Layout *p = makeLayout(root);
    int left = 0, right = 0;
    for (int d = 0; d < p->depth; d++)
    {
        if (p->minX[d] < left) left = p->minX[d];
        if (p->maxX[d] > right) right = p->maxX[d];
    }
    int width = right - left + 3;
    int rows = p->depth * 2 - 1;
    char **lines = malloc((size_t)rows * sizeof(*lines));
    if (lines == NULL)
        exit(1);
    for (int r = 0; r < rows; r++)
    {
        lines[r] = malloc((size_t)width + 1);
        if (lines[r] == NULL)
            exit(1);
        memset(lines[r], ' ', (size_t)width);
        lines[r][width] = '\0';
    }

    draw(p, 1 - left, 0, lines);
    for (int r = 0; r < rows; r++)
    {
        int end = width;
        while (end > 0 && lines[r][end - 1] == ' ')
            end--;
        lines[r][end] = '\0';
        fprintf(out, "%s\n", lines[r]);
        free(lines[r]);
    }
    free(lines);
    freeLayout(p);
}
