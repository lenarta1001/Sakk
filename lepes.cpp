#include "lepes.h"
#include "tabla.h"
#include "babu.h"
#include "jatekos.h"

void NormalLepes::elvegez(Tabla &t) const {
    Babu* babu = t[kezdo];
    delete t[veg];
    t[veg] = babu;
    t[kezdo] = nullptr;
}

bool Lepes::ervenyes(Tabla& tabla) const {
    Tabla masolat = tabla;
    Jatekos akt(tabla[kezdo]->get_szin());
    elvegez(masolat);
    return !masolat.sakkban_van(akt);
}

void ParasztAtvaltozas::elvegez(Tabla& t) const {
    delete t[veg];
    t[veg] = mive->copy();
    t[kezdo] = nullptr;
}

ParasztAtvaltozas::ParasztAtvaltozas(const ParasztAtvaltozas& p) : Lepes(p.kezdo, p.veg), mive(p.mive->copy()) { }

Lepes* ParasztAtvaltozas::copy() {
    return new ParasztAtvaltozas(kezdo, veg, mive->copy());
}

ParasztAtvaltozas::~ParasztAtvaltozas() {
    delete mive;
}
