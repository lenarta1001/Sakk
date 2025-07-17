#include "jatekallas.h"
#include "tabla.h"
#include "poz.h"
#include "lepes.h"
#include "babu.h"

Lepesek JatekAllas::ervenyes_lepesek(const Poz& p) {
    if (!tabla.benne_van(p) || tabla[p]->get_szin() != akt_jatekos.szin) {
        return Lepesek(0);
    }
    Lepesek lehetseges_lepesek = tabla[p]->lepesek(p, tabla);
    Lepesek valid_lepesek;
    for (size_t i = 0; i < lehetseges_lepesek.size(); i++) {
        if (lehetseges_lepesek[i]->ervenyes(tabla))
            valid_lepesek.push_back(lehetseges_lepesek[i]);
    }
    return valid_lepesek;
}

void JatekAllas::lep(Lepes* l) {
    tabla.del_atugrott_pozicio(akt_jatekos);
    l->elvegez(tabla);
    akt_jatekos = akt_jatekos.ellenfel();
    vege_ellenorzes();
}

Lepesek JatekAllas::osszes_ervenyes_lepes(const Jatekos &jatekos) {
    std::vector<Poz> poziciok = tabla.egyszinu_babuk_pozicioja(jatekos);
    Lepesek osszes;
    for (auto poz : poziciok) {
        Lepesek egy_babu_lepesei = ervenyes_lepesek(poz);
        osszes.insert(osszes.end(), egy_babu_lepesei.begin(), egy_babu_lepesei.end());
    }
    return osszes;
}

void JatekAllas::vege_ellenorzes() {
    if (osszes_ervenyes_lepes(akt_jatekos).empty()) {
        if (tabla.sakkban_van(akt_jatekos))
            eredmeny = Eredmeny(akt_jatekos.ellenfel(), "sakkmatt");
        else
            eredmeny = Eredmeny(none, "patt");
        vege = true;
    }
}
