#include <stdlib.h>
#include "3.8-dop.h"

void addDOP(Vertex **p, int k)
{
    if (*p == NULL)
    {
        *p = malloc(sizeof(Vertex));
        if (*p == NULL) exit(EXIT_FAILURE);
        (*p)->Data = A[k].Data;
        (*p)->Weight = A[k].Weight;
        (*p)->Index = k;
        (*p)->Left = (*p)->Right = NULL;
    }
    else if (A[k].Data < (*p)->Data)
        addDOP(&(*p)->Left, k);
    else
        addDOP(&(*p)->Right, k);
}
