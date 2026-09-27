#include <stdlib.h>
#include "sdp.h"

void insertRecursive(struct Node **root, int value)
{
    if (*root == NULL)
    {
        *root = malloc(sizeof(struct Node));
        if (*root == NULL)
            exit(1);
        (*root)->Data = value;
        (*root)->Left = NULL;
        (*root)->Right = NULL;
        return;
    }

    if (value < (*root)->Data)
        insertRecursive(&(*root)->Left, value);
    else if (value > (*root)->Data)
        insertRecursive(&(*root)->Right, value);
}
