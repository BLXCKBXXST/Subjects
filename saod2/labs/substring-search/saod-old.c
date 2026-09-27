#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define D 256
#define Q 101

int naivny(char *T, char *W) {
    int n = strlen(T);
    int m = strlen(W);
    int cmp = 0;

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            cmp++;
            if (T[i + j] != W[j]) break;
        }
        if (j == m)
            printf("  вхождение с индекса %d\n", i);
    }
    return cmp;
}

int rabin_karp(char *T, char *W) {
    int n = strlen(T);
    int m = strlen(W);
    int cmp = 0;
    int hcmp = 0;
    int hW = 0;
    int hT = 0;
    int dm = 1;

    for (int i = 0; i < m - 1; i++)
        dm = (dm * D) % Q;

    for (int i = 0; i < m; i++) {
        hW = (hW * D + W[i]) % Q;
        hT = (hT * D + T[i]) % Q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (hT == hW) {
            hcmp++;
            int j;
            for (j = 0; j < m; j++) {
                cmp++;
                if (T[i + j] != W[j]) break;
            }
            if (j == m)
                printf("  вхождение с индекса %d\n", i);
        }
        if (i < n - m) {
            hT = (D * (hT - T[i] * dm) + T[i + m]) % Q;
            if (hT < 0) hT += Q;
        }
    }
    printf("  сравнений хешей: %d\n", hcmp);
    return cmp;
}

int main(void) {
    char filename[100], W[100];

    FILE *f = fopen("2.txt", "r");
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

    printf("Подстрока: ");
    if (scanf("%99s", W) != 1) {
        fprintf(stderr, "Не удалось прочитать подстроку\n");
        free(T);
        return 1;
    }

    printf("\nДлина текста: %ld символов\n", size);

    printf("\nНаивный поиск:\n");
    int c1 = naivny(T, W);
    printf("  сравнений: %d\n", c1);

    printf("\nРабин-Карп:\n");
    int c2 = rabin_karp(T, W);
    printf("  сравнений: %d\n", c2);

    free(T);
    return 0;
}
