#ifndef SDP_H
#define SDP_H

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
void printExtras(const int A[], int n, struct Node *sdp1, struct Node *sdp2);
void printSummary(const int A[], int maxN);
int saveTreeSvg(const char *filename, struct Node *root);
void freeTree(struct Node *root);
int deleteNode(struct Node **root, int key);

struct Node *searchRecursive(struct Node *root, int key);
void searchMultiple(struct Node *root);

#endif
