#include <iostream>
#include <vector>

#include "babu.h"
#include "eltolas.h"
#include "poz.h"
#include "lepes.h"
#include "szin.h"
#include "tabla.h"

Lepesek Paraszt::lepesek(const Poz &kezdo, Tabla &tabla) {
    Lepesek elerhetok;
    Eltolas irany = szin == Szin::feher ? Eltolas::eszak : Eltolas::del;

    Poz kovetkezo = kezdo + irany;
    if (tabla.benne_van(kovetkezo) && tabla.ures(kovetkezo)) {
        elerhetok.push_back(new NormalLepes(kezdo, kovetkezo));
        Poz kettos = kovetkezo + irany;
        if (!mozgott && tabla.benne_van(kettos) && tabla.ures(kettos) && tabla.benne_van(kettos))
            elerhetok.push_back(new NormalLepes(kezdo, kettos));
    }


    Poz egyik_oldal = kovetkezo + Eltolas::kelet;
    Poz masik_oldal = kovetkezo + Eltolas::nyugat;
    if (tabla.benne_van(egyik_oldal) && !tabla.ures(egyik_oldal) && tabla[egyik_oldal]->get_szin() != szin)
        elerhetok.push_back(new NormalLepes(kezdo, egyik_oldal));

    if (tabla.benne_van(masik_oldal) && !tabla.ures(masik_oldal) && tabla[masik_oldal]->get_szin() != szin)
        elerhetok.push_back(new NormalLepes(kezdo, masik_oldal));

    return elerhetok;
}

Lepesek Bastya::lepesek(const Poz &kezdo, Tabla &tabla) {
    Lepesek elerhetok;
    Eltolas iranyok[4] = {Eltolas::eszak, Eltolas::kelet, Eltolas::del, Eltolas::nyugat};

    for (int i = 0; i < 4; i++) {
        for (Poz p = kezdo + iranyok[i]; tabla.benne_van(p); p += iranyok[i]) {
            if (tabla.ures(p)) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else if (tabla[p]->get_szin()  != szin) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else {
                break;
            }
        }
    }

    return elerhetok;
}

Lepesek Futo::lepesek(const Poz& kezdo, Tabla& tabla) {
    Lepesek elerhetok;
    Eltolas iranyok[4] = {Eltolas::eszakkelet, Eltolas::delkelet, Eltolas::delnyugat, Eltolas::eszaknyugat};

    for (int i = 0; i < 4; i++) {
        for (Poz p = kezdo + iranyok[i]; tabla.benne_van(p); p += iranyok[i]) {
            if (tabla.ures(p)) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else if (tabla[p]->get_szin() != szin) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else {
                break;
            }
        }
    }

    return elerhetok;
}

Lepesek Kiralyno::lepesek(const Poz& kezdo, Tabla& tabla) {
    Lepesek elerhetok;
    Eltolas iranyok[8] = {Eltolas::eszak, Eltolas::eszakkelet, Eltolas::kelet, Eltolas::delkelet, Eltolas::del, Eltolas::delnyugat, Eltolas::nyugat, Eltolas::eszaknyugat};

    for (int i = 0; i < 8; i++) {
        for (Poz p = kezdo + iranyok[i]; tabla.benne_van(p); p += iranyok[i]) {
            if (tabla.ures(p)) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else if (tabla[p]->get_szin() != szin) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else {
                break;
            }
        }
    }

    return elerhetok;
}

Lepesek Huszar::lepesek(const Poz& kezdo, Tabla& tabla) {
    Lepesek elerhetok;
    Eltolas vizszintes[2] = {Eltolas::kelet, Eltolas::nyugat};
    Eltolas fuggoleges[2] = {Eltolas::eszak, Eltolas::del};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            Poz veg = kezdo + vizszintes[i] * 2 + fuggoleges[j];
            if (tabla.benne_van(veg) && (tabla.ures(veg) || tabla[veg]->get_szin() != szin)) {
                elerhetok.push_back(new NormalLepes(kezdo, veg));
            }

            veg = kezdo + fuggoleges[i] * 2 + vizszintes[j];
            if (tabla.benne_van(veg) && (tabla.ures(veg) || tabla[veg]->get_szin() != szin)) {
                elerhetok.push_back(new NormalLepes(kezdo, veg));
            }
        }
    }
    return elerhetok;
}

Lepesek Kiraly::lepesek(const Poz& kezdo, Tabla& tabla) {
    Lepesek elerhetok;
    Eltolas iranyok[8] = {Eltolas::eszak, Eltolas::eszakkelet, Eltolas::kelet, Eltolas::delkelet, Eltolas::del, Eltolas::delnyugat, Eltolas::nyugat, Eltolas::eszaknyugat};
    for (int i = 0; i < 8; i++) {
        Poz veg = kezdo + iranyok[i];
        if (tabla.benne_van(veg) && (tabla.ures(veg) || tabla[veg]->get_szin() != szin))
            elerhetok.push_back(new NormalLepes(kezdo, veg));
    }

    return elerhetok;
}

int main() {
    return 0;
}
