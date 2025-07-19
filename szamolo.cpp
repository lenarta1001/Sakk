#include "szamolo.h"
#include "jatekos.h"
#include "szin.h"
#include "babu.h"

size_t Szamolo::mennyi_feher(BabuTipus babutipus) {
    return feher_babutipusok_szama[babutipus];
}

size_t Szamolo::mennyi_fekete(BabuTipus babutipus) {
    return fekete_babutipusok_szama[babutipus];
}

Szamolo::Szamolo() : osszes(0) {
    std::vector<BabuTipus> babutipusok = { kiraly, kiralyno, futo, huszar, bastya, paraszt };
    for (size_t i = 0; i < babutipusok.size(); i++) {
        feher_babutipusok_szama[babutipusok[i]] = 0;
        fekete_babutipusok_szama[babutipusok[i]] = 0;
    }
}


void Szamolo::novel(const Jatekos &j, BabuTipus babutipus)
{
    if (j.szin == feher)
        feher_babutipusok_szama[babutipus]++;
    else
        fekete_babutipusok_szama[babutipus]++;

    osszes++;
}