#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lanc.h"
#include "blokk.h"
#include "../lib/debugmalloc.h"

void lanc_init(Lanc *lanc) {
    lanc->eleje = NULL;
    lanc->vege = NULL;
    lanc->darabszam = 0;
    lanc->csak_olvashato = false;
    lanc->mentetlen = false;
};

void lanc_hozzafuz(Lanc *lanc, Blokk *blokk) {
    if (lanc->darabszam == 0) {
        lanc->eleje = blokk;
        lanc->vege = blokk;
    }
    else {
        lanc->vege = blokk->kovetkezo;
        lanc->vege = blokk;
    }
    lanc->darabszam++;
}

void lanc_felszabadit(Lanc *lanc) {
    Blokk *akt = lanc->eleje;
    while (akt != NULL) {
        Blokk *kov = akt->kovetkezo;
        free(akt);
        akt = kov;
    }
    lanc->eleje = NULL, lanc->vege = NULL, lanc->darabszam = 0;
}

bool lanc_genesis(Lanc *lanc) {
    Tranzakcio tranzgen;
    snprintf(tranzgen.cimzett, sizeof(tranzgen.cimzett), "%s", "SYSTEM");
    snprintf(tranzgen.kuldo, sizeof(tranzgen.kuldo), "%s", "SYSTEM");
    tranzgen.osszeg = 1000000;
    // return lanc_uj_blokk(lanc, &tranzgen);

    // forditas miatt csak return true atmenetileg
    return true;
}

// bool lanc_uj_blokk(Lanc *lanc, const Tranzakcio *tranz) {
//     char ido[IDOBELYEG_MERET];
//     idobelyeg_most(ido);
//     i32 sorszam = lanc->darabszam;
//     if (lanc->vege) {
//         u64 hash_elozo = 0;
//     }
//     u64 hash_elozo = 0;
//     Blokk *blokk = blokk_letrehoz(sorszam, ido, tranz, hash_elozo);
//     if (blokk == NULL) return false;
//     lanc_hozzafuz(lanc, blokk);
//     return true;
// };

i64 egyenleg_szamol(const Lanc *lanc, const char *nev) {
    i64 szamolt = 0;
    for (int i = 0; i < lanc->darabszam; i++) {
        if (lanc->eleje->tranz.cimzett == nev) {
            szamolt += lanc->eleje->tranz.osszeg;
        }
        if (lanc->eleje->tranz.kuldo == nev && (strcmp(lanc->eleje->tranz.kuldo, "SYSTEM") != 0)) {
            szamolt -= lanc->eleje->tranz.osszeg;
        }
    }
    return szamolt;
}
