#ifndef TREE_H
#define TREE_H

#include "zapis.h"

struct Derevo {
    char key[65];
    int weight;
    struct Zapis **zapisi;
    struct Derevo *left, *right;
};

int sravnit(const char *a, const char *b);
struct Derevo *postroit_a2(struct Zapis **zapisi, int n);
void pokazat_derevo(struct Derevo *root);
void poisk_derevo(struct Derevo *root, const char *key);
void ochistit_derevo(struct Derevo *root);

#endif
