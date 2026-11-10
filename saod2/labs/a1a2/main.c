#include <stdlib.h>
#include <time.h>
#include "a1a2.h"

Item A[N + 1];

int main(void)
{
    srand((unsigned)time(NULL));
    generate();
    printComparison();
    return 0;
}
