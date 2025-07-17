#ifndef TABLA_H
#define TABLA_H

#include <iostream>
#include <vector>
#include <map>

#include "jatekos.h"

class Babu;
class Poz;
class Jatekos;

class Tabla {
    std::vector<std::vector<Babu*>> tabla;
    std::map<Jatekos, Poz> atugrott_poziciok;
public:
    Tabla();
    Tabla(const Tabla&);
    Babu* operator[](const Poz& p) const;
    Babu*& operator[](const Poz& p);
    void init();
    void set_atugrott_pozicio(const Jatekos& j, Poz p);
    void del_atugrott_pozicio(const Jatekos& j);
    Poz& get_atugrott_pozicio(const Jatekos& j);
    bool ures(const Poz& p) const;
    bool benne_van(const Poz& p) const;
    std::vector<Poz> babuk_pozicioja() const;
    std::vector<Poz> egyszinu_babuk_pozicioja(const Jatekos &jatekos) const;
    bool uresek(std::vector<Poz> poziciok);
    bool sakkban_van(const Jatekos &j);
    ~Tabla();
};
#endif // TABLA_H
