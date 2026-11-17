#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../coursework/src/coursework.h"

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
    int list_size = 0;
    for (struct Spisok *item = p->head; item != NULL; item = item->next) {
        list_size++;
        struct Zapis *z = item->zapis;
        assert(z >= records && z < records + N);
        assert(z->god == year);
        assert(seen[z - records]++ == 0);
        char key[65]; key_of(z, key);
        assert(sravnit(key, p->key) == 0);
    }
    assert(list_size == p->weight);
    int left = verify(p->left, low, p->key, year, root);
    int right = verify(p->right, p->key, high, year, root);
    int total = left + p->weight + right;
    assert(2 * left < total);
    assert(2 * (left + p->weight) >= total);
    return total;
}

static int verify_records(struct RecordVertex *p, const char *low,
                          const char *high, struct Derevo *groups, int *count) {
    if (p == NULL) return 0;
    assert(!low || sravnit(low, p->key) <= 0);
    assert(!high || sravnit(p->key, high) <= 0);
    struct Zapis *z = p->zapis;
    assert(z >= records && z < records + N);
    assert(seen[z - records]++ == 0);
    char key[65]; key_of(z, key);
    assert(sravnit(key, p->key) == 0);
    assert(p->weight == nayti_v_dereve(groups, key)->weight);
    (*count)++;
    int left = verify_records(p->left, low, p->key, groups, count);
    int right = verify_records(p->right, p->key, high, groups, count);
    int total = left + p->weight + right;
    assert(2 * left < total && total <= 2 * (left + p->weight));
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
        struct RecordVertex *individual = postroit_zapisi_a2(root);
        int count = 0;
        memset(seen, 0, sizeof(seen));
        verify_records(individual, NULL, NULL, root, &count);
        assert(count == last - first);
        ochistit_zapisi_a2(individual);
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
    assert(sohranit_zapisi_svg(root, "build/coursework-long-records.svg"));
    ochistit_derevo(root);
    for (int i = 0; i < 5; i++) {
        memset(records[i].zagl, ' ', 32);
        memcpy(records[i].zagl, "Same", 4);
        a[i] = &records[i];
    }
    root = postroit_a2(a, 5);
    struct RecordVertex *individual = postroit_zapisi_a2(root);
    assert(individual->left && individual->right);
    assert(sravnit(individual->key, individual->left->key) == 0);
    assert(sravnit(individual->key, individual->right->key) == 0);
    int count = 0;
    memset(seen, 0, sizeof(seen));
    assert(verify_records(individual, NULL, NULL, root, &count) == 25);
    assert(count == 5);
    ochistit_zapisi_a2(individual);
    ochistit_derevo(root);
    Element entries[5] = {0};
    for (int i = 0; i < 5; i++) entries[i].zapis = &records[i];
    Group first = {"Same", 0, 2}, last = {"Same", 2, 3};
    root = NULL;
    Add(&root, first, entries);
    Add(&root, last, entries);
    assert(root->weight == 5 && !root->left && !root->right);
    struct Spisok *item = root->head;
    for (int i = 0; i < 5; i++) {
        assert(item && item->zapis == &records[i]);
        item = item->next;
    }
    assert(item == NULL);
    ochistit_derevo(root);
    puts("Coursework: actual 4000 records, year search, FIFO, A2 medians and duplicates passed.");
}
