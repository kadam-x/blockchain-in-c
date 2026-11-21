#ifndef LANC_H
#define LANC_H

#include <stdbool.h>

#include "blokk.h"

typedef struct Lanc {
    Blokk *eleje;
    Blokk *vege;
    i32 darabszam;
    bool mentetlen;
    bool csak_olvashato;
} Lanc;

void lanc_init(Lanc *lanc);
void lanc_felszabadit(Lanc *lanc);
bool lanc_genesis(Lanc *lanc);
void lanc_hozzafuz(Lanc *lanc, Blokk *blokk);
bool lanc_uj_blokk(Lanc *lanc, const Tranzakcio *tranz);
i64 egyenleg_szamol(const Lanc *lanc, const char *nev);

#endif
