#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "coursework.h"
#include "../../labs/lab-viewer.h"

int vvod_stroki(const char *prompt, char *s, size_t capacity) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(s, (int)capacity, stdin) == NULL) return 0;
    size_t n = strlen(s);
    if (n && s[n - 1] == '\n') s[--n] = '\0';
    else {
        int ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Слишком длинная строка. Повторите ввод.\n");
            return -1;
        }
    }
    if (n && s[n - 1] == '\r') s[n - 1] = '\0';
    return 1;
}

int vvod_chisla(const char *prompt, int *value) {
    char s[80], *end;
    for (;;) {
        int status = vvod_stroki(prompt, s, sizeof(s));
        if (status == 0) return 0;
        if (status < 0) continue;
        errno = 0;
        long number = strtol(s, &end, 10);
        int empty = end == s;
        while (isspace((unsigned char)*end)) end++;
        if (!empty && *end == '\0' && errno != ERANGE &&
            number >= INT_MIN && number <= INT_MAX) {
            *value = (int)number;
            return 1;
        }
        printf("Введите целое число.\n");
    }
}

#define NA_STR 20

int zagruzit(struct Zapis *baza, struct Zapis **uk) {
    FILE *f = fopen(BASE_FILE, "rb");
    if (f == NULL) { perror(BASE_FILE); return 0; }
    size_t n = fread(baza, sizeof(*baza), N, f);
    int extra = fgetc(f);
    int ok = !ferror(f) && n == N && extra == EOF;
    if (fclose(f) != 0) ok = 0;
    if (!ok) {
        fprintf(stderr, "База должна содержать ровно %d полных записей.\n", N);
        return 0;
    }
    for (int i = 0; i < (int)n; i++) uk[i] = &baza[i];
    return (int)n;
}

void pokazat(struct Zapis **uk, int n, int vse) {
    int i = 0;
    char otvet[20];
    while (i < n) {
        tab_shapka();
        for (int k = 0; i < n && (vse || k < NA_STR); k++, i++)
            tab_stroka(i + 1, uk[i]);
        tab_niz();
        if (i >= n) { printf("Конец базы.\n"); break; }
        printf("Показано %d из %d. ", i, n);
        int status = vvod_stroki("Enter - дальше, q - выход: ", otvet, sizeof(otvet));
        if (status == 0 || (status > 0 && (otvet[0] == 'q' || otvet[0] == 'Q'))) break;
    }
}

int main(int argc, char **argv) {
    (void)argc;
    if (!initLabPaths(argv[0])) return 1;
    struct Zapis *baza = malloc(N * sizeof(*baza));
    struct Zapis **uk = malloc(N * sizeof(*uk));
    if (baza == NULL || uk == NULL) {
        fprintf(stderr, "Не хватает памяти.\n");
        free(baza); free(uk);
        return 1;
    }
    int n = zagruzit(baza, uk);
    if (n == 0 || !obnovit_prosmotr(NULL, 0)) {
        free(uk); free(baza);
        return 1;
    }
    int vibor, otsortirovano = 0, result = 0;
    printf("Загружено записей: %d\n", n);
    for (;;) {
        printf("\n1 - показать базу по страницам\n"
               "2 - сортировка методом Хоара\n"
               "3 - поиск по году, дерево А2 и поиск по заглавию\n"
               "4 - показать всю базу\n0 - выход\n");
        if (!vvod_chisla("> ", &vibor) || vibor == 0) break;
        if (vibor == 1 || vibor == 4) {
            pokazat(uk, n, vibor == 4);
        } else if (vibor == 2) {
            hoar(uk, 0, n - 1);
            otsortirovano = 1;
            printf("Сортировка завершена.\n");
            pokazat(uk, n, 0);
        } else if (vibor == 3) {
            int god;
            if (!otsortirovano) { printf("Сначала выполните сортировку.\n"); continue; }
            if (!vvod_chisla("Введите год: ", &god)) break;
            if (!poisk_po_godu(uk, n, god)) { result = 1; break; }
        } else {
            printf("Нет такого пункта меню.\n");
        }
    }
    free(uk); free(baza);
    return result;
}
