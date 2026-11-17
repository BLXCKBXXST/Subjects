#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "../../labs/3.9-a1-a2/3.9-a1-a2.h"

static struct Derevo *privyazat_zapisi(Vertex *p, Group *g, Element *a) {
    if (p == NULL) return NULL;

    int i = p->Index;
    struct Derevo *root = malloc(sizeof(struct Derevo));
    if (root == NULL) { perror("А2"); exit(EXIT_FAILURE); }
    kopirovat(root->key, g[i].key);
    root->weight = p->Weight;
    root->zapisi = malloc(root->weight * sizeof(struct Zapis *));
    if (root->zapisi == NULL) {
        perror("Записи А2");
        free(root);
        exit(EXIT_FAILURE);
    }
    for (int j = 0; j < root->weight; j++)
        root->zapisi[j] = a[g[i].start + j].zapis;

    root->left = privyazat_zapisi(p->Left, g, a);
    root->right = privyazat_zapisi(p->Right, g, a);
    free(p);
    return root;
}

struct Derevo *a2(Group *g, Element *a, int L, int R) {
    if (L > R) return NULL;

    int n = R - L + 1;
    WeightedItem *V = malloc(n * sizeof(WeightedItem));
    if (V == NULL) { perror("А2"); exit(EXIT_FAILURE); }
    for (int i = 0; i < n; i++) {
        V[i].Data = L + i;
        V[i].Weight = g[L + i].weight;
        V[i].Index = L + i;
    }

    Vertex *root = NULL;
    A2(V, 0, n - 1, &root);
    free(V);
    return privyazat_zapisi(root, g, a);
}
