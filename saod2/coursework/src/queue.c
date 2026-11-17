#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"
#include "queue.h"

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
