#include "jatekallas.h"
#include "tabla.h"
#include "poz.h"
#include "lepes.h"
#include "babu.h"

void JatekAllas::fenstring_frissit() {
    fenstring = FenString(akt_jatekos, tabla).get_s();
    if (korabbi_fenstringek.count(fenstring) == 0)
        korabbi_fenstringek[fenstring] = 1;
    else
        korabbi_fenstringek[fenstring]++;
}

Lepesek JatekAllas::ervenyes_lepesek(const Poz &p)
{
    if (!tabla.benne_van(p) || tabla.ures(p) || tabla[p]->get_szin() != akt_jatekos.szin) {
        return Lepesek(0);
    }
    Lepesek lehetseges_lepesek = tabla[p]->lepesek(p, tabla);
    Lepesek valid_lepesek;
    for (auto& lepes : lehetseges_lepesek) {
        if (lepes->ervenyes(tabla))
            valid_lepesek.push_back(lepes->copy());
    }
    return valid_lepesek;
}

void JatekAllas::lep(Lepes* l) {
    tabla.del_atugrott_pozicio(akt_jatekos);
    l->elvegez(tabla);
    if (l->parasztlepes_utes(tabla)) {
        korabbi_fenstringek.clear();
        otvenlepes_szabaly_szamlalo = 0;
    } else
        otvenlepes_szabaly_szamlalo++;

    akt_jatekos = akt_jatekos.ellenfel();
    fenstring_frissit();
    vege_ellenorzes();
}

Lepesek JatekAllas::osszes_ervenyes_lepes(const Jatekos &jatekos) {
    std::vector<Poz> poziciok = tabla.egyszinu_babuk_pozicioja(jatekos);
    Lepesek osszes;
    for (auto poz : poziciok) {
        Lepesek egy_babu_lepesei = ervenyes_lepesek(poz);
        for (auto& lepes : egy_babu_lepesei) {
            osszes.push_back(lepes->copy());
        }
    }
    return osszes;
}

void JatekAllas::vege_ellenorzes() {
    if (osszes_ervenyes_lepes(akt_jatekos).empty()) {
        if (tabla.sakkban_van(akt_jatekos))
            eredmeny = Eredmeny(akt_jatekos.ellenfel(), akt_jatekos.ellenfel().nev() + " NYERT", "SAKKMATT" );
        else
            eredmeny = Eredmeny(none, "DÖNTETLEN", "PATT");
        vege = true;
    } else if (tabla.elegtelen_anyag()) {
        vege = true;
        eredmeny = Eredmeny(none, "DÖNTETLEN", "ELÉGTELEN ANYAG");
    } else if (otvenlepes_szabaly_szamlalo >= 100) {
        vege = true;
        eredmeny = Eredmeny(none, "DÖNTETLEN", "ÖTVENLÉPÉSES SZABÁLY");
    } else if (korabbi_fenstringek[fenstring] >= 3) {
        vege = true;
        eredmeny = Eredmeny(none, "DÖNTETLEN", "HÁROMSZORI ÁLLÁSISMÉTLÉS");
    }
}
