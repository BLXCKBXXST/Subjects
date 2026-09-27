#ifndef SDP_H
#define SDP_H

struct Node {
    int Data;
    struct Node *Left;
    struct Node *Right;
};

void insertRecursive(struct Node **root, int value);
void insertDouble(struct Node **root, int value);

#ifdef USE_DOUBLE
#define insert insertDouble
#else
#define insert insertRecursive
#endif

void generateNumbers(int A[], int n);
void inorder(struct Node *root);
void printStats(struct Node *root);
void printExtras(const int A[], int n, struct Node *root);
void freeTree(struct Node *root);

#endif
