#include <stdio.h>
#include <stdlib.h>
#include "dbd.h"

struct Page
{
    const struct Node *first;
    const struct Node *second;
    struct Page *child[3];
    int width;
    int x;
    int y;
};

static struct Page *makePage(const struct Node *root)
{
    if (root == NULL)
        return NULL;

    struct Page *p = calloc(1, sizeof(struct Page));
    if (p == NULL)
        exit(1);

    p->first = root;
    if (root->Bal == 1)
    {
        p->second = root->Right;
        p->child[0] = makePage(root->Left);
        p->child[1] = makePage(root->Right->Left);
        p->child[2] = makePage(root->Right->Right);
    }
    else
    {
        p->child[0] = makePage(root->Left);
        p->child[1] = makePage(root->Right);
    }

    int count = 0;
    int total = 0;
    for (int i = 0; i < 3; i++)
        if (p->child[i] != NULL)
        {
            total += p->child[i]->width;
            count++;
        }

    if (count > 1)
        total += (count - 1) * 24;

    int pageWidth = p->second ? 136 : 74;
    p->width = total > pageWidth ? total : pageWidth;
    return p;
}

static void arrange(struct Page *p, int left, int level)
{
    if (p == NULL)
        return;

    p->x = left + p->width / 2;
    p->y = 47 + level * 100;

    int count = 0;
    int total = 0;
    for (int i = 0; i < 3; i++)
        if (p->child[i] != NULL)
        {
            total += p->child[i]->width;
            count++;
        }

    if (count > 1)
        total += (count - 1) * 24;

    int childLeft = left + (p->width - total) / 2;
    for (int i = 0; i < 3; i++)
        if (p->child[i] != NULL)
        {
            arrange(p->child[i], childLeft, level + 1);
            childLeft += p->child[i]->width + 24;
        }
}

static void drawEdges(FILE *f, const struct Page *p)
{
    if (p == NULL)
        return;

    for (int i = 0; i < 3; i++)
        if (p->child[i] != NULL)
        {
            const struct Page *q = p->child[i];
            fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#64748b\" stroke-width=\"2\"/>\n",
                    p->x, p->y + 24, q->x, q->y - 24);
            drawEdges(f, q);
        }
}

static void drawNodes(FILE *f, const struct Page *p)
{
    if (p == NULL)
        return;

    int x = p->x, y = p->y;
    int half = p->second ? 68 : 37;

    fprintf(f, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"52\" rx=\"10\" stroke=\"#0d9488\" stroke-dasharray=\"5 4\" fill=\"#f0fdfa\"/>\n",
            x - half, y - 26, 2 * half);

    if (p->second != NULL)
    {
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#0d9488\" stroke-width=\"4\"/>\n",
                x - 11, y, x + 11, y);
        fprintf(f, "<circle cx=\"%d\" cy=\"%d\" r=\"20\" fill=\"white\" stroke=\"#334155\"/>\n", x - 34, y);
        fprintf(f, "<circle cx=\"%d\" cy=\"%d\" r=\"20\" fill=\"white\" stroke=\"#334155\"/>\n", x + 34, y);
        fprintf(f, "<text x=\"%d\" y=\"%d\">%d</text>\n", x - 34, y + 5, p->first->Data);
        fprintf(f, "<text x=\"%d\" y=\"%d\">%d</text>\n", x + 34, y + 5, p->second->Data);
    }
    else
    {
        fprintf(f, "<circle cx=\"%d\" cy=\"%d\" r=\"20\" fill=\"white\" stroke=\"#334155\"/>\n", x, y);
        fprintf(f, "<text x=\"%d\" y=\"%d\">%d</text>\n", x, y + 5, p->first->Data);
    }

    for (int i = 0; i < 3; i++)
        drawNodes(f, p->child[i]);
}

static void freePages(struct Page *p)
{
    if (p == NULL)
        return;

    for (int i = 0; i < 3; i++)
        freePages(p->child[i]);
    free(p);
}

int saveDBDSvg(const char *filename, struct Node *root)
{
    struct Page *layout = makePage(root);
    if (layout == NULL)
        return 0;

    arrange(layout, 30, 0);
    int width = layout->width + 60;
    int height = pageLevels(root) * 100 + 20;

    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        freePages(layout);
        return 0;
    }

    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 %d %d\" width=\"%d\" height=\"%d\">\n", width, height, width, height);
    fprintf(f, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
    fprintf(f, "<style>text{font:600 13px Arial,sans-serif;fill:#0f172a;text-anchor:middle}</style>\n");
    drawEdges(f, layout);
    drawNodes(f, layout);
    fputs("</svg>\n", f);

    int ok = fclose(f) == 0;
    freePages(layout);
    return ok;
}

void showDBDImage(struct Node *root)
{
    if (!saveDBDSvg("dbd.svg", root))
    {
        perror("dbd.svg");
        return;
    }

    printf("Изображение ДБД: dbd.svg\n");
    fflush(stdout);
    if (system("command -v xdg-open >/dev/null 2>&1") == 0)
    {
        if (system("xdg-open labs/dbd/preview.html >/dev/null 2>&1 &") != 0)
            printf("Откройте labs/dbd/preview.html в браузере.\n");
    }
    else
        printf("Откройте labs/dbd/preview.html в браузере.\n");
}
