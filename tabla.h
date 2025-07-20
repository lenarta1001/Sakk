#ifndef TABLA_H
#define TABLA_H

#include <iostream>
#include <vector>
#include <map>

#include "jatekos.h"
#include "babu.h"

class Babu;
class Poz;
class Jatekos;
class Szamolo;

class Tabla {
    std::vector<std::vector<Babu*>> tabla;
    std::map<Jatekos, Poz> atugrott_poziciok;
public:
    Tabla();
    Tabla(const Tabla&);
    Babu* operator[](const Poz& p) const;
    Babu*& operator[](const Poz& p);
    Babu* operator() (unsigned s, unsigned o) const;
    Babu*& operator() (unsigned s, unsigned o);
    static Tabla init();
    void set_atugrott_pozicio(const Jatekos& j, Poz p);
    void del_atugrott_pozicio(const Jatekos& j);
    Poz& get_atugrott_pozicio(const Jatekos& j);
    bool ures(const Poz& p) const;
    bool benne_van(const Poz& p) const;
    std::vector<Poz> babuk_pozicioja() const;
    std::vector<Poz> egyszinu_babuk_pozicioja(const Jatekos &jatekos) const;
    bool uresek(std::vector<Poz> poziciok);
    bool sakkban_van(const Jatekos &j);
    Szamolo babuk_szama_tipusonkent();
    bool elegtelen_anyag();
    bool KiralyvsKiraly();
    bool KiralyvsKiralyFuto();
    bool KiralyvsKiralyHuszar();
    bool KiralyFutovsKiralyFuto();
    Poz holvan(BabuTipus babutipus, const Szin& szin);
    bool kiralyoldali_sanc_jog(const Jatekos &j) const;
    bool kiralynooldali_sanc_jog(const Jatekos &j) const;
    bool enpassant_jog(const Jatekos& j);

    ~Tabla();
};
#endif // TABLA_H
