#include <stdio.h>
#include <time.h>
#include "3.6-avl-delete.h"
#include "../lab-viewer.h"

int saveDeleteStep(struct Node *root, int step)
{
    char filename[80];
    snprintf(filename, sizeof(filename), "3.6-avl-delete-%d.svg", step);
    return saveTreeSvg(filename, root);
}

int showDeletePreview(const int deletedKeys[], int count)
{
    static int browserOpened = 0;
    static unsigned long session;
    if (count == 0) session = (unsigned long)time(NULL) + (unsigned long)clock();
    FILE *file = fopen("3.6-avl-delete-steps.js", "w");
    if (file == NULL)
    {
        perror("3.6-avl-delete-steps.js");
        return 0;
    }
    fprintf(file, "window.treeSession = '%lu';\nwindow.deletedKeys = [", session);
    for (int i = 0; i < count; i++)
        fprintf(file, "%s%d", i ? ", " : "", deletedKeys[i]);
    fputs("];\n", file);
    if (fclose(file) != 0)
    {
        perror("3.6-avl-delete-steps.js");
        return 0;
    }
    if (!browserOpened)
        browserOpened = openLabPage("labs/3.6-avl-delete/3.6-view.html");
    return 1;
}
