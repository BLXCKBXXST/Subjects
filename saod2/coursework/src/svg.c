#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct {
    struct Derevo *node;
    int x, y;
} Position;

static int count_nodes(struct Derevo *p) {
    if (p == NULL) return 0;
    return 1 + count_nodes(p->left) + count_nodes(p->right);
}

static int depth(struct Derevo *p) {
    if (p == NULL) return 0;
    int l = depth(p->left), r = depth(p->right);
    return 1 + (l > r ? l : r);
}

static void positions(struct Derevo *p, Position *a, int *n, int level) {
    if (p == NULL) return;
    positions(p->left, a, n, level + 1);
    a[*n].node = p;
    a[*n].x = 125 + (*n) * 280;
    a[*n].y = 130 + level * 155;
    (*n)++;
    positions(p->right, a, n, level + 1);
}

static Position *find(Position *a, int n, struct Derevo *p) {
    for (int i = 0; i < n; i++)
        if (a[i].node == p) return &a[i];
    return NULL;
}

static void xml_text(FILE *f, const char *s) {
    for (; *s; s++) {
        if (*s == '&') fputs("&amp;", f);
        else if (*s == '<') fputs("&lt;", f);
        else if (*s == '>') fputs("&gt;", f);
        else if (*s == '"') fputs("&quot;", f);
        else fputc(*s, f);
    }
}

static void wrapped_name(FILE *f, const char *name, int x, int y) {
    char lines[4][128] = {{0}};
    int lengths[4] = {0};
    int line = 0, chars = 0;
    const unsigned char *p = (const unsigned char *)name;

    while (*p && line < 4) {
        int bytes = (*p < 128) ? 1 : ((*p & 0xE0) == 0xC0 ? 2 : ((*p & 0xF0) == 0xE0 ? 3 : 4));
        if (*p == ' ' && chars >= 13 && line < 3) {
            line++;
            chars = 0;
            p++;
            continue;
        }
        if (chars >= 17 && line < 3) {
            line++;
            chars = 0;
        }
        if (lengths[line] + bytes >= 127) break;
        for (int j = 0; j < bytes && p[j]; j++)
            lines[line][lengths[line]++] = (char)p[j];
        chars++;
        p += bytes;
    }

    int count = line + 1;
    for (int i = 0; i < count; i++) {
        int yy = y - 30 + i * 19;
        fprintf(f, "<text class=\"name\" x=\"%d\" y=\"%d\" text-anchor=\"middle\">", x, yy);
        xml_text(f, lines[i]);
        fputs("</text>\n", f);
    }
}

int sohranit_svg(struct Derevo *root, const char *filename) {
    int n = count_nodes(root);
    if (n == 0) return 0;
    Position *a = malloc(n * sizeof(Position));
    if (a == NULL) return 0;
    int k = 0;
    positions(root, a, &k, 0);
    FILE *f = fopen(filename, "w");
    if (f == NULL) { free(a); return 0; }
    int w = 280 + (n - 1) * 280;
    int h = 260 + (depth(root) - 1) * 155;
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\" viewBox=\"0 0 %d %d\">\n", w, h, w, h);
    fputs("<rect width=\"100%\" height=\"100%\" fill=\"#f8fafc\"/>\n", f);
    fputs("<style>text{font-family:Arial,sans-serif} .edge{stroke:#94a3b8;stroke-width:3;fill:none} .node{fill:#ffffff;stroke:#2563eb;stroke-width:2.5} .name{font-size:18px;fill:#0f172a;font-weight:bold} .weight{font-size:15px;fill:#475569}</style>\n", f);
    for (int i = 0; i < n; i++) {
        struct Derevo *p = a[i].node;
        struct Derevo *children[2] = {p->left, p->right};
        for (int j = 0; j < 2; j++) {
            Position *c = find(a, n, children[j]);
            if (c != NULL)
                fprintf(f, "<path class=\"edge\" d=\"M%d %d L%d %d\"/>\n", a[i].x, a[i].y + 49, c->x, c->y - 49);
        }
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "<rect class=\"node\" x=\"%d\" y=\"%d\" width=\"260\" height=\"110\" rx=\"15\"/>\n", a[i].x - 130, a[i].y - 55);
        wrapped_name(f, a[i].node->key, a[i].x, a[i].y);
        fprintf(f, "<text class=\"weight\" x=\"%d\" y=\"%d\" text-anchor=\"middle\">Вес: %d</text>\n", a[i].x, a[i].y + 43, a[i].node->weight);
    }
    fputs("</svg>\n", f);
    fclose(f);
    free(a);
    return 1;
}
