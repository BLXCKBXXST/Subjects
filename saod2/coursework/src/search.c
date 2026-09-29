#include <stdio.h>
#include <stdlib.h>
#include "zapis.h"
#include "tablica.h"

struct Ochered {
    struct Zapis *zapis;
    struct Ochered *next;
};

int bin_poisk(struct Zapis **uk, int n, int god) {
    int left = 0;
    int right = n - 1;
    int found = -1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (uk[mid]->god < god) {
            left = mid + 1;
        } else if (uk[mid]->god > god) {
            right = mid - 1;
        } else {
            found = mid;
            right = mid - 1;
        }
    }

    return found;
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

    pokazat_ochered(ochered);
    ochistit_ochered(ochered);
}
