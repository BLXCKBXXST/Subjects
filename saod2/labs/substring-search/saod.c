#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define D 256
#define W1 10
#define WC 14

void ramka(const char *l, const char *m, const char *r, int cols) {
    printf("%s", l);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < (i == 0 ? W1 : WC); j++) printf("%s", "\u2500");
        printf("%s", i < cols - 1 ? m : r);
    }
    printf("\n");
}

int shrina(const char *s) {
    int w = 0;
    while (*s) {
        if ((*s & 0xC0) != 0x80) w++;
        s++;
    }
    return w;
}

void yacheyka(const char *s) {
    printf("\u2502%s", s);
    int d = WC - shrina(s);
    for (int i = 0; i < d; i++) printf(" ");
}

void yacheyka_ch(long v) {
    char buf[32];
    sprintf(buf, "%ld", v);
    yacheyka(buf);
}

void pervaya_s(const char *s) {
    printf("\u2502%s", s);
    int d = W1 - shrina(s);
    for (int i = 0; i < d; i++) printf(" ");
}

void pervaya_ch(long v) {
    char buf[32];
    sprintf(buf, "%ld", v);
    pervaya_s(buf);
}

long naivny(char *T, char *W) {
    long n = strlen(T);
    long m = strlen(W);
    long cmp = 0;

    for (long i = 0; i <= n - m; i++) {
        long j;
        for (j = 0; j < m; j++) {
            cmp++;
            if (T[i + j] != W[j]) break;
        }
    }
    return cmp;
}

long rabin_karp(char *T, char *W, long Q, long *hcmp, long *false_pos) {
    long n = strlen(T);
    long m = strlen(W);
    long cmp = 0;
    long hW = 0;
    long hT = 0;
    long dm = 1;

    *hcmp = 0;
    *false_pos = 0;

    for (long i = 0; i < m - 1; i++)
        dm = (dm * D) % Q;

    for (long i = 0; i < m; i++) {
        hW = (hW * D + (unsigned char)W[i]) % Q;
        hT = (hT * D + (unsigned char)T[i]) % Q;
    }

    for (long i = 0; i <= n - m; i++) {
        if (hT == hW) {
            (*hcmp)++;
            long j;
            for (j = 0; j < m; j++) {
                cmp++;
                if (T[i + j] != W[j]) break;
            }
            if (j < m) (*false_pos)++;
        }
        if (i < n - m) {
            hT = (D * (hT - (unsigned char)T[i] * dm) + (unsigned char)T[i + m]) % Q;
            if (hT < 0) hT += Q;
        }
    }
    return cmp;
}

int main(void) {
    char filename[100];
    char W[5][100];
    int k;
    long Qs[4] = {13, 101, 1009, 1000003};

    printf("Имя файла с текстом: ");
    if (scanf("%99s", filename) != 1) {
        fprintf(stderr, "Не удалось прочитать имя файла\n");
        return 1;
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Не удалось открыть файл\n");
        return 1;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fprintf(stderr, "Не удалось определить размер файла\n");
        fclose(f);
        return 1;
    }
    long size = ftell(f);
    if (size < 0 || fseek(f, 0, SEEK_SET) != 0) {
        fprintf(stderr, "Не удалось подготовить файл к чтению\n");
        fclose(f);
        return 1;
    }
    char *T = malloc((size_t)size + 1);
    if (T == NULL) {
        fprintf(stderr, "Не хватает памяти\n");
        fclose(f);
        return 1;
    }
    if (fread(T, 1, (size_t)size, f) != (size_t)size || ferror(f)) {
        fprintf(stderr, "Не удалось прочитать файл полностью\n");
        free(T);
        fclose(f);
        return 1;
    }
    T[size] = '\0';
    fclose(f);

    printf("Размер файла: %ld байт (%.2f МБ)\n", size, size / 1048576.0);

    printf("Сколько подстрок (1-5): ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Не удалось прочитать количество подстрок\n");
        free(T);
        return 1;
    }
    if (k < 1 || k > 5) k = 1;
    for (int i = 0; i < k; i++) {
        printf("Подстрока %d: ", i + 1);
        if (scanf("%99s", W[i]) != 1) {
            fprintf(stderr, "Не удалось прочитать подстроку\n");
            free(T);
            return 1;
        }
    }

    printf("\nТаблица 1. Посимвольные сравнения Рабина-Карпа\n");
    ramka("\u250c", "\u252c", "\u2510", k + 1);
    pervaya_s("Q/подстр.");
    for (int i = 0; i < k; i++) yacheyka(W[i]);
    printf("%s\n", "\u2502");
    ramka("\u251c", "\u253c", "\u2524", k + 1);
    for (int q = 0; q < 4; q++) {
        pervaya_ch(Qs[q]);
        for (int i = 0; i < k; i++) {
            long hcmp, fp;
            yacheyka_ch(rabin_karp(T, W[i], Qs[q], &hcmp, &fp));
        }
        printf("%s\n", "\u2502");
    }
    ramka("\u251c", "\u253c", "\u2524", k + 1);
    pervaya_s("наивный");
    for (int i = 0; i < k; i++) yacheyka_ch(naivny(T, W[i]));
    printf("%s\n", "\u2502");
    ramka("\u2514", "\u2534", "\u2518", k + 1);

    for (int i = 0; i < k; i++) {
        printf("\nТаблица %d. Подстрока \"%s\"\n", i + 2, W[i]);
        ramka("\u250c", "\u252c", "\u2510", 4);
        pervaya_s("Q");
        yacheyka("сравн. хешей");
        yacheyka("посимв. сравн.");
        yacheyka("коллизии");
        printf("%s\n", "\u2502");
        ramka("\u251c", "\u253c", "\u2524", 4);
        for (int q = 0; q < 4; q++) {
            long hcmp, fp;
            long cmp = rabin_karp(T, W[i], Qs[q], &hcmp, &fp);
            pervaya_ch(Qs[q]);
            yacheyka_ch(hcmp);
            yacheyka_ch(cmp);
            yacheyka_ch(fp);
            printf("%s\n", "\u2502");
        }
        ramka("\u2514", "\u2534", "\u2518", 4);
    }

    free(T);
    return 0;
}
