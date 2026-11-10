#include <stdio.h>
#include <stdlib.h>
#include "zapis.h"
#include "tablica.h"
#include "tree.h"

struct Ochered {
    struct Zapis *zapis;
    struct Ochered *next;
};

int bin_poisk(struct Zapis **uk, int n, int god) {
    if (n == 0)
        return -1;

    int L = 0;
    int R = n - 1;

    while (L < R) {
        int m = (L + R) / 2;

        if (uk[m]->god < god)
            L = m + 1;
        else
            R = m;
    }

    if (uk[L]->god == god)
        return L;

    return -1;
}

struct Ochered *sozdat_ochered(struct Zapis **uk, int n, int god) {
    int i = bin_poisk(uk, n, god);
    struct Ochered *first = NULL;
    struct Ochered *last = NULL;

    if (i == -1)
        return NULL;

    while (i < n && uk[i]->god == god) {
        struct Ochered *noviy = malloc(sizeof(struct Ochered));

        if (noviy == NULL)
            break;

        noviy->zapis = uk[i];
        noviy->next = NULL;

        if (first == NULL)
            first = noviy;
        else
            last->next = noviy;

        last = noviy;
        i++;
    }

    return first;
}

void pokazat_ochered(struct Ochered *first) {
    int i = 1;
    struct Ochered *p = first;

    if (p == NULL) {
        printf("Записей с таким годом нет.\n");
        return;
    }

    tab_shapka();

    while (p != NULL) {
        tab_stroka(i, p->zapis);
        p = p->next;
        i++;
    }

    tab_niz();
    printf("Найдено записей: %d\n", i - 1);
}

void ochistit_ochered(struct Ochered *first) {
    while (first != NULL) {
        struct Ochered *p = first;
        first = first->next;
        free(p);
    }
}

void poisk_po_godu(struct Zapis **uk, int n, int god) {
    struct Ochered *ochered = sozdat_ochered(uk, n, god);
    struct Ochered *p;
    struct Zapis **massiv;
    struct Derevo *root;
    char key[100];
    int count = 0, i = 0;

    pokazat_ochered(ochered);

    for (p = ochered; p != NULL; p = p->next) count++;
    if (count == 0) return;

    massiv = malloc(count * sizeof(struct Zapis *));
    if (massiv == NULL) {
        ochistit_ochered(ochered);
        return;
    }
    for (p = ochered; p != NULL; p = p->next) massiv[i++] = p->zapis;

    root = postroit_a2(massiv, count);
    free(massiv);

    if (root != NULL) {
        printf("\nДерево А2 по заглавиям (ФИО героев):\n");
        pokazat_derevo(root);
        if (sohranit_svg(root, "a2.svg")) {
            printf("SVG сохранён: coursework/src/a2.svg\n");
#ifdef _WIN32
            system("start \"\" \"a2.svg\"");
#elif defined(__APPLE__)
            system("open a2.svg");
#else
            system("xdg-open a2.svg >/dev/null 2>&1 &");
#endif
        }

        while (1) {
            printf("\nВведите ФИО героя для поиска (Enter - назад): ");
            if (fgets(key, sizeof(key), stdin) == NULL) break;
            i = 0;
            while (key[i] != '\0' && key[i] != '\n') i++;
            key[i] = '\0';
            if (i == 0) break;
            poisk_derevo(root, key);
        }
    }

    ochistit_derevo(root);
    ochistit_ochered(ochered);
}
