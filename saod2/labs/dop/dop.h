#ifndef DOP_H
#define DOP_H

#include <stdio.h>

typedef struct vertex {
    int Data, Weight, Index;
    struct vertex *Left, *Right;
} Vertex;

int saveSVG(const char *filename, Vertex *root, int n);

#endif
