#include <iostream>
#include <vector>

#include "babu.h"
#include "eltolas.h"
#include "poz.h"
#include "lepes.h"
#include "szin.h"
#include "tabla.h"
#include "jatekos.h"

Lepesek Paraszt::elore_lepesek(const Poz &kezdo, Tabla &tabla) const {
    Lepesek elerhetok;
    Poz kovetkezo = kezdo + irany;

    if (tabla.benne_van(kovetkezo) && tabla.ures(kovetkezo)) {
        if (kovetkezo.get_sor() == 0 || kovetkezo.get_sor() == 7) {
            elerhetok.push_back(new ParasztAtvaltozas(kezdo, kovetkezo, new Kiralyno(get_szin(), true)));
            elerhetok.push_back(new ParasztAtvaltozas(kezdo, kovetkezo, new Futo(get_szin(), true)));
            elerhetok.push_back(new ParasztAtvaltozas(kezdo, kovetkezo, new Huszar(get_szin(), true)));
            elerhetok.push_back(new ParasztAtvaltozas(kezdo, kovetkezo, new Bastya(get_szin(), true)));
        } else {
            elerhetok.push_back(new NormalLepes(kezdo, kovetkezo));
            Poz kettos = kovetkezo + irany;
            if (!mozgott && tabla.benne_van(kettos) && tabla.ures(kettos))
                elerhetok.push_back(new DuplaLepes(kezdo, kettos));
        }
    }

    return elerhetok;
}

Lepesek Paraszt::atlos_lepesek(const Poz &kezdo, Tabla &tabla) const {
    Lepesek elerhetok;

    Eltolas oldalsok[2] = { Eltolas::kelet,  Eltolas::nyugat };

    for (auto oldalso : oldalsok) {
        Poz atlos = kezdo + irany + oldalso;

        if (tabla.get_atugrott_pozicio(Jatekos(szin).ellenfel()) == atlos) {
            elerhetok.push_back(new EnPassant(kezdo, atlos));
        } else if (tabla.benne_van(atlos) && !tabla.ures(atlos) && tabla[atlos]->get_szin() != szin) {
            if (atlos.get_sor() == 0 || atlos.get_sor() == 7) {
                elerhetok.push_back(new ParasztAtvaltozas(kezdo, atlos, new Kiralyno(get_szin(), true)));
                elerhetok.push_back(new ParasztAtvaltozas(kezdo, atlos, new Futo(get_szin(), true)));
                elerhetok.push_back(new ParasztAtvaltozas(kezdo, atlos, new Huszar(get_szin(), true)));
                elerhetok.push_back(new ParasztAtvaltozas(kezdo, atlos, new Bastya(get_szin(), true)));
            } else {
                elerhetok.push_back(new NormalLepes(kezdo, atlos));
            }
        }
    }

    return elerhetok;
}

Lepesek Paraszt::lepesek(const Poz &kezdo, Tabla &tabla) const {
    Lepesek elore = elore_lepesek(kezdo, tabla);
    Lepesek atlosan = atlos_lepesek(kezdo, tabla);
    Lepesek osszes;

    osszes.insert(osszes.end(), elore.begin(), elore.end());
    osszes.insert(osszes.end(), atlosan.begin(), atlosan.end());

    return osszes;
}

Lepesek Bastya::lepesek(const Poz &kezdo, Tabla &tabla) const {
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

Lepesek Futo::lepesek(const Poz& kezdo, Tabla& tabla) const {
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

Lepesek Kiralyno::lepesek(const Poz& kezdo, Tabla& tabla) const {
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

Lepesek Huszar::lepesek(const Poz& kezdo, Tabla& tabla) const {
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

Lepesek Kiraly::lepesek(const Poz& kezdo, Tabla& tabla) const {
    Lepesek elerhetok;
    Eltolas iranyok[8] = {Eltolas::eszak, Eltolas::eszakkelet, Eltolas::kelet, Eltolas::delkelet, Eltolas::del, Eltolas::delnyugat, Eltolas::nyugat, Eltolas::eszaknyugat};
    for (int i = 0; i < 8; i++) {
        Poz veg = kezdo + iranyok[i];
        if (tabla.benne_van(veg) && (tabla.ures(veg) || tabla[veg]->get_szin() != szin))
            elerhetok.push_back(new NormalLepes(kezdo, veg));
    }
    if (sancolhat_kiraly_oldalon(kezdo, tabla))
        elerhetok.push_back(new KiralynoOldaliSanc(kezdo));
    if (sancolhat_kiralyno_oldalon(kezdo, tabla))
        elerhetok.push_back(new KiralynoOldaliSanc(kezdo));

    return elerhetok;
}

bool Kiraly::sancolhat_kiraly_oldalon(Poz kezdo, Tabla &tabla) const {
    std::vector<Poz> poziciok = { Poz(kezdo.get_sor(), 5), Poz(kezdo.get_sor(), 6)  };
    Poz bastya_poz(kezdo.get_sor(), 7);

    return !get_mozgott() && tabla.uresek(poziciok) && !tabla.ures(bastya_poz) && !tabla[bastya_poz]->get_mozgott();
}

bool Kiraly::sancolhat_kiralyno_oldalon(Poz kezdo, Tabla &tabla) const {
    std::vector<Poz> poziciok = { Poz(kezdo.get_sor(), 1), Poz(kezdo.get_sor(), 2), Poz(kezdo.get_sor(), 3)  };
    Poz bastya_poz(kezdo.get_sor(), 0);

    return !get_mozgott() && tabla.uresek(poziciok) && !tabla.ures(bastya_poz) && !tabla[bastya_poz]->get_mozgott();
}

bool Babu::uti_a_kiralyt(const Poz& poz, Tabla& tabla) const {
    Lepesek lehetseges_lepesek = lepesek(poz, tabla);
    for (size_t i = 0; i < lehetseges_lepesek.size(); i++) {
        Poz veg = lehetseges_lepesek[i]->veg;
        if (tabla[veg] != nullptr && tabla[veg]->kiraly_e()) {
                return true;
        }
    }
    return false;
}

bool Paraszt::uti_a_kiralyt(const Poz& poz, Tabla& tabla) const {
    Lepesek atlosan = atlos_lepesek(poz, tabla);
    for (size_t i = 0; i < atlosan.size(); i++) {
        Poz veg = atlosan[i]->veg;
        if (tabla[veg] != nullptr && tabla[veg]->kiraly_e()) {
            return true;
        }
    }
    return false;
}

int main() {
    return 0;
}
