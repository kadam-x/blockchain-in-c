#ifndef BLOKK_H
#define BLOKK_H

#include <stdint.h>
#include <stdbool.h>

typedef int32_t i32; 
typedef uint64_t u64;

#define NEV_MERET 61 // 30 karakter a leghosszabb nev + \0
#define IDOBELYEG_MERET 20 // "EEEE-HH-NN OO:PP:MM" + \0

typedef struct Tranzakcio {
    char kuldo[NEV_MERET];
    char cimzett[NEV_MERET];
    i32 osszeg; // 1-1 000 000 kozotti szam, eleg az i32
}Tranzakcio;

typedef struct Blokk {
    i32 sorszam;
    char idobelyeg[IDOBELYEG_MERET];
    Tranzakcio tranz;
    u64 hash_elozo; // fajlban tarolt ertek, ez lesz osszevetve az ellenorzesnel
    u64 hash;
    struct Blokk *kovetkezo;
}Blokk;

Blokk *blokk_letrehoz(i32 sorszam, const char *idobelyeg, const Tranzakcio *tranz, u64 hash_elozo);

bool blokk_hash_egyezik(const Blokk *blokk);

void idobelyeg_most(char cel[IDOBELYEG_MERET]);

#endif
