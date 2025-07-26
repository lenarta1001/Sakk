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
        if (kovetkezo.sor == 0 || kovetkezo.sor == 7) {
            elerhetok.push_back(new ParasztAtvaltozas(kezdo, kovetkezo, new Kiralyno(get_szin(), true)));
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
            if (atlos.sor == 0 || atlos.sor == 7) {
                elerhetok.push_back(new ParasztAtvaltozas(kezdo, atlos, new Kiralyno(get_szin(), true)));
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

    for (auto& lepes : elore) {
        osszes.push_back(lepes->copy());
    }
    for (auto& lepes : atlosan) {
        osszes.push_back(lepes->copy());
    }  

    return osszes;
}

Lepesek Bastya::lepesek(const Poz &kezdo, Tabla &tabla) const {
    Lepesek elerhetok;
    Eltolas iranyok[4] = {Eltolas::eszak, Eltolas::kelet, Eltolas::del, Eltolas::nyugat};

    for (auto irany : iranyok) {
        for (Poz p = kezdo + irany; tabla.benne_van(p); p += irany) {
            if (tabla.ures(p)) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else if (tabla[p]->get_szin()  != szin) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
                break;
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

    for (auto irany : iranyok) {
        for (Poz p = kezdo + irany; tabla.benne_van(p); p += irany) {
            if (tabla.ures(p)) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else if (tabla[p]->get_szin() != szin) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
                break;
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

    for (auto irany : iranyok) {
        for (Poz p = kezdo + irany; tabla.benne_van(p); p += irany) {
            if (tabla.ures(p)) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
            } else if (tabla[p]->get_szin() != szin) {
                elerhetok.push_back(new NormalLepes(kezdo, p));
                break;
            } else {
                break;
            }
        }
    }

    return elerhetok;
}

Lepesek Huszar::lepesek(const Poz& kezdo, Tabla& tabla) const {
    Lepesek elerhetok;
    Eltolas vizszintesek[2] = {Eltolas::kelet, Eltolas::nyugat};
    Eltolas fuggolegesek[2] = {Eltolas::eszak, Eltolas::del};

    for (auto vizszintes : vizszintesek) {
        for (auto fuggoleges : fuggolegesek) {
            Poz veg = kezdo + vizszintes * 2 + fuggoleges;
            if (tabla.benne_van(veg) && (tabla.ures(veg) || tabla[veg]->get_szin() != szin)) {
                elerhetok.push_back(new NormalLepes(kezdo, veg));
            }

            veg = kezdo + fuggoleges * 2 + vizszintes;
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
    for (auto irany : iranyok) {
        Poz veg = kezdo + irany;
        if (tabla.benne_van(veg) && (tabla.ures(veg) || tabla[veg]->get_szin() != szin))
            elerhetok.push_back(new NormalLepes(kezdo, veg));
    }
    if (sancolhat_kiraly_oldalon(kezdo, tabla))
        elerhetok.push_back(new KiralyOldaliSanc(kezdo));
    if (sancolhat_kiralyno_oldalon(kezdo, tabla))
        elerhetok.push_back(new KiralynoOldaliSanc(kezdo));

    return elerhetok;
}

bool Kiraly::sancolhat_kiraly_oldalon(Poz kezdo, Tabla &tabla) const {
    std::vector<Poz> poziciok = { Poz(kezdo.sor, 5), Poz(kezdo.sor, 6)  };
    Poz bastya_poz(kezdo.sor, 7);

    return !mozgott && tabla.uresek(poziciok) && !tabla.ures(bastya_poz) && !tabla[bastya_poz]->mozgott;
}

bool Kiraly::sancolhat_kiralyno_oldalon(Poz kezdo, Tabla &tabla) const {
    std::vector<Poz> poziciok = { Poz(kezdo.sor, 1), Poz(kezdo.sor, 2), Poz(kezdo.sor, 3)  };
    Poz bastya_poz(kezdo.sor, 0);

    return !mozgott && tabla.uresek(poziciok) && !tabla.ures(bastya_poz) && !tabla[bastya_poz]->mozgott;
}

bool Babu::uti_a_kiralyt(const Poz& poz, Tabla& tabla) const {
    Lepesek lehetseges_lepesek = lepesek(poz, tabla);
    for (auto lepes : lehetseges_lepesek) {
        Poz veg = lepes->veg;
        if (tabla[veg] != nullptr && tabla[veg]->get_tipus() == kiraly) {
            return true;
        }
    }
    return false;
}

bool Paraszt::uti_a_kiralyt(const Poz& poz, Tabla& tabla) const {
    Lepesek atlosan = atlos_lepesek(poz, tabla);
    for (auto lepes : atlosan) {
        Poz veg = lepes->veg;
        if (tabla[veg] != nullptr && tabla[veg]->get_tipus() == kiraly) {
            return true;
        }
    }
    return false;
}
