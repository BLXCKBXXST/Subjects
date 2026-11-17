#include "tree.h"

void A2(struct Derevo **Root, Group V[], Element *a, int L, int R) {
    int wes = 0, sum = 0, i;

    if (L <= R) {
        for (i = L; i <= R; i++)
            wes = wes + V[i].weight;

        for (i = L; i <= R; i++) {
            if (2 * sum < wes &&
                2 * (sum + V[i].weight) >= wes)
                break;

            sum = sum + V[i].weight;
        }

        Add(Root, V[i], a);

        A2(Root, V, a, L, i - 1);
        A2(Root, V, a, i + 1, R);
    }
}
