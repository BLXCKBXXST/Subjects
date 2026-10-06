#include <stdio.h>
#include <stdlib.h>
#include "sdp.h"
#include "delete_preview.h"

#define SVG_FILE "sdp-delete.svg"
#define TEMP_FILE "sdp-delete.tmp.svg"

void showTreeImage(struct Node *root)
{
    static int browserOpened = 0;

    if (root != NULL)
    {
        if (!saveTreeSvg(TEMP_FILE, root))
        {
            perror(TEMP_FILE);
            return;
        }
    }
    else
    {
        FILE *file = fopen(TEMP_FILE, "w");
        if (file == NULL)
        {
            perror(TEMP_FILE);
            return;
        }
        fputs("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"400\" height=\"120\">"
              "<text x=\"20\" y=\"65\" font-size=\"24\">Дерево пусто</text></svg>\n", file);
        fclose(file);
    }

    if (rename(TEMP_FILE, SVG_FILE) != 0)
    {
        perror(SVG_FILE);
        return;
    }

    if (!browserOpened)
    {
        printf("Изображение дерева открывается в браузере; файл: %s\n", SVG_FILE);
        fflush(stdout);
        if (system("command -v xdg-open >/dev/null 2>&1") == 0)
        {
            if (system("xdg-open labs/sdp/delete_preview.html >/dev/null 2>&1 &") != 0)
                printf("Откройте labs/sdp/delete_preview.html в браузере.\n");
        }
        else
            printf("Откройте labs/sdp/delete_preview.html в браузере.\n");
        browserOpened = 1;
    }
}
