#ifndef ZAPIS_H
#define ZAPIS_H

struct Zapis {
    char avtor[12];
    char zagl[32];
    char izd[16];
    short god;
    short str;
};

_Static_assert(sizeof(struct Zapis) == 64);

#endif
