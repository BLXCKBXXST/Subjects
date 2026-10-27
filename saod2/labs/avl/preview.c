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

int saveDeleteStep(struct Node *root, int step)
{
    char filename[64];
    snprintf(filename, sizeof(filename), "avl-delete-%d.svg", step);
    return saveTreeSvg(filename, root);
}

void showDeletePreview(const int deletedKeys[], int count)
{
    static int browserOpened = 0;
    FILE *file = fopen("avl-delete-steps.tmp.js", "w");
    if (file == NULL)
    {
        perror("avl-delete-steps.tmp.js");
        return;
    }

    fputs("window.deletedKeys = [", file);
    for (int i = 0; i < count; i++)
        fprintf(file, "%s%d", i ? ", " : "", deletedKeys[i]);
    fputs("];\n", file);
    if (fclose(file) != 0)
    {
        perror("avl-delete-steps.tmp.js");
        return;
    }
    if (rename("avl-delete-steps.tmp.js", "avl-delete-steps.js") != 0)
    {
        perror("avl-delete-steps.js");
        return;
    }

    if (browserOpened)
        return;

    printf("Просмотр удаления: labs/avl/delete_preview.html\n");
    fflush(stdout);
    if (system("command -v xdg-open >/dev/null 2>&1") == 0)
    {
        if (system("xdg-open labs/avl/delete_preview.html >/dev/null 2>&1 &") != 0)
            printf("Откройте labs/avl/delete_preview.html в браузере.\n");
    }
    else
        printf("Откройте labs/avl/delete_preview.html в браузере.\n");
    browserOpened = 1;
}
