#include <stdio.h>
#include <stdlib.h>
#include "3.5-avl.h"
#include "../lab-viewer.h"

void showTreeImage(struct Node *root)
{
    if (!saveTreeSvg("3.5-avl.svg", root))
    {
        fprintf(stderr, "Не удалось сохранить 3.5-avl.svg\n");
        return;
    }
    openLabPage("labs/3.5-avl/3.5-view.html");
}
