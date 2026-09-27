#ifndef TREEPRINT_H
#define TREEPRINT_H

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

void printTree(struct Node* root, int level);

#endif
