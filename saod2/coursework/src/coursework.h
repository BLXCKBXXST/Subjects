#ifndef COURSEWORK_H
#define COURSEWORK_H
#include <stddef.h>
#include "zapis.h"
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
#endif
