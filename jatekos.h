#ifndef JATEKOS_H
#define JATEKOS_H

#include "szin.h"

struct Jatekos {
    Szin szin;
    Jatekos(Szin sz) : szin(sz) {}
    Jatekos ellenfel() { return szin == Szin::feher ? Jatekos(Szin::fekete) : Jatekos(Szin::feher); } 
};

#endif // JATEKOS_H