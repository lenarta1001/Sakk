#ifndef TABLA_H
#define TABLA_H

#include <iostream>
#include <vector>

#include "poz.h"
#include "babu.h"

class Babu;
class Poz;

class Tabla {
    std::vector<std::vector<Babu*>> tabla;
public:
    Tabla();
    Babu*& operator[](const Poz& p);
    void init();
    bool ures(const Poz& p) const;
    bool benne_van(const Poz& p) const;
    ~Tabla();
};
#endif // TABLA_H