#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct Derevo *a2(Group *g, Element *a, int L, int R) {
    if (L > R) return NULL;

    int total = 0, sum = 0, i, j;
    for (i = L; i <= R; i++) total += g[i].weight;

    for (i = L; i < R; i++) {
        if (2 * (sum + g[i].weight) >= total) break;
        sum += g[i].weight;
    }

    struct Derevo *p = malloc(sizeof(struct Derevo));
    if (p == NULL) { perror("А2"); exit(EXIT_FAILURE); }
    kopirovat(p->key, g[i].key);
    p->weight = g[i].weight;
    p->zapisi = malloc(p->weight * sizeof(struct Zapis *));
    if (p->zapisi == NULL) { perror("Записи А2"); free(p); exit(EXIT_FAILURE); }
    for (j = 0; j < p->weight; j++)
        p->zapisi[j] = a[g[i].start + j].zapis;

    p->left = a2(g, a, L, i - 1);
    p->right = a2(g, a, i + 1, R);
    return p;
}
