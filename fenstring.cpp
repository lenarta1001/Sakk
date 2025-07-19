#include "fenstring.h"
#include "tabla.h"
#include "poz.h"
#include <iostream>
#include <sstream>

void FenString::babu_poziciok_hozzafuzese(const Tabla& tabla) {
    for (size_t i = 0; i < 8; i++) {
        if (i != 0)
            fenstring.append("/");

        int ures_db = 0;
        for (size_t j = 0; j < 8; j++) {
            if (tabla.ures(Poz(i, j))) {
                ures_db++;
            } else {
                char fen_ch = tabla(i, j)->fen_char();
                if (ures_db != 0) {
                    fenstring += std::to_string(ures_db);
                    ures_db = 0;
                }
                fenstring += std::to_string(fen_ch);
            }
        }
        if (ures_db > 0) {
            fenstring += std::to_string(ures_db);
        }
    }
}

void FenString::akt_jatekos_hozzafuzese(const Jatekos &jatekos) {
    if (jatekos.szin == feher) {
        fenstring += std::to_string('w');
    } else {
        fenstring += std::to_string('b');
    }

}

void FenString::sanc_jog_hozzafuzes(const Tabla &tabla) {
    bool kiralyoldali_feher = tabla.kiralyoldali_sanc_jog(Jatekos(feher));
    bool kiralynooldali_feher = tabla.kiralynooldali_sanc_jog(Jatekos(feher));
    bool kiralyoldali_fekete = tabla.kiralyoldali_sanc_jog(Jatekos(fekete));
    bool kiralynooldali_fekete = tabla.kiralynooldali_sanc_jog(Jatekos(fekete));

    if (!(kiralyoldali_feher || kiralynooldali_feher || kiralyoldali_fekete || kiralynooldali_fekete))
        fenstring += std::to_string('-');

    if (kiralyoldali_feher)
        fenstring += std::to_string('K');

    if (kiralynooldali_feher)
        fenstring += std::to_string('Q');

    if (kiralyoldali_fekete)
        fenstring += std::to_string('k');

    if (kiralynooldali_fekete)
        fenstring += std::to_string('q');
}

void FenString::enpassant_jog_hozzafuzes(Tabla &tabla, const Jatekos& jatekos) {
    if (!tabla.enpassant_jog(jatekos)) {
        fenstring += std::to_string('-');
    } else {
        Poz atugrott = tabla.get_atugrott_pozicio(jatekos.ellenfel());
        char oszlop = (char)atugrott.get_oszlop() + 'a';
        int sor = 8 - atugrott.get_sor();
        fenstring += std::to_string(oszlop) + std::to_string(sor);
    }
}
