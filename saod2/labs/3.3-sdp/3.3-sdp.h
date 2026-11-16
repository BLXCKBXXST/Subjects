#ifndef LAB_3_3_SDP_H
#define LAB_3_3_SDP_H

struct Node
{
    int Data;
    struct Node *Left;
    struct Node *Right;
};

void insertRecursive(struct Node **root, int value);
void insertDouble(struct Node **root, int value);
void generateNumbers(int A[], int n);
void inorder(struct Node *root);
int printExtras(const int A[], int n, struct Node *sdp1, struct Node *sdp2);
void printSummary(const int A[], int maxN);
int saveTreeSvg(const char *filename, struct Node *root);
int size(struct Node *root);
int checkSum(struct Node *root);
int height(struct Node *root);
int sumHeight(struct Node *root, int level);
void freeTree(struct Node *root);
struct Node *searchRecursive(struct Node *root, int key);
void searchMultiple(struct Node *root);

#endif
