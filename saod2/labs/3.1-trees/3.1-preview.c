#include <stdio.h>
#include "3.1-trees.h"
#include "../lab-viewer.h"
int showTree(struct Node *root, int large)
{
    const char *file = large ? "3.1-trees-100.svg" : "3.1-trees.svg";
    if (!saveTreeSvg(file, root)) { perror(file); return 0; }
    return openLabPage(large ? "labs/3.1-trees/3.1-view-100.html" : "labs/3.1-trees/3.1-view.html");
}
