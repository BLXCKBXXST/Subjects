#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "coursework.h"

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
