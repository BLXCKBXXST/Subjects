#include <stdio.h>
#include <stdlib.h>
#include "sdp.h"

struct Layout
{
    struct Node *node;
    struct Layout *left;
    struct Layout *right;
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

    int a = p->left ? p->left->depth : 0;
    int b = p->right ? p->right->depth : 0;
    p->depth = 1 + (a > b ? a : b);
    p->minX = malloc((size_t)p->depth * sizeof(int));
    p->maxX = malloc((size_t)p->depth * sizeof(int));
    if (p->minX == NULL || p->maxX == NULL)
        exit(1);

    if (p->left && p->right)
    {
        int distance = 6;
        int overlap = a < b ? a : b;
        for (int i = 0; i < overlap; i++)
        {
            int needed = p->left->maxX[i] - p->right->minX[i] + 5;
            if (needed > distance)
                distance = needed;
        }
        p->leftX = -distance / 2;
        p->rightX = p->leftX + distance;
    }
    else if (p->left)
        p->leftX = -3;
    else if (p->right)
        p->rightX = 3;

    p->minX[0] = -2;
    p->maxX[0] = 2;
    for (int i = 1; i < p->depth; i++)
    {
        int min = 1000000000;
        int max = -1000000000;
        if (p->left && i <= a)
        {
            min = p->left->minX[i - 1] + p->leftX;
            max = p->left->maxX[i - 1] + p->leftX;
        }
        if (p->right && i <= b)
        {
            int l = p->right->minX[i - 1] + p->rightX;
            int r = p->right->maxX[i - 1] + p->rightX;
            if (l < min) min = l;
            if (r > max) max = r;
        }
        p->minX[i] = min;
        p->maxX[i] = max;
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

static void svgEdges(FILE *file, struct Layout *p, int x, int level)
{
    if (p == NULL)
        return;
    int px = 14 * x;
    int py = 38 + 76 * level;
    if (p->left)
    {
        int child = x + p->leftX;
        fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"/>\n",
                px, py, 14 * child, py + 76);
        svgEdges(file, p->left, child, level + 1);
    }
    if (p->right)
    {
        int child = x + p->rightX;
        fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"/>\n",
                px, py, 14 * child, py + 76);
        svgEdges(file, p->right, child, level + 1);
    }
}

static void svgNodes(FILE *file, struct Layout *p, int x, int level)
{
    if (p == NULL)
        return;
    int px = 14 * x;
    int py = 38 + 76 * level;
    fprintf(file, "<g><title>%d</title><circle cx=\"%d\" cy=\"%d\" r=\"19\"/>"
                  "<text x=\"%d\" y=\"%d\">%d</text></g>\n",
            p->node->Data, px, py, px, py + 5, p->node->Data);
    svgNodes(file, p->left, x + p->leftX, level + 1);
    svgNodes(file, p->right, x + p->rightX, level + 1);
}

int saveTreeSvg(const char *filename, struct Node *root)
{
    if (root == NULL)
        return 0;
    struct Layout *p = makeLayout(root);
    int left = 0, right = 0;
    for (int i = 0; i < p->depth; i++)
    {
        if (p->minX[i] < left) left = p->minX[i];
        if (p->maxX[i] > right) right = p->maxX[i];
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        freeLayout(p);
        return 0;
    }
    int width = 14 * (right - left + 8);
    int height = p->depth * 76 + 24;
    int start = 4 - left;
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 %d %d\" width=\"%d\" height=\"%d\">\n",
            width, height, width, height);
    fprintf(file, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
    /* Едва заметные границы между уровнями дерева. */
    fprintf(file, "<g stroke=\"#64748b\" stroke-opacity=\"0.16\" stroke-width=\"1\" stroke-dasharray=\"4 7\">\n");
    for (int level = 0; level < p->depth - 1; level++)
        fprintf(file, "<line x1=\"8\" y1=\"%d\" x2=\"%d\" y2=\"%d\"/>\n",
                76 + 76 * level, width - 8, 76 + 76 * level);
    fprintf(file, "</g>\n");

    fprintf(file, "<g stroke=\"#64748b\" stroke-width=\"2\">\n");
    svgEdges(file, p, start, 0);
    fprintf(file, "</g>\n<g fill=\"#2563eb\" stroke=\"#1e40af\" stroke-width=\"1\">\n");
    svgNodes(file, p, start, 0);
    fprintf(file, "</g>\n<style>text{fill:white;stroke:none;font:600 13px Arial,sans-serif;text-anchor:middle}</style>\n</svg>\n");
    int ok = fclose(file) == 0;
    freeLayout(p);
    return ok;
}
