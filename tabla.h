#ifndef TABLA_H
#define TABLA_H

#include <iostream>
#include <vector>

class Babu;
class Poz;
class Jatekos;

class Tabla {
    std::vector<std::vector<Babu*>> tabla;
public:
    Tabla();
    Tabla(const Tabla&);
    Babu* operator[](const Poz& p) const;
    Babu*& operator[](const Poz& p);
    void init();
    bool ures(const Poz& p) const;
    bool benne_van(const Poz& p) const;
    std::vector<Poz> babuk_pozicioja() const;
    std::vector<Poz> egyszinu_babuk_pozicioja(const Jatekos &jatekos) const;
    bool sakkban_van(const Jatekos &j) const;
    ~Tabla();
};
#endif // TABLA_H
