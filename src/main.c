#include <stdio.h> 
#include <stdlib.h>
#include <inttypes.h>

#include "blokk.h"
#include "../lib/debugmalloc.h"


// Tesztkent megirt main
int main(void) {
    Tranzakcio t;
    snprintf(t.kuldo, sizeof(t.kuldo), "%s", "SYSTEM");
    snprintf(t.cimzett, sizeof(t.kuldo), "%s", "TESzT");
    t.osszeg = 500000;
    char ido[IDOBELYEG_MERET];
    idobelyeg_most(ido);
    Blokk *b0 = blokk_letrehoz(0, ido, &t, 0);
    if (b0 == NULL) {
        printf("Nem sikerult blokkot letrehozni\n");
        return -1;
    }
    printf("Blokk letrehozva\n");
    printf("A blokk sorszama: %d, az idobelyeg: %s, a kuldo neve: %s, a cimzett neve: %s, az osszeg: %d\n", b0->sorszam, b0->idobelyeg, b0->tranz.kuldo, b0->tranz.cimzett, b0->tranz.osszeg);
    printf("A blokk egyezik: %s\n", blokk_hash_egyezik(b0) ? "igen" : "nem");
    printf("A hash: %016" PRIx64 "\n", b0->hash);
    
    printf("\n\n");
    
    printf("A tranzakcio osszege kezi atirasa 1-re\n");
    b0->tranz.osszeg = 1;
    printf("A blokk egyezik: %s\n", blokk_hash_egyezik(b0) ? "igen" : "nem");
    free(b0);



    return 0;
}
