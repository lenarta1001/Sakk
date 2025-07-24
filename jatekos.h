#ifndef JATEKOS_H
#define JATEKOS_H

#include "szin.h"

struct Jatekos {
    Szin szin;
    Jatekos(Szin sz) : szin(sz) {}
    Jatekos ellenfel() const { return szin == Szin::feher ? Jatekos(Szin::fekete) : Jatekos(Szin::feher); }
    std::string nev() const { return szin == feher ? "FEHÉR" : "FEKETE"; }
    bool operator<(const Jatekos& rhs_j) const { return (int)szin < (int)rhs_j.szin; }
    bool operator>(const Jatekos& rhs_j) const { return (int)szin > (int)rhs_j.szin; }
};

#endif // JATEKOS_H
