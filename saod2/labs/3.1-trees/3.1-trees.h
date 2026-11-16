#ifndef LAB_3_1_TREES_H
#define LAB_3_1_TREES_H
struct Node { int Data; struct Node *Left, *Right; };
struct Node *newNode(int data);
void preorder(struct Node *root);
void inorder(struct Node *root);
void postorder(struct Node *root);
int size(struct Node *root);
int checksum(struct Node *root);
int height(struct Node *root);
void sumHeights(struct Node *root, int level, int *sum);
void freeTree(struct Node *root);
int saveTreeSvg(const char *filename, struct Node *root);
int showTree(struct Node *root, int large);
#endif
