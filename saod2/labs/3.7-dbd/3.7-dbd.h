#ifndef DBD_H
#define DBD_H

#include "../3.5-avl/3.5-avl.h"

extern int VR, HR;

void B2INSERT(int D, struct Node **p);
int pageLevels(struct Node *p);
int saveDBDSvg(const char *filename, struct Node *root);
void showDBDImage(struct Node *root);
void printDBDComparison(const int A[], int maxN);

#endif
