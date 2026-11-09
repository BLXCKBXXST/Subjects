#include <stdio.h>
#include "dop.h"

static void drawLines(FILE *f, Vertex *p, int level)
{
    if (p == NULL)
        return;

    int x = 30 + p->Index * 54;
    int y = 35 + level * 80;

    if (p->Left != NULL)
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#94a3b8\" stroke-width=\"2\"/>\n",
                x, y, 30 + p->Left->Index * 54, y + 80);
    if (p->Right != NULL)
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#94a3b8\" stroke-width=\"2\"/>\n",
                x, y, 30 + p->Right->Index * 54, y + 80);

    drawLines(f, p->Left, level + 1);
    drawLines(f, p->Right, level + 1);
}

static void drawNodes(FILE *f, Vertex *p, int level)
{
    if (p == NULL)
        return;

    int x = 30 + p->Index * 54;
    int y = 35 + level * 80;
    fprintf(f, "<rect x=\"%d\" y=\"%d\" width=\"46\" height=\"40\" rx=\"8\" fill=\"#eff6ff\" stroke=\"#2563eb\"/>\n",
            x - 23, y - 20);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-size=\"13\" font-weight=\"bold\">%d</text>\n",
            x, y - 2, p->Data);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-size=\"11\">w=%d</text>\n",
            x, y + 13, p->Weight);

    drawNodes(f, p->Left, level + 1);
    drawNodes(f, p->Right, level + 1);
}

static int getHeight(Vertex *p)
{
    if (p == NULL)
        return 0;
    int l = getHeight(p->Left);
    int r = getHeight(p->Right);
    return 1 + (l > r ? l : r);
}

int saveSVG(const char *filename, Vertex *root, int n)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
        return 0;

    int width = (n + 1) * 54 + 20;
    int height = getHeight(root) * 80 + 40;

    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 %d %d\" width=\"%d\" height=\"%d\">\n",
            width, height, width, height);
    fprintf(f, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
    fprintf(f, "<style>text {font-family:Arial,sans-serif;text-anchor:middle;fill:#0f172a}</style>\n");
    drawLines(f, root, 0);
    drawNodes(f, root, 0);
    fprintf(f, "</svg>\n");
    return fclose(f) == 0;
}