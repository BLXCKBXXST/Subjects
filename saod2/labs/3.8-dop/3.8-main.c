#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "3.8-dop.h"
#include "../lab-viewer.h"

Item A[N + 1];

int main(int argc, char **argv)
{
    if (!initLabPaths(argv[0])) return 1;
    int show = 10;
    if (argc > 1)
    {
        char *end;
        long value = strtol(argv[1], &end, 10);
        if (*end != '\0' || value < 1 || value > N)
        {
            fprintf(stderr, "Размер примера: от 1 до %d.\n", N);
            return 1;
        }
        show = (int)value;
    }
    srand((unsigned)time(NULL));
    generate();
    int ok = showDOPMatrices(show);
    if (!printDOPComparison()) ok = 0;
    if (ok) openLabPage("labs/3.8-dop/3.8-view.html");
    return ok ? 0 : 1;
}
