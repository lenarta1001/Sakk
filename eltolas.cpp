#include "eltolas.h"

Eltolas Eltolas::operator*(double c) const {
    return Eltolas(c * dsor, c * doszlop);
}


Eltolas Eltolas::operator+(const Eltolas& e) const {
    return Eltolas(dsor + e.dsor, doszlop + e.doszlop);
}

Eltolas Eltolas::del = Eltolas(1, 0);
Eltolas Eltolas::kelet = Eltolas(0, 1);
Eltolas Eltolas::eszak = Eltolas(-1, 0);
Eltolas Eltolas::nyugat = Eltolas(0, -1);
Eltolas Eltolas::eszakkelet = eszak + kelet;
Eltolas Eltolas::eszaknyugat = eszak + nyugat;
Eltolas Eltolas::delkelet = del + kelet;
Eltolas Eltolas::delnyugat = del + nyugat;