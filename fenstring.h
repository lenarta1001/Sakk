#ifndef FENSTRING_H
#define FENSTRING_H

#include <iostream>

class Jatekos;
class Tabla;

class FenString {
    std::string fenstring;
public:
    FenString(const Jatekos& jatekos, Tabla& tabla) {
        babu_poziciok_hozzafuzese(tabla);
        fenstring.append(" ");
        akt_jatekos_hozzafuzese(jatekos);
        fenstring.append(" ");
        sanc_jog_hozzafuzes(tabla);
        fenstring.append(" ");
        enpassant_jog_hozzafuzes(tabla, jatekos);
    }

    void babu_poziciok_hozzafuzese(const Tabla& tabla);
    void akt_jatekos_hozzafuzese(const Jatekos& jatekos);
    void sanc_jog_hozzafuzes(const Tabla& tabla);
    void enpassant_jog_hozzafuzes(Tabla &tabla, const Jatekos& jatekos);
    std::string get_s() { return fenstring; }
};

#endif // FENSTRING
