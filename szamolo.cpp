#include "szamolo.h"
#include "jatekos.h"
#include "szin.h"
#include "babu.h"


void Szamolo::novel(const Jatekos &j, BabuTipus babutipus) {
    if (j.szin == feher)
        feher_babutipusok_szama[babutipus]++;
    else
        fekete_babutipusok_szama[babutipus]++;

    osszes++;
}

size_t Szamolo::mennyi_feher(BabuTipus babutipus) {
    return feher_babutipusok_szama[babutipus];
}

size_t Szamolo::mennyi_fekete(BabuTipus babutipus) {
    return fekete_babutipusok_szama[babutipus];
}
