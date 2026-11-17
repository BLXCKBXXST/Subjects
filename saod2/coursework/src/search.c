#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"

int bin_poisk(struct Zapis **uk, int n, int god) {
    if (n <= 0)
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

int putqueue(struct Ochered **first, struct Ochered **last, struct Zapis *zapis) {
    struct Ochered *p = malloc(sizeof(*p));
    if (p == NULL) return 0;
    p->zapis = zapis;
    p->next = NULL;
    if (*first == NULL) *first = p;
    else (*last)->next = p;
    *last = p;
    return 1;
}

struct Zapis *getqueue(struct Ochered **first, struct Ochered **last) {
    if (*first == NULL) return NULL;
    struct Ochered *p = *first;
    struct Zapis *zapis = p->zapis;
    *first = p->next;
    if (*first == NULL) *last = NULL;
    free(p);
    return zapis;
}

void ochistit_ochered(struct Ochered *first) {
    struct Ochered *last = NULL;
    while (getqueue(&first, &last) != NULL) {}
}

struct Ochered *sozdat_ochered(struct Zapis **uk, int n, int god) {
    int i = bin_poisk(uk, n, god);
    struct Ochered *first = NULL, *last = NULL;
    if (i == -1) return NULL;
    while (i < n && uk[i]->god == god) {
        if (!putqueue(&first, &last, uk[i])) {
            ochistit_ochered(first);
            fprintf(stderr, "Не хватает памяти для очереди.\n");
            exit(EXIT_FAILURE);
        }
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

int poisk_po_godu(struct Zapis **uk, int n, int god) {
    if (!obnovit_prosmotr(NULL, 0)) return 0;
    struct Ochered *ochered = sozdat_ochered(uk, n, god);
    struct Ochered *p;
    struct Zapis **massiv;
    struct Derevo *root;
    char key[100];
    int count = 0, i = 0;

    pokazat_ochered(ochered);

    for (p = ochered; p != NULL; p = p->next) count++;
    if (count == 0) return 1;

    massiv = malloc(count * sizeof(struct Zapis *));
    if (massiv == NULL) {
        ochistit_ochered(ochered);
        fprintf(stderr, "Не хватает памяти для записей дерева.\n");
        return 0;
    }
    for (p = ochered; p != NULL; p = p->next) massiv[i++] = p->zapis;

    root = postroit_a2(massiv, count);
    free(massiv);

    if (root != NULL) {
        printf("\nОбход дерева А2 слева направо:\n");
        pokazat_derevo(root);
        if (!obnovit_prosmotr(root, 1)) {
            ochistit_derevo(root);
            ochistit_ochered(ochered);
            return 0;
        }

        while (1) {
            int status = vvod_stroki("\nВведите заглавие книги (Enter - назад): ",
                                     key, sizeof(key));
            if (status == 0) break;
            if (status < 0) continue;
            if (key[0] == '\0') break;
            poisk_derevo(root, key);
        }
    } else {
        fprintf(stderr, "Не удалось построить дерево А2.\n");
        ochistit_ochered(ochered);
        return 0;
    }

    ochistit_derevo(root);
    ochistit_ochered(ochered);
    return 1;
}
