#ifndef POZ_H
#define POZ_H


#include "szin.h"
#include "eltolas.h"

class Poz {
public:
    int sor;
    int oszlop;
    Poz(int s = -1, int o = -1) : sor(s), oszlop(o) {}
    Szin szin() { return (sor + oszlop) % 2 == 0 ? Szin::feher : Szin::fekete; }
    Poz operator+(const Eltolas& e) const;
    Poz& operator+=(const Eltolas& e);
    bool operator==(const Poz& p) const;
    bool operator!=(const Poz& p) const;
};

#endif // POZ_H
