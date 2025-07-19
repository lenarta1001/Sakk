#ifndef JATEKALLAS_H
#define JATEKALLAS_H

#include <map>
#include <iostream>

#include "tabla.h"
#include "jatekos.h"
#include "eredmeny.h"
#include "fenstring.h"

class Lepes;
class Lepesek;
class Poz;


class JatekAllas {
    Jatekos akt_jatekos;
    Tabla tabla;
    Eredmeny eredmeny;
    size_t otvenlepes_szabaly_szamlalo;
    std::string fenstring;
    std::map<std::string, size_t> korabbi_fenstringek;
public:
    bool vege;
    JatekAllas(Jatekos j, Tabla& t) : akt_jatekos(j), tabla(t), otvenlepes_szabaly_szamlalo(0), vege(false) {
        fenstring = FenString(j, t).get_s();
        korabbi_fenstringek[fenstring] = 1;
    }
    void fenstring_frissit();
    Lepesek ervenyes_lepesek(const Poz& p);
    void lep(Lepes* l);
    Lepesek osszes_ervenyes_lepes(const Jatekos& jatekos);
    void vege_ellenorzes();
};

#endif // JATEKALLAS_H
