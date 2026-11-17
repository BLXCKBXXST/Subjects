#include <stddef.h>
#include "tree.h"

struct Derevo *nayti_v_dereve(struct Derevo *root, const char *key) {
    while (root != NULL) {
        int c = sravnit(key, root->key);
        if (c == 0) return root;
        if (c < 0) root = root->left;
        else root = root->right;
    }
    return NULL;
}
