#ifndef JATEKALLAS_H
#define JATEKALLAS_H

#include "tabla.h"
#include "jatekos.h"
#include "eredmeny.h"

class Lepes;
class Lepesek;
class Poz;


class JatekAllas {
    Jatekos akt_jatekos;
    Tabla tabla;
    Eredmeny eredmeny;
    size_t otvenlepes_szabaly_szamlalo;  
public:
    bool vege;
    JatekAllas(Jatekos j, const Tabla& t) : akt_jatekos(j), tabla(t), vege(false), otvenlepes_szabaly_szamlalo(0) {}
    Lepesek ervenyes_lepesek(const Poz& p);
    void lep(Lepes* l);
    Lepesek osszes_ervenyes_lepes(const Jatekos& jatekos);
    void vege_ellenorzes();
};

#endif // JATEKALLAS_H