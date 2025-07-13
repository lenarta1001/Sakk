#ifndef JATEKALLAS_H
#define JATEKALLAS_H

#include "babu.h"
#include "tabla.h"
#include "szin.h"

class JatekAllas {
    Szin akt_jatekos;
    Tabla tabla;
public:
    JatekAllas(Szin j, Tabla t) : akt_jatekos(j), tabla(t) {}

};

#endif // JATEKALLAS_H