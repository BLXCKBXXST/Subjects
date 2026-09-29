#include <stdio.h>
#include <stdlib.h>
#include "zapis.h"
#include "tablica.h"

#define N 4000
#define NA_STR 20

void hoar(struct Zapis **uk, int left, int right);
void poisk_po_godu(struct Zapis **uk, int n, int god);

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

        if (fgets(otvet, sizeof(otvet), stdin) == NULL)
            break;

        if (otvet[0] == 'q' || otvet[0] == 'Q')
            break;
    }
}

int main(void) {
    struct Zapis *baza;
    struct Zapis **uk;
    int n, vibor = -1;
    int otsortirovano = 0;

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
        printf("3 - двоичный поиск по году\n");
        printf("0 - выход\n");
        printf("> ");

        if (scanf("%d", &vibor) != 1)
            break;

        getchar();

        if (vibor == 1) {
            pokazat(uk, n);
        } else if (vibor == 2) {
            hoar(uk, 0, n - 1);
            otsortirovano = 1;
            printf("Сортировка завершена.\n");
            pokazat(uk, n);
        } else if (vibor == 3) {
            int god;

            if (!otsortirovano) {
                printf("Сначала выполните сортировку.\n");
                continue;
            }

            printf("Введите год: ");

            if (scanf("%d", &god) != 1)
                break;

            getchar();
            poisk_po_godu(uk, n, god);
        }
    }

    free(uk);
    free(baza);
    return 0;
}
