#ifndef AVL_H
#define AVL_H

struct Node
{
    int Data;
    int Bal;
    struct Node *Left;
    struct Node *Right;
};

void addAVL(int D, struct Node **p);
void generateNumbers(int A[], int n);
void inorder(struct Node *p);
int size(struct Node *p);
int checkSum(struct Node *p);
int height(struct Node *p);
int sumHeight(struct Node *p, int level);
void printComparison(const int A[], int n, struct Node *avl);
void freeTree(struct Node *p);

#endif
