#ifndef LAB_3_4_SDP_DELETE_H
#define LAB_3_4_SDP_DELETE_H
#include "../3.3-sdp/3.3-sdp.h"
int deleteNode(struct Node **root, int key);
int deleteNodeMove(struct Node **root, int key);
int readCount(const char *prompt, int max);
int saveDeleteStep(struct Node *root, int step);
int showDeletePreview(const int deletedKeys[], int count);
#endif
