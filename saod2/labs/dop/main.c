#include <stdlib.h>
#include <time.h>
#include "dop.h"

int main(int argc, char **argv)
{
    int show = argc > 1 ? atoi(argv[1]) : 10;

    srand((unsigned)time(NULL));
    generate();

    if (show >= 1 && show <= N)
        showDOPMatrices(show);

    printDOPComparison();
    return 0;
}
