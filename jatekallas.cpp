#include "jatekallas.h"
#include "tabla.h"
#include "poz.h"
#include "lepes.h"

Lepesek JatekAllas::ervenyes_lepesek(const Poz& p) {
    if (!tabla.benne_van(p) || tabla[p]->get_szin() != akt_jatekos.szin) {
        return Lepesek(0);
    }
    return tabla[p]->lepesek(p, tabla);
}

void JatekAllas::lep(Lepes* l) {
    l->elvegez(tabla);
    akt_jatekos = akt_jatekos.ellenfel();
}
