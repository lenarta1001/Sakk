#include "poz.h"
#include "eltolas.h"

Poz Poz::operator+(const Eltolas &e) const {
    return Poz(sor + e.dsor, oszlop + e.doszlop);
}

Poz &Poz::operator+=(const Eltolas &e) {
    *this = *this + e;
    return *this;
}

bool Poz::operator==(const Poz &p) const {
    return sor == p.sor && oszlop == p.oszlop;
}

bool Poz::operator!=(const Poz &p) const
{
    return !(*this == p);
}
