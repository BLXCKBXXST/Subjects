#ifndef A1A2_H
#define A1A2_H

#include "../3.8-dop/3.8-dop.h"

typedef struct {
    int Data, Weight, Index;
} WeightedItem;

void add(Vertex **p, WeightedItem D);
void QuickSort(WeightedItem V[], int L, int R);
void QuickSortKeys(Item V[], int L, int R);
void A1(WeightedItem V[], int n, Vertex **root);
void A2(WeightedItem V[], int L, int R, Vertex **root);
int printComparison(void);

#endif
