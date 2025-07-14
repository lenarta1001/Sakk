#ifndef JATEKALLAS_H
#define JATEKALLAS_H

#include "babu.h"
#include "tabla.h"
#include "szin.h"
#include "jatekos.h"
#include "lepes.h"

class Poz;


class JatekAllas {
    Jatekos akt_jatekos;
    Tabla tabla;
public:
    JatekAllas(Jatekos j, const Tabla& t) : akt_jatekos(j), tabla(t) {}
    Lepesek ervenyes_lepesek(const Poz& p);
    void lep(Lepes* l); 
};

#endif // JATEKALLAS_H