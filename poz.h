#ifndef POZ_H
#define POZ_H


#include "szin.h"
#include "eltolas.h"

class Poz {
    unsigned sor;
    unsigned oszlop;
public:
    Poz(unsigned s, unsigned o) : sor(s), oszlop(o) {}
    unsigned get_sor() const { return sor; }
    unsigned get_oszlop() const { return oszlop; }
    Szin szin() { return (sor + oszlop) % 2 == 0 ? Szin::feher : Szin::fekete; }
    Poz operator+(const Eltolas& e) const;
    Poz& operator+=(const Eltolas& e);
    bool operator==(const Poz& p) const;
    bool operator!=(const Poz& p) const;
};

#endif // POZ_H
