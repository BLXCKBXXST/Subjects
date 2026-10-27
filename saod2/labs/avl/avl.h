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
int deleteAVL(int D, struct Node **p);

void generateNumbers(int A[], int n);
void inorder(struct Node *p);
int size(struct Node *p);
int checkSum(struct Node *p);
int height(struct Node *p);
int sumHeight(struct Node *p, int level);
void freeTree(struct Node *p);

void printComparison(const int A[], int maxN);

struct Node *searchNode(struct Node *p, int key);
void searchMultiple(struct Node *root);

int saveTreeSvg(const char *filename, struct Node *root);
void showTreeImage(struct Node *root);
int saveDeleteStep(struct Node *root, int step);
void showDeletePreview(const int deletedKeys[], int count);

#endif
