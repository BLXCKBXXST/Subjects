#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "sdp.h"

#define MAX_N 500

static void deleteSvg(void)
{
    char name[80];

    remove("sdp-isdp.svg");
    remove("sdp-sdp.svg");
    remove("sdp-sdp2.svg");

    remove("images/sdp/sdp-isdp.svg");
    remove("images/sdp/sdp-sdp.svg");
    remove("images/sdp/sdp-sdp2.svg");

    for (int n = 200; n <= 500; n += 100)
    {
        snprintf(name, sizeof(name), "sdp-isdp-%d.svg", n);
        remove(name);
        snprintf(name, sizeof(name), "sdp-sdp-%d.svg", n);
        remove(name);
        snprintf(name, sizeof(name), "sdp-sdp2-%d.svg", n);
        remove(name);

        snprintf(name, sizeof(name), "images/sdp/sdp-isdp-%d.svg", n);
        remove(name);
        snprintf(name, sizeof(name), "images/sdp/sdp-sdp-%d.svg", n);
        remove(name);
        snprintf(name, sizeof(name), "images/sdp/sdp-sdp2-%d.svg", n);
        remove(name);
    }

    rmdir("images/sdp");
    rmdir("images");
}

static void stopProgram(int signalNumber)
{
    unlink("sdp-isdp.svg");
    unlink("sdp-sdp.svg");
    unlink("sdp-sdp2.svg");

    unlink("images/sdp/sdp-isdp.svg");
    unlink("images/sdp/sdp-sdp.svg");
    unlink("images/sdp/sdp-sdp2.svg");

    rmdir("images/sdp");
    rmdir("images");

    _exit(128 + signalNumber);
}

void insertRecursive(struct Node **root, int value)
{
    if (*root == NULL)
    {
        *root = malloc(sizeof(struct Node));
        if (*root == NULL)
            exit(1);
        (*root)->Data = value;
        (*root)->Left = NULL;
        (*root)->Right = NULL;
        return;
    }

    if (value < (*root)->Data)
        insertRecursive(&(*root)->Left, value);
    else if (value > (*root)->Data)
        insertRecursive(&(*root)->Right, value);
}

void insertDouble(struct Node **root, int value)
{
    while (*root != NULL)
    {
        if (value < (*root)->Data)
            root = &(*root)->Left;
        else if (value > (*root)->Data)
            root = &(*root)->Right;
        else
            return;
    }

    *root = malloc(sizeof(struct Node));
    if (*root == NULL)
        exit(1);
    (*root)->Data = value;
    (*root)->Left = NULL;
    (*root)->Right = NULL;
}

struct Node *searchRecursive(struct Node *root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->Data == key)
        return root;

    if (key < root->Data)
        return searchRecursive(root->Left, key);
    else
        return searchRecursive(root->Right, key);
}

struct Node *searchIterative(struct Node *root, int key)
{
    while (root != NULL)
    {
        if (root->Data == key)
            return root;

        if (key < root->Data)
            root = root->Left;
        else
            root = root->Right;
    }

    return NULL;
}

void searchMultiple(struct Node *sdp1, struct Node *sdp2)
{
    int count;

    printf("\nПоиск по ключам\n");
    printf("Количество ключей (0 - выход): ");

    if (scanf("%d", &count) != 1 || count <= 0)
        return;

    for (int i = 0; i < count; i++)
    {
        int key;
        struct Node *recursiveResult;
        struct Node *iterativeResult;

        printf("Ключ %d: ", i + 1);

        if (scanf("%d", &key) != 1)
            return;

        recursiveResult = searchRecursive(sdp1, key);
        iterativeResult = searchIterative(sdp2, key);

        printf("  рекурсивный поиск: %s\n",
               recursiveResult != NULL ? "найден" : "не найден");
        printf("  нерекурсивный поиск: %s\n",
               iterativeResult != NULL ? "найден" : "не найден");
    }
}

int main(void)
{
    int A[MAX_N];
    struct Node *sdp1 = NULL;
    struct Node *sdp2 = NULL;

    signal(SIGINT, stopProgram);
    deleteSvg();

    srand((unsigned)time(NULL));
    generateNumbers(A, MAX_N);

    for (int i = 0; i < 100; i++)
    {
        insertRecursive(&sdp1, A[i]);
        insertDouble(&sdp2, A[i]);
    }

    printf("Обход ИСДП, СДП1 и СДП2 слева направо:\n");
    inorder(sdp1);
    printf("\n");

    printSummary(A, MAX_N);
    printExtras(A, 100, sdp1, sdp2);

    searchMultiple(sdp1, sdp2);

    deleteSvg();
    freeTree(sdp1);
    freeTree(sdp2);
    return 0;
}
