#ifndef COURSEWORK_H
#define COURSEWORK_H

#include <stddef.h>
#include <stdio.h>

struct Zapis {
    char avtor[12];
    char zagl[32];
    char izd[16];
    short god;
    short str;
};

_Static_assert(sizeof(struct Zapis) == 64, "Размер записи базы должен быть 64 байта");

typedef struct {
    struct Zapis *zapis;
    char key[65];
} Element;

typedef struct {
    char key[65];
    int start, weight;
} Group;

struct Spisok {
    struct Zapis *zapis;
    struct Spisok *next;
};

struct Derevo {
    char key[65];
    int weight;
    struct Spisok *head;
    struct Derevo *left, *right;
};

struct RecordVertex {
    char key[65];
    int weight;
    struct Zapis *zapis;
    struct RecordVertex *left, *right;
};

struct RecordVertex *postroit_zapisi_a2(struct Derevo *root);
void ochistit_zapisi_a2(struct RecordVertex *root);

void kopirovat(char *a, const char *b);
int sravnit(const char *a, const char *b);
void Add(struct Derevo **p, Group D, Element *a);
void A2(struct Derevo **Root, Group V[], Element *a, int L, int R);
struct Derevo *postroit_a2(struct Zapis **zapisi, int n);
void pokazat_derevo(struct Derevo *root);
int sohranit_svg(struct Derevo *root, const char *filename);
int sohranit_zapisi_svg(struct Derevo *root, const char *filename);
struct Derevo *nayti_v_dereve(struct Derevo *root, const char *key);
void poisk_derevo(struct Derevo *root, const char *key);
void ochistit_derevo(struct Derevo *root);

struct Ochered {
    struct Zapis *zapis;
    struct Ochered *next;
};
int putqueue(struct Ochered **first, struct Ochered **last, struct Zapis *zapis);
struct Zapis *getqueue(struct Ochered **first, struct Ochered **last);
struct Ochered *sozdat_ochered(struct Zapis **uk, int n, int god);
void ochistit_ochered(struct Ochered *first);

struct Derevo;
int obnovit_prosmotr(struct Derevo *root, int otkrit);

#define N 4000
#define BASE_FILE "coursework/testBase1.dat"
#define SVG_FILE "coursework/src/a2.svg"
#define PREVIEW_FILE "coursework/src/a2.html"
#define REVISION_FILE "coursework/src/a2-state.js"
void hoar(struct Zapis **uk, int left, int right);
int sravni(struct Zapis *a, struct Zapis *b);
int bin_poisk(struct Zapis **uk, int n, int god);
int poisk_po_godu(struct Zapis **uk, int n, int god);
int vvod_stroki(const char *prompt, char *s, size_t capacity);
int vvod_chisla(const char *prompt, int *value);

static inline void cp866_to_utf8(const char *src, int dlina, char *dst) {
    int i;
    unsigned char c;

    for (i = 0; i < dlina && src[i] != '\0'; i++) {
        c = (unsigned char)src[i];

        if (c >= 0x80 && c <= 0x9F) {
            *dst++ = (char)0xD0;
            *dst++ = (char)(c - 0x80 + 0x90);
        } else if (c >= 0xA0 && c <= 0xAF) {
            *dst++ = (char)0xD0;
            *dst++ = (char)(c - 0xA0 + 0xB0);
        } else if (c >= 0xE0 && c <= 0xEF) {
            *dst++ = (char)0xD1;
            *dst++ = (char)(c - 0xE0 + 0x80);
        } else if (c == 0xF0) {
            *dst++ = (char)0xD0;
            *dst++ = (char)0x81;
        } else if (c == 0xF1) {
            *dst++ = (char)0xD1;
            *dst++ = (char)0x91;
        } else {
            *dst++ = (char)c;
        }
    }

    *dst = 0;
}

#define W_NUM 4
#define W_AVT 12
#define W_ZAG 32
#define W_IZD 16
#define W_GOD 4
#define W_STR 4

static inline int shirina(const char *s) {
    int w = 0;
    while (*s) {
        if ((*s & 0xC0) != 0x80) w++;
        s++;
    }
    return w;
}

static inline void ubrat_probely(char *s) {
    int i = 0;

    while (s[i] != '\0')
        i++;

    while (i > 0 && s[i - 1] == ' ') {
        s[i - 1] = '\0';
        i--;
    }
}

static inline void yacheyka(const char *s, int w) {
    int d = w - shirina(s);
    int left = d / 2;
    int right = d - left;
    int i;

    printf("│ ");
    for (i = 0; i < left; i++) printf(" ");
    printf("%s", s);
    for (i = 0; i < right + 1; i++) printf(" ");
}

static inline void yacheyka_sleva(const char *s, int w) {
    int d = w - shirina(s);
    printf("│ %s", s);
    for (int i = 0; i < d + 1; i++) printf(" ");
}

static inline void liniya_ves(const char *l, const char *m, const char *r, int s_vesom) {
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

static inline void tab_shapka(void) {
    tab_shapka_ves(0);
}

static inline void tab_stroka(int nomer, struct Zapis *z) {
    tab_stroka_ves(nomer, z, 0);
}

static inline void tab_niz(void) {
    tab_niz_ves(0);
}

#endif
