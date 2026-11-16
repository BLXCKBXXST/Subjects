#include <stdlib.h>
#include <time.h>
#include "3.9-a1-a2.h"
#include "../lab-viewer.h"

Item A[N + 1];

int main(int argc, char **argv)
{
    (void)argc;
    if (!initLabPaths(argv[0])) return 1;
    srand((unsigned)time(NULL));
    generate();
    int ok = printComparison();
    if (ok) openLabPage("labs/3.9-a1-a2/3.9-view.html");
    return ok ? 0 : 1;
}
