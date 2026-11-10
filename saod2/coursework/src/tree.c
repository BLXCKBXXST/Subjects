#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tablica.h"

static void pechat(struct Derevo *p, int level) {
    int i;
    if (p == NULL) return;
    pechat(p->right, level + 1);
    for (i = 0; i < level; i++) printf("    ");
    printf("%s (вес %d)\n", p->key, p->weight);
    pechat(p->left, level + 1);
}

void pokazat_derevo(struct Derevo *root) {
    pechat(root, 0);
}

void poisk_derevo(struct Derevo *root, const char *key) {
    while (root != NULL) {
        int c = sravnit(key, root->key);
        if (c == 0) {
            tab_shapka();
            for (int i = 0; i < root->weight; i++)
                tab_stroka(i + 1, root->zapisi[i]);
            tab_niz();
            printf("Найдено записей: %d\n", root->weight);
            return;
        }
        if (c < 0) root = root->left;
        else root = root->right;
    }
    printf("Записей с таким заглавием нет.\n");
}

void ochistit_derevo(struct Derevo *root) {
    if (root == NULL) return;
    ochistit_derevo(root->left);
    ochistit_derevo(root->right);
    free(root->zapisi);
    free(root);
}
