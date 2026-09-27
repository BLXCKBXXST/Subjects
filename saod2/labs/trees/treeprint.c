#include <stdio.h>
#include <string.h>
#include "treeprint.h"

static void printRec(struct Node* root, char* prefix, int isRight) {
    if (root == NULL) return;

    int len = strlen(prefix);
    strcat(prefix, isRight ? "    " : "│   ");
    printRec(root->right, prefix, 1);
    prefix[len] = '\0';

    printf("%s%s%d\n", prefix, isRight ? "┌── " : "└── ", root->data);

    strcat(prefix, isRight ? "│   " : "    ");
    printRec(root->left, prefix, 0);
    prefix[len] = '\0';
}

void printTree(struct Node* root, int level) {
    char prefix[4096] = "";
    if (root == NULL) return;
    printRec(root->right, prefix, 1);
    printf("%d\n", root->data);
    printRec(root->left, prefix, 0);
}
