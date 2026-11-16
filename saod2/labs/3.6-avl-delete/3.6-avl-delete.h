#ifndef AVL_DELETE_H
#define AVL_DELETE_H
#include "../3.5-avl/3.5-avl.h"

int deleteAVL(int D, struct Node **p);
int saveDeleteStep(struct Node *root, int step);
int showDeletePreview(const int deletedKeys[], int count);
#endif
