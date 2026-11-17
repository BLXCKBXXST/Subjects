#include <stdlib.h>
#include "3.9-a1-a2.h"

void add(Vertex **p, WeightedItem D)
{
    if (*p == NULL)
    {
        *p = malloc(sizeof(Vertex));
        if (*p == NULL) exit(EXIT_FAILURE);
        (*p)->Data = D.Data;
        (*p)->Weight = D.Weight;
        (*p)->Index = D.Index;
        (*p)->Left = (*p)->Right = NULL;
    }
    else if (D.Data < (*p)->Data)
        add(&(*p)->Left, D);
    else
        add(&(*p)->Right, D);
}
