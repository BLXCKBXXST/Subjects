#include <stdlib.h>
#include "sdp.h"

void insertDouble(struct Node **root, int value)
{
    while (*root != NULL)
    {
        if (value < (*root)->Data)
            root = &(*root)->Left;
        else if (value > (*root)->Data)
            root = &(*root)->Right;
        else
            return;
    }

    *root = malloc(sizeof(struct Node));
    if (*root == NULL)
        exit(1);
    (*root)->Data = value;
    (*root)->Left = NULL;
    (*root)->Right = NULL;
}
