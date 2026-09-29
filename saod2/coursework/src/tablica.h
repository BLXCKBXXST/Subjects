#ifndef TABLICA_H
#define TABLICA_H

#include <stdio.h>
#include "zapis.h"
#include "cp866.h"

#define W_NUM 4
#define W_AVT 12
#define W_ZAG 32
#define W_IZD 16
#define W_GOD 4
#define W_STR 4

static int shirina(const char *s) {
    int w = 0;
    while (*s) {
        if ((*s & 0xC0) != 0x80) w++;
        s++;
    }
    return w;
}

static void yacheyka(const char *s, int w) {
    int d = w - shirina(s);
    int i;
    printf("│ %s", s);
    for (i = 0; i < d + 1; i++) printf(" ");
}

static void liniya(const char *l, const char *m, const char *r) {
    int w[6] = {W_NUM, W_AVT, W_ZAG, W_IZD, W_GOD, W_STR};
    int i, j;
    printf("%s", l);
    for (i = 0; i < 6; i++) {
        for (j = 0; j < w[i] + 2; j++) printf("─");
        printf("%s", i < 5 ? m : r);
    }
    printf("\n");
}

static void tab_shapka(void) {
    liniya("┌", "┬", "┐");
    yacheyka("N", W_NUM);
    yacheyka("Автор", W_AVT);
    yacheyka("Заглавие", W_ZAG);
    yacheyka("Издательство", W_IZD);
    yacheyka("Год", W_GOD);
    yacheyka("Стр.", W_STR);
    printf("│\n");
    liniya("├", "┼", "┤");
}

static void tab_stroka(int nomer, struct Zapis *z) {
    char avt[32], zag[80], izd[40], num[12], god[12], str[12];
    cp866_to_utf8(z->avtor, 12, avt);
    cp866_to_utf8(z->zagl, 32, zag);
    cp866_to_utf8(z->izd, 16, izd);
    sprintf(num, "%d", nomer);
    sprintf(god, "%d", z->god);
    sprintf(str, "%d", z->str);
    yacheyka(num, W_NUM);
    yacheyka(avt, W_AVT);
    yacheyka(zag, W_ZAG);
    yacheyka(izd, W_IZD);
    yacheyka(god, W_GOD);
    yacheyka(str, W_STR);
    printf("│\n");
}

static void tab_niz(void) {
    liniya("└", "┴", "┘");
}

#endif
