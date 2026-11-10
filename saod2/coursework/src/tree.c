#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tablica.h"
#include "cp866.h"

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

static void kopirovat(char *a, const char *b) {
    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

static int sravnit(const char *a, const char *b) {
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

static struct Derevo *a2(Group *g, Element *a, int L, int R) {
    if (L > R) return NULL;

    int total = 0, sum = 0, i, j;
    for (i = L; i <= R; i++) total += g[i].weight;

    for (i = L; i < R; i++) {
        if (2 * (sum + g[i].weight) >= total) break;
        sum += g[i].weight;
    }

    struct Derevo *p = malloc(sizeof(struct Derevo));
    kopirovat(p->key, g[i].key);
    p->weight = g[i].weight;
    p->zapisi = malloc(p->weight * sizeof(struct Zapis *));
    for (j = 0; j < p->weight; j++)
        p->zapisi[j] = a[g[i].start + j].zapis;

    p->left = a2(g, a, L, i - 1);
    p->right = a2(g, a, i + 1, R);
    return p;
}

struct Derevo *postroit_a2(struct Zapis **zapisi, int n) {
    if (n == 0) return NULL;

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

    struct Derevo *root = a2(g, a, 0, k - 1);
    free(g);
    free(a);
    return root;
}

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
