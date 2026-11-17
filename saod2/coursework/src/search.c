#include "coursework.h"

int bin_poisk(struct Zapis **uk, int n, int god) {
    if (n <= 0)
        return -1;

    int L = 0;
    int R = n - 1;

    while (L < R) {
        int m = (L + R) / 2;

        if (uk[m]->god < god)
            L = m + 1;
        else
            R = m;
    }

    if (uk[L]->god == god)
        return L;

    return -1;
}

