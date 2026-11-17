#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tablica.h"
#include "cp866.h"

void kopirovat(char *a, const char *b) {
    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

int sravnit(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if ((unsigned char)a[i] != (unsigned char)b[i])
            return (unsigned char)a[i] < (unsigned char)b[i] ? -1 : 1;
        i++;
    }
    if (a[i] == b[i]) return 0;
    return a[i] == '\0' ? -1 : 1;
}

static void zaglavie(struct Zapis *z, char *key) {
    int i = 0;
    cp866_to_utf8(z->zagl, 32, key);
    while (key[i] != '\0') i++;
    while (i > 0 && key[i - 1] == ' ') i--;
    key[i] = '\0';
}

static void hoar_zaglavie(Element *a, int L, int R) {
    if (L >= R) return;
    int i = L, j = R;
    char opora[65];
    Element temp;
    kopirovat(opora, a[(L + R) / 2].key);

    while (i <= j) {
        while (sravnit(a[i].key, opora) < 0) i++;
        while (sravnit(a[j].key, opora) > 0) j--;
        if (i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    if (L < j) hoar_zaglavie(a, L, j);
    if (i < R) hoar_zaglavie(a, i, R);
}

void Add(struct Derevo **p, Group D, Element *a) {
    if (*p == NULL) {
        *p = malloc(sizeof(struct Derevo));
        if (*p == NULL) { perror("А2"); exit(EXIT_FAILURE); }
        kopirovat((*p)->key, D.key);
        (*p)->weight = D.weight;
        (*p)->zapisi = malloc(D.weight * sizeof(struct Zapis *));
        if ((*p)->zapisi == NULL) {
            perror("Записи А2");
            free(*p);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < D.weight; j++)
            (*p)->zapisi[j] = a[D.start + j].zapis;
        (*p)->left = (*p)->right = NULL;
    } else if (sravnit(D.key, (*p)->key) < 0) {
        Add(&(*p)->left, D, a);
    } else {
        Add(&(*p)->right, D, a);
    }
}

struct Derevo *postroit_a2(struct Zapis **zapisi, int n) {
    if (n <= 0) return NULL;

    Element *a = malloc(n * sizeof(Element));
    Group *g = malloc(n * sizeof(Group));
    int i, k = 0;
    if (a == NULL || g == NULL) {
        free(a);
        free(g);
        return NULL;
    }

    for (i = 0; i < n; i++) {
        a[i].zapis = zapisi[i];
        zaglavie(zapisi[i], a[i].key);
    }
    hoar_zaglavie(a, 0, n - 1);

    for (i = 0; i < n; i++) {
        if (k == 0 || sravnit(a[i].key, g[k - 1].key) != 0) {
            kopirovat(g[k].key, a[i].key);
            g[k].start = i;
            g[k].weight = 1;
            k++;
        } else {
            g[k - 1].weight++;
        }
    }

    struct Derevo *root = NULL;
    A2(&root, g, a, 0, k - 1);
    free(g);
    free(a);
    return root;
}

static void obhod_tablicey(struct Derevo *root, int *nomer) {
    if (root == NULL) return;
    obhod_tablicey(root->left, nomer);
    for (int i = 0; i < root->weight; i++)
        tab_stroka_ves((*nomer)++, root->zapisi[i], root->weight);
    obhod_tablicey(root->right, nomer);
}

void pokazat_derevo(struct Derevo *root) {
    int nomer = 1;
    tab_shapka_ves(1);
    obhod_tablicey(root, &nomer);
    tab_niz_ves(1);
}

void poisk_derevo(struct Derevo *root, const char *key) {
    struct Derevo *found = nayti_v_dereve(root, key);
    if (found == NULL) {
        printf("Записей с таким заглавием нет.\n");
        return;
    }
    tab_shapka();
    for (int i = 0; i < found->weight; i++) tab_stroka(i + 1, found->zapisi[i]);
    tab_niz();
    printf("Найдено записей: %d\n", found->weight);
}

void ochistit_derevo(struct Derevo *root) {
    if (root == NULL) return;
    ochistit_derevo(root->left);
    ochistit_derevo(root->right);
    free(root->zapisi);
    free(root);
}
