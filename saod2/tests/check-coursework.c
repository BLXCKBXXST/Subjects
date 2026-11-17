#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../coursework/src/coursework.h"
#include "../coursework/src/tree.h"
#include "../coursework/src/queue.h"
#include "../coursework/src/cp866.h"

static struct Zapis records[N];
static int seen[N];

static void key_of(struct Zapis *z, char key[65]) {
    cp866_to_utf8(z->zagl, 32, key);
    size_t n = strlen(key);
    while (n && key[n - 1] == ' ') key[--n] = 0;
}

static int verify(struct Derevo *p, const char *low, const char *high,
                  int year, struct Derevo *root) {
    if (!p) return 0;
    assert(!low || sravnit(low, p->key) < 0);
    assert(!high || sravnit(p->key, high) < 0);
    assert(nayti_v_dereve(root, p->key) == p);
    assert(p->weight > 0);
    for (int i = 0; i < p->weight; i++) {
        struct Zapis *z = p->zapisi[i];
        assert(z >= records && z < records + N);
        assert(z->god == year);
        assert(seen[z - records]++ == 0);
        char key[65]; key_of(z, key);
        assert(sravnit(key, p->key) == 0);
    }
    int left = verify(p->left, low, p->key, year, root);
    int right = verify(p->right, p->key, high, year, root);
    int total = left + p->weight + right;
    assert(2 * left < total);
    assert(2 * (left + p->weight) >= total);
    return total;
}

int main(void) {
    FILE *file = fopen(BASE_FILE, "rb");
    assert(file);
    assert(fread(records, sizeof(records[0]), N, file) == N);
    assert(fclose(file) == 0);
    struct Zapis *a[N], *copy[N];
    for (int i = 0; i < N; i++) a[i] = &records[i];
    hoar(a, 0, N - 1);
    for (int i = 1; i < N; i++) assert(sravni(a[i - 1], a[i]) <= 0);
    hoar(NULL, 0, -1);
    assert(bin_poisk(NULL, 0, 2000) == -1);
    assert(!postroit_a2(NULL, 0));
    assert(!nayti_v_dereve(NULL, "нет"));
    for (int first = 0; first < N;) {
        int year = a[first]->god, last = first;
        while (last < N && a[last]->god == year) last++;
        assert(bin_poisk(a, N, year) == first);
        struct Ochered *queue = sozdat_ochered(a, N, year), *tail = NULL;
        for (struct Ochered *p = queue; p; p = p->next) tail = p;
        for (int i = first; i < last; i++) {
            copy[i - first] = getqueue(&queue, &tail);
            assert(copy[i - first] == a[i]);
        }
        assert(!queue && !tail && !getqueue(&queue, &tail));
        memset(seen, 0, sizeof(seen));
        struct Derevo *root = postroit_a2(copy, last - first);
        assert(verify(root, NULL, NULL, year, root) == last - first);
        assert(!nayti_v_dereve(root, "несуществующий ключ ~~~~~"));
        ochistit_derevo(root);
        first = last;
    }
    assert(!sozdat_ochered(a, N, -1));
    memset(records, ' ', sizeof(records));
    const char *titles[] = {"A & B <C> \"D\"", "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
                            "A & B <C> \"D\"", "Middle", "Middle", "Z"};
    for (int i = 0; i < 6; i++) {
        memcpy(records[i].zagl, titles[i], strlen(titles[i]));
        records[i].god = 2000;
        a[i] = &records[i];
    }
    memset(records[6].zagl, 0x98, 32);
    records[6].god = 2000;
    a[6] = &records[6];
    memset(seen, 0, sizeof(seen));
    struct Derevo *root = postroit_a2(a, 7);
    assert(verify(root, NULL, NULL, 2000, root) == 7);
    assert(nayti_v_dereve(root, titles[0])->weight == 2);
    assert(sohranit_svg(root, "build/coursework-long.svg"));
    ochistit_derevo(root);
    puts("Coursework: actual 4000 records, year search, FIFO, A2 medians and duplicates passed.");
}
