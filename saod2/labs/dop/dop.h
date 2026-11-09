#ifndef DOP_H
#define DOP_H

#define N 500
#define MAX_KEY 1000

typedef struct {
    int Data, Weight;
} Item;

typedef struct vertex {
    int Data, Weight, Index;
    struct vertex *Left, *Right;
} Vertex;

extern Item A[N + 1];
extern int AW[N + 1][N + 1], AP[N + 1][N + 1], AR[N + 1][N + 1];

void generate(void);
void buildMatrices(int n);
Vertex *createTree(int L, int R);
void inorder(Vertex *p, int *count);
void freeTree(Vertex *p);
int size(Vertex *p);
int checksum(Vertex *p);
int height(Vertex *p);
int weightedSum(Vertex *p, int level);
void printMatrix(const char *name, int M[N + 1][N + 1], int n);
void showDOPMatrices(int n);
void printDOPComparison(void);
int saveSVG(const char *filename, Vertex *root, int n);

#endif
