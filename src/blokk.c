#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

#include "blokk.h"

#include "../lib/debugmalloc.h"

#define FNV_64_PRIME 0x100000001b3ULL // 
#define FNV_64_BASIS 0xcbf29ce484222325ULL


// A fuggveny feltetelezi hogy a rendszer ahol a kod futtatva van mukodo orat
// hasznal, ezert nincs semmilyen safety-check
void idobelyeg_most(char cel[IDOBELYEG_MERET]) {
    time_t masodpercek = time(NULL);
    strftime(cel, IDOBELYEG_MERET, "%Y-%m-%d %H:%M:%S", localtime(&masodpercek));
}

#define ADAT_MERET 256


// A blokk nevei lezart szovegek, a fuggveny ezt feltetelezi, ezert nem is
// kezeli hibanak a 
u64 hash_szamol(const Blokk *blokk) {
    char adat[ADAT_MERET];
    int j = snprintf(adat, sizeof(adat), "%d;%s;%s;%s;%d;%016"PRIx64, blokk->sorszam, blokk->idobelyeg, blokk->tranz.kuldo, blokk->tranz.cimzett, blokk->tranz.osszeg, blokk->hash_elozo);

    u64 hash = FNV_64_BASIS;
    for (size_t i = 0; i < j; i++) {
        hash ^= (unsigned char)adat[i];
        hash *= FNV_64_PRIME;
    }
    
    return hash;
}

bool blokk_hash_egyezik(const Blokk *blokk) {
    return (blokk->hash == hash_szamol(blokk));
}

// A fuggveny dinamikusan foglal memoriat es hozza letre a blokkot, feltolti
// adatokkal, biztonsagi lepesket lezarja a tranz ket nevet \0-val es ezek segitsegevel kiszamolja a hash-et.
// Beallitja NULL-ra az azutani blokk mutatojat. lanc.c fileban definialt
// lanch_felszabadit() fuggvennyel szabaditja fel a hivo a memoirat, kivele a
// NULL visszateresi erteknel
Blokk *blokk_letrehoz(i32 sorszam, const char *idobelyeg, const Tranzakcio *tranz, u64 hash_elozo) {
    Blokk *blokk = malloc(sizeof(Blokk));
    if (blokk == NULL) return NULL;

    blokk->sorszam = sorszam;
    blokk->hash_elozo = hash_elozo;
    blokk->kovetkezo = NULL;
    blokk->tranz = *tranz;
    blokk->tranz.kuldo[NEV_MERET - 1] = '\0';
    blokk->tranz.cimzett[NEV_MERET - 1] = '\0';
    snprintf(blokk->idobelyeg, sizeof(blokk->idobelyeg), "%s", idobelyeg);

    blokk->hash = hash_szamol(blokk);
    return blokk;
}
