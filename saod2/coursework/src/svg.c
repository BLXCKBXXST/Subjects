#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct Layout
{
    struct Derevo *node;
    struct Layout *left;
    struct Layout *right;
    int leftX;
    int rightX;
    int depth;
    int *minX;
    int *maxX;
};

static struct Layout *makeLayout(struct Derevo *node)
{
    if (node == NULL)
        return NULL;

    struct Layout *p = calloc(1, sizeof(*p));
    if (p == NULL)
        exit(1);

    p->node = node;
    p->left = makeLayout(node->left);
    p->right = makeLayout(node->right);

    int a = p->left ? p->left->depth : 0;
    int b = p->right ? p->right->depth : 0;

    p->depth = 1 + (a > b ? a : b);
    p->minX = malloc((size_t)p->depth * sizeof(int));
    p->maxX = malloc((size_t)p->depth * sizeof(int));

    if (p->minX == NULL || p->maxX == NULL)
        exit(1);

    if (p->left && p->right)
    {
        int distance = 20;
        int overlap = a < b ? a : b;

        for (int i = 0; i < overlap; i++)
        {
            int needed = p->left->maxX[i] - p->right->minX[i] + 4;
            if (needed > distance)
                distance = needed;
        }

        p->leftX = -distance / 2;
        p->rightX = p->leftX + distance;
    }
    else if (p->left)
        p->leftX = -10;
    else if (p->right)
        p->rightX = 10;

    p->minX[0] = -8;
    p->maxX[0] = 8;

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
            int left = p->right->minX[i - 1] + p->rightX;
            int right = p->right->maxX[i - 1] + p->rightX;

            if (left < min)
                min = left;
            if (right > max)
                max = right;
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

    int px = 20 * x;
    int py = 80 + 200 * level;

    if (p->left)
    {
        int child = x + p->leftX;
        fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"/>\n",
                px, py, 20 * child, py + 200);
        svgEdges(file, p->left, child, level + 1);
    }

    if (p->right)
    {
        int child = x + p->rightX;
        fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"/>\n",
                px, py, 20 * child, py + 200);
        svgEdges(file, p->right, child, level + 1);
    }
}

static void xmlText(FILE *file, const char *s)
{
    for (; *s; s++) {
        if (*s == '&') fputs("&amp;", file);
        else if (*s == '<') fputs("&lt;", file);
        else if (*s == '>') fputs("&gt;", file);
        else if (*s == '"') fputs("&quot;", file);
        else fputc(*s, file);
    }
}

static void titleLines(FILE *file, const char *key, int x, int y)
{
    char lines[2][65] = {{0}};
    int lengths[2] = {0}, line = 0, count = 0;
    const unsigned char *p = (const unsigned char *)key;
    while (*p) {
        if (count == 18) { line++; count = 0; }
        if (line == 2) break;
        int bytes = *p < 128 ? 1 : 2;
        if (lengths[line] + bytes >= 65) break;
        for (int j = 0; j < bytes && *p; j++) lines[line][lengths[line]++] = (char)*p++;
        count++;
    }
    int rows = line + 1;
    if (rows > 2) rows = 2;
    for (int i = 0; i < rows; i++) {
        fprintf(file, "<text class=\"name\" x=\"%d\" y=\"%d\">", x, y - (rows == 2 ? 15 : 4) + i * 23);
        xmlText(file, lines[i]);
        fputs("</text>\n", file);
    }
}

static void svgNodes(FILE *file, struct Layout *p, int x, int level)
{
    if (p == NULL) return;
    int px = 20 * x, py = 80 + 200 * level;
    fputs("<g><title>", file);
    xmlText(file, p->node->key);
    fprintf(file, "</title><rect class=\"node\" x=\"%d\" y=\"%d\" width=\"320\" height=\"116\" rx=\"10\"/>\n", px - 160, py - 58);
    titleLines(file, p->node->key, px, py);
    fprintf(file, "<text class=\"weight\" x=\"%d\" y=\"%d\">Вес: %d</text></g>\n", px, py + 38, p->node->weight);
    svgNodes(file, p->left, x + p->leftX, level + 1);
    svgNodes(file, p->right, x + p->rightX, level + 1);
}

int sohranit_svg(struct Derevo *root, const char *filename)
{
    if (root == NULL)
    {
        FILE *file = fopen(filename, "w");
        if (file == NULL)
            return 0;
        fputs("<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 400 120\" width=\"400\" height=\"120\">\n"
              "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n"
              "<text x=\"200\" y=\"65\" fill=\"#2563eb\" text-anchor=\"middle\" "
              "font-family=\"Arial,sans-serif\" font-size=\"20\">Дерево ещё не построено</text>\n</svg>\n", file);
        return fclose(file) == 0;
    }

    struct Layout *p = makeLayout(root);
    int left = 0;
    int right = 0;

    for (int i = 0; i < p->depth; i++)
    {
        if (p->minX[i] < left)
            left = p->minX[i];
        if (p->maxX[i] > right)
            right = p->maxX[i];
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        freeLayout(p);
        return 0;
    }

    int width = 20 * (right - left + 8);
    int height = p->depth * 200 - 40;
    int start = 4 - left;

    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file,
            "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 %d %d\" width=\"%d\" height=\"%d\">\n",
            width, height, width, height);
    fprintf(file, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");

    fprintf(file, "<g stroke=\"#64748b\" stroke-opacity=\"0.30\" stroke-width=\"1\" stroke-dasharray=\"4 7\">\n");
    for (int level = 0; level < p->depth - 1; level++)
        fprintf(file, "<line x1=\"8\" y1=\"%d\" x2=\"%d\" y2=\"%d\"/>\n",
                180 + 200 * level, width - 8, 180 + 200 * level);
    fprintf(file, "</g>\n");

    fprintf(file, "<g stroke=\"#64748b\" stroke-width=\"2\">\n");
    svgEdges(file, p, start, 0);
    fprintf(file, "</g>\n");

    fprintf(file, "<g fill=\"#2563eb\" stroke=\"#1e40af\" stroke-width=\"1\">\n");
    svgNodes(file, p, start, 0);
    fprintf(file, "</g>\n");

    fprintf(file, "<style>text{fill:white;stroke:none;font:600 16px Arial,sans-serif;text-anchor:middle}.weight{font-size:13px}</style>\n");
    fprintf(file, "</svg>\n");

    int ok = fclose(file) == 0;
    freeLayout(p);
    return ok;
}
