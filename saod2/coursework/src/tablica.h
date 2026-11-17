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

static void ubrat_probely(char *s) {
    int i = 0;

    while (s[i] != '\0')
        i++;

    while (i > 0 && s[i - 1] == ' ') {
        s[i - 1] = '\0';
        i--;
    }
}

static void yacheyka(const char *s, int w) {
    int d = w - shirina(s);
    int left = d / 2;
    int right = d - left;
    int i;

    printf("│ ");
    for (i = 0; i < left; i++) printf(" ");
    printf("%s", s);
    for (i = 0; i < right + 1; i++) printf(" ");
}

static void yacheyka_sleva(const char *s, int w) {
    int d = w - shirina(s);
    printf("│ %s", s);
    for (int i = 0; i < d + 1; i++) printf(" ");
}

static void liniya_ves(const char *l, const char *m, const char *r, int s_vesom) {
    int w[7] = {W_NUM, W_AVT, W_ZAG, W_IZD, W_GOD, W_STR, 4};
    int count = 6 + s_vesom;
    int i, j;
    printf("%s", l);
    for (i = 0; i < count; i++) {
        for (j = 0; j < w[i] + 2; j++) printf("─");
        printf("%s", i < count - 1 ? m : r);
    }
    printf("\n");
}

static inline void tab_shapka_ves(int s_vesom) {
    liniya_ves("┌", "┬", "┐", s_vesom);
    yacheyka("N", W_NUM);
    yacheyka("Автор", W_AVT);
    yacheyka("Заглавие", W_ZAG);
    yacheyka("Издательство", W_IZD);
    yacheyka("Год", W_GOD);
    yacheyka("Стр.", W_STR);
    if (s_vesom) yacheyka("Вес", 4);
    printf("│\n");
    liniya_ves("├", "┼", "┤", s_vesom);
}

static inline void tab_stroka_ves(int nomer, struct Zapis *z, int ves) {
    char avt[32], zag[80], izd[40], num[12], god[12], str[12];

    cp866_to_utf8(z->avtor, 12, avt);
    cp866_to_utf8(z->zagl, 32, zag);
    cp866_to_utf8(z->izd, 16, izd);

    ubrat_probely(avt);
    ubrat_probely(zag);
    ubrat_probely(izd);

    sprintf(num, "%d", nomer);
    sprintf(god, "%d", z->god);
    sprintf(str, "%d", z->str);

    yacheyka(num, W_NUM);
    yacheyka_sleva(avt, W_AVT);
    yacheyka_sleva(zag, W_ZAG);
    yacheyka_sleva(izd, W_IZD);
    yacheyka(god, W_GOD);
    yacheyka(str, W_STR);
    if (ves > 0) {
        char weight[12];
        sprintf(weight, "%d", ves);
        yacheyka(weight, 4);
    }
    printf("│\n");
}

static inline void tab_niz_ves(int s_vesom) {
    liniya_ves("└", "┴", "┘", s_vesom);
}

static void tab_shapka(void) {
    tab_shapka_ves(0);
}

static void tab_stroka(int nomer, struct Zapis *z) {
    tab_stroka_ves(nomer, z, 0);
}

static void tab_niz(void) {
    tab_niz_ves(0);
}

#endif
