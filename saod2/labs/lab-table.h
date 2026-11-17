#ifndef LAB_TABLE_H
#define LAB_TABLE_H

#include <stdio.h>

static inline void tableBorder(const int widths[], int count,
                               const char *left, const char *middle, const char *right)
{
    printf("%s", left);
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < widths[i] + 2; j++) printf("─");
        printf("%s", i + 1 < count ? middle : right);
    }
    printf("\n");
}

static inline void tableCell(const char *text, int width)
{
    int length = 0;
    for (const unsigned char *p = (const unsigned char *)text; *p; p++)
        if ((*p & 0xc0) != 0x80) length++;

    int spaces = width > length ? width - length : 0;
    printf("│ %*s%s%*s ", spaces / 2, "", text, spaces - spaces / 2, "");
}

static inline void tableInt(int value, int width)
{
    char text[32];
    snprintf(text, sizeof(text), "%d", value);
    tableCell(text, width);
}

static inline void tableDouble(double value, int width)
{
    char text[64];
    snprintf(text, sizeof(text), "%.3f", value);
    tableCell(text, width);
}

#endif
