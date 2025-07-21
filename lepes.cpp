#include "lepes.h"
#include "tabla.h"
#include "babu.h"
#include "jatekos.h"

void NormalLepes::elvegez(Tabla &tabla) const {
    Babu* babu = tabla[kezdo];
    delete tabla[veg];
    babu->mozgott = true;
    tabla[veg] = babu;
    tabla[kezdo] = nullptr;
}

bool NormalLepes::parasztlepes_utes(Tabla& tabla) const {
    return !tabla.ures(veg) || tabla[kezdo]->get_tipus() == paraszt;
}

bool Lepes::ervenyes(Tabla& tabla) const {
    Tabla masolat = tabla;
    Jatekos akt(tabla[kezdo]->get_szin());
    elvegez(masolat);
    return !masolat.sakkban_van(akt);
}

void DuplaLepes::elvegez(Tabla& tabla) const {
    Jatekos akt_jatekos(tabla[kezdo]->get_szin());
    tabla.set_atugrott_pozicio(akt_jatekos, atugrott);
    NormalLepes(kezdo, veg).elvegez(tabla);
}

bool DuplaLepes::parasztlepes_utes(Tabla& tabla) const {
    return true;
}

bool ParasztAtvaltozas::parasztlepes_utes(Tabla& tabla) const {
    return true;
}

void ParasztAtvaltozas::elvegez(Tabla& tabla) const {
    delete tabla[veg];
    tabla[veg] = mive->copy();
    tabla[kezdo] = nullptr;
}

ParasztAtvaltozas::ParasztAtvaltozas(const ParasztAtvaltozas& p) : Lepes(p.kezdo, p.veg), mive(p.mive->copy()) { }

Lepes* ParasztAtvaltozas::copy() {
    return new ParasztAtvaltozas(kezdo, veg, mive->copy());
}

ParasztAtvaltozas::~ParasztAtvaltozas() {
    delete mive;
}

void KiralyOldaliSanc::elvegez(Tabla& tabla) const {
    NormalLepes kiraly_lepes(kezdo, veg);
    kiraly_lepes.elvegez(tabla);
    NormalLepes bastya_lepes(bastya_kezdo, bastya_veg);
    bastya_lepes.elvegez(tabla);
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

    return true;
}

bool KiralyOldaliSanc::parasztlepes_utes(Tabla& tabla) const {
    return false;
}

void KiralynoOldaliSanc::elvegez(Tabla& tabla) const {
    NormalLepes kiraly_lepes(kezdo, veg);
    kiraly_lepes.elvegez(tabla);
    NormalLepes bastya_lepes(bastya_kezdo, bastya_veg);
    bastya_lepes.elvegez(tabla);
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

    return true;
}

bool KiralynoOldaliSanc::parasztlepes_utes(Tabla& tabla) const {
    return false;
}

void EnPassant::elvegez(Tabla& tabla) const {
    delete tabla[leutott_poz];
    tabla[leutott_poz] = nullptr;
    NormalLepes(kezdo, veg).elvegez(tabla);
}

bool EnPassant::parasztlepes_utes(Tabla& tabla) const {
    return true;
}
