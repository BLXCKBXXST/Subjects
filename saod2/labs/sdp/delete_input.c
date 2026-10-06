#include <stdio.h>
#include "delete_input.h"

int readCount(const char *prompt, int max)
{
    int value;
    printf("%s (1..%d): ", prompt, max);
    fflush(stdout);
    if (scanf("%d", &value) != 1 || value < 1 || value > max)
        return 0;
    return value;
}
