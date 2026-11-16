#ifndef LAB_3_2_ISDP_H
#define LAB_3_2_ISDP_H
struct Node { int Data; struct Node *Left, *Right; };
struct Node *ISDP(int A[], int L, int R);
void printTree(struct Node *p);
int size(struct Node *p);
int checkSum(struct Node *p);
int height(struct Node *p);
int sumHeight(struct Node *p, int level);
void freeTree(struct Node *p);
void sortArray(int A[], int left, int right);
void printComparisonTable(struct Node *root);
int saveTreeSvg(const char *filename, struct Node *root);
struct Node *searchRecursive(struct Node *root, int key);
void searchMultiple(struct Node *root);
#endif
