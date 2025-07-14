#include "lepes.h"
#include "tabla.h"
#include "babu.h"
#include "jatekos.h"

void NormalLepes::elvegez(Tabla &t) const {
    Babu* babu = t[kezdo];
    delete t[veg];
    t[veg] = babu;
    t[kezdo] = babu;
}

bool Lepes::ervenyes(Tabla& tabla) const {
    Tabla masolat = tabla;
    Jatekos akt(tabla[kezdo]->get_szin());
    elvegez(masolat);
    return !masolat.sakkban_van(akt);
}
