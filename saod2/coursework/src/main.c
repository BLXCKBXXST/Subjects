#include <stdio.h>
#include <stdlib.h>
#include "zapis.h"
#include "tablica.h"

#define N 4000
#define NA_STR 20

int zagruzit(struct Zapis *baza, struct Zapis **uk) {
    FILE *f = fopen("../testBase1.dat", "rb");
    int n, i;
    if (f == NULL) {
        printf("Не могу открыть файл ../testBase1.dat\n");
        return 0;
    }
    n = fread(baza, sizeof(struct Zapis), N, f);
    fclose(f);
    for (i = 0; i < n; i++)
        uk[i] = &baza[i];
    return n;
}

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
    if (a->god < b->god) return -1;
    if (a->god > b->god) return 1;
    return sravni_pole(a->avtor, b->avtor, 12);
}

void hoar(struct Zapis **uk, int left, int right) {
    int i = left;
    int j = right;
    struct Zapis *opora = uk[(left + right) / 2];
    struct Zapis *tmp;
    while (i <= j) {
        while (sravni(uk[i], opora) < 0) i++;
        while (sravni(uk[j], opora) > 0) j--;
        if (i <= j) {
            tmp = uk[i];
            uk[i] = uk[j];
            uk[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j) hoar(uk, left, j);
    if (i < right) hoar(uk, i, right);
}

void pokazat(struct Zapis **uk, int n) {
    int i = 0, k;
    char otvet[10];
    while (i < n) {
        tab_shapka();
        for (k = 0; k < NA_STR && i < n; k++, i++)
            tab_stroka(i + 1, uk[i]);
        tab_niz();
        if (i >= n) {
            printf("Конец базы.\n");
            break;
        }
        printf("Показано %d из %d. Enter - дальше, q - выход: ", i, n);
        if (fgets(otvet, sizeof(otvet), stdin) == NULL) break;
        if (otvet[0] == 'q' || otvet[0] == 'Q') break;
    }
}

int main(void) {
    struct Zapis *baza;
    struct Zapis **uk;
    int n, vibor = -1;

    baza = malloc(N * sizeof(struct Zapis));
    uk = malloc(N * sizeof(struct Zapis *));
    if (baza == NULL || uk == NULL) {
        printf("Не хватает памяти\n");
        free(baza);
        free(uk);
        return 1;
    }

    n = zagruzit(baza, uk);
    if (n == 0) {
        free(uk);
        free(baza);
        return 1;
    }
    printf("Загружено записей: %d\n", n);

    while (vibor != 0) {
        printf("\n1 - показать базу\n");
        printf("2 - метод Хоара\n");
        printf("0 - выход\n");
        printf("> ");
        if (scanf("%d", &vibor) != 1) break;
        getchar();
        if (vibor == 1) {
            pokazat(uk, n);
        } else if (vibor == 2) {
            hoar(uk, 0, n - 1);
            printf("Сортировка завершена.\n");
            pokazat(uk, n);
        }
    }

    free(uk);
    free(baza);
    return 0;
}
