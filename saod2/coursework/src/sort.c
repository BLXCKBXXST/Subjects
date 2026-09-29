#include "zapis.h"

int sravni_pole(const char *a, const char *b, int dlina) {
    int i;

    for (i = 0; i < dlina; i++) {
        if ((unsigned char)a[i] < (unsigned char)b[i])
            return -1;

        if ((unsigned char)a[i] > (unsigned char)b[i])
            return 1;
    }

    return 0;
}

int sravni(struct Zapis *a, struct Zapis *b) {
    if (a->god < b->god)
        return -1;

    if (a->god > b->god)
        return 1;

    return sravni_pole(a->avtor, b->avtor, 12);
}

void hoar(struct Zapis **uk, int left, int right) {
    int i = left;
    int j = right;
    struct Zapis *opora = uk[(left + right) / 2];
    struct Zapis *tmp;

    while (i <= j) {
        while (sravni(uk[i], opora) < 0)
            i++;

        while (sravni(uk[j], opora) > 0)
            j--;

        if (i <= j) {
            tmp = uk[i];
            uk[i] = uk[j];
            uk[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        hoar(uk, left, j);

    if (i < right)
        hoar(uk, i, right);
}
