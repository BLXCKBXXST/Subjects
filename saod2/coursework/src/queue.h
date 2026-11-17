#ifndef QUEUE_H
#define QUEUE_H
#include "zapis.h"
struct Ochered {
    struct Zapis *zapis;
    struct Ochered *next;
};
int putqueue(struct Ochered **first, struct Ochered **last, struct Zapis *zapis);
struct Zapis *getqueue(struct Ochered **first, struct Ochered **last);
struct Ochered *sozdat_ochered(struct Zapis **uk, int n, int god);
void ochistit_ochered(struct Ochered *first);
#endif
