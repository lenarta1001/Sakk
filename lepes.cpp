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

void KiralyOldaliSanc::elvegez(Tabla& tabla) {
    NormalLepes kiraly_lepes(kezdo, veg);
    kiraly_lepes.elvegez();
    NormalLepes bastya_lepes(bastya_kezdo, bastya_veg);
    bastya_lepes.elvegez();
}

void KiralynoOldaliSanc::elvegez(Tabla& tabla) {
    NormalLepes kiraly_lepes(kezdo, veg);
    kiraly_lepes.elvegez();
    NormalLepes bastya_lepes(bastya_kezdo, bastya_veg);
    bastya_lepes.elvegez();
}

bool KiralynoOldaliSanc::ervenyes(Tabla& tabla) const {
    Tabla masolat = tabla;
    Poz mozgo_kiraly = kezdo;
    Jatekos akt_jatekos = tabla[kezdo]->get_szin();

    if (tabla.sakkban_van(akt_jatekos))
        return false;

    for (int i = 0; i < 2; i++) {
        NormalLepes(mozgo_kiraly, mozgo_kiraly + irany).elvegez(masolat);
        if (masolat.sakkban_van(akt_jatekos))
            return false;
        mozgo_kiraly += irany;
    }

    return false;
}

bool KiralyOldaliSanc::ervenyes(Tabla& tabla) const {
    Tabla masolat = tabla;
    Poz mozgo_kiraly = kezdo;
    Jatekos akt_jatekos = tabla[kezdo]->get_szin();

    if (tabla.sakkban_van(akt_jatekos))
        return false;

    for (int i = 0; i < 2; i++) {
        NormalLepes(mozgo_kiraly, mozgo_kiraly + irany).elvegez(masolat);
        if (masolat.sakkban_van(akt_jatekos))
            return false;
        mozgo_kiraly += irany;
    }

    return false;
}


