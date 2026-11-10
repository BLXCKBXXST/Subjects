#ifndef TREE_H
#define TREE_H

#include "zapis.h"

typedef struct {
    struct Zapis *zapis;
    char key[65];
} Element;

typedef struct {
    char key[65];
    int start, weight;
} Group;

struct Derevo {
    char key[65];
    int weight;
    struct Zapis **zapisi;
    struct Derevo *left, *right;
};

void kopirovat(char *a, const char *b);
int sravnit(const char *a, const char *b);
struct Derevo *a2(Group *g, Element *a, int L, int R);
struct Derevo *postroit_a2(struct Zapis **zapisi, int n);
void pokazat_derevo(struct Derevo *root);
int sohranit_svg(struct Derevo *root, const char *filename);
void poisk_derevo(struct Derevo *root, const char *key);
void ochistit_derevo(struct Derevo *root);

#endif
