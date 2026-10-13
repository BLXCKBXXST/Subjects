#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define SVG_FILE "avl.svg"
#define TEMP_FILE "avl.tmp.svg"

void showTreeImage(struct Node *root)
{
    if (!saveTreeSvg(TEMP_FILE, root))
    {
        perror(TEMP_FILE);
        return;
    }

    if (rename(TEMP_FILE, SVG_FILE) != 0)
    {
        perror(SVG_FILE);
        return;
    }

    printf("Изображение АВЛ-дерева открывается в браузере; файл: %s\n", SVG_FILE);
    fflush(stdout);

    if (system("command -v xdg-open >/dev/null 2>&1") == 0)
    {
        if (system("xdg-open labs/avl/preview.html >/dev/null 2>&1 &") != 0)
            printf("Откройте labs/avl/preview.html в браузере.\n");
    }
    else
        printf("Откройте labs/avl/preview.html в браузере.\n");
}
