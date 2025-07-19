#ifndef SZAMOLO_H
#define SZAMOLO_H

#include <iostream>
#include <map>
#include <vector>

#include "babu.h"

class Jatekos;

class Szamolo {
    std::map<BabuTipus, size_t> feher_babutipusok_szama;
    std::map<BabuTipus, size_t> fekete_babutipusok_szama;
    size_t osszes;
public:
    Szamolo();
    void novel(const Jatekos& j, BabuTipus babutipus);
    size_t mennyi_feher(BabuTipus babutipus);
    size_t mennyi_fekete(BabuTipus babutipus);
    size_t get_osszes() { return osszes; }
};

#endif // SZAMOLO_H
