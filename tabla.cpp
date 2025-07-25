#include "tabla.h"
#include "babu.h"
#include "poz.h"
#include "jatekos.h"
#include "szamolo.h"
#include "eltolas.h"

Tabla::Tabla() : tabla(8, std::vector<Babu*>(8, nullptr))  {}

Tabla::~Tabla() {
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            delete tabla[i][j];
}

Tabla& Tabla::operator=(const Tabla& tabla) {
    if (this != &tabla) {
        for (size_t i = 0; i < 8; i++)
            for (size_t j = 0; j < 8; j++)
                delete this->tabla[i][j];
        
        for (size_t i = 0; i < 8; i++) {
            for (size_t j = 0; j < 8; j++) {
                if (!tabla.ures(Poz(i, j)))
                    this->tabla[i][j] = tabla.tabla[i][j]->copy();
                else
                    this->tabla[i][j] = nullptr;
            }
        }  
    }
    return *this;
}

Babu*& Tabla::operator[](const Poz& p) {
    return tabla[p.sor][p.oszlop];
}

Babu* Tabla::operator()(unsigned s, unsigned o) const {
    return tabla[s][o];
}

Babu* Tabla::operator[](const Poz& p) const {
    return tabla[p.sor][p.oszlop];
}

Babu*& Tabla::operator()(unsigned s, unsigned o)  {
    return tabla[s][o];
}

Tabla Tabla::init() {
    Tabla tabla;
    tabla.tabla[0][0] = new Bastya(fekete);
    tabla.tabla[0][1] = new Huszar(fekete);
    tabla.tabla[0][2] = new Futo(fekete);
    tabla.tabla[0][3] = new Kiralyno(fekete);
    tabla.tabla[0][4] = new Kiraly(fekete);
    tabla.tabla[0][5] = new Futo(fekete);
    tabla.tabla[0][6] = new Huszar(fekete);
    tabla.tabla[0][7] = new Bastya(fekete);

    tabla.tabla[7][0] = new Bastya(feher);
    tabla.tabla[7][1] = new Huszar(feher);
    tabla.tabla[7][2] = new Futo(feher);
    tabla.tabla[7][3] = new Kiralyno(feher);
    tabla.tabla[7][4] = new Kiraly(feher);
    tabla.tabla[7][5] = new Futo(feher);
    tabla.tabla[7][6] = new Huszar(feher);
    tabla.tabla[7][7] = new Bastya(feher);

    for (int i = 0; i < 8; i++) {
        tabla.tabla[1][i] = new Paraszt(fekete);
        tabla.tabla[6][i] = new Paraszt(feher);
    }
    return tabla;
}

void Tabla::set_atugrott_pozicio(const Jatekos &j, Poz poz) {
    atugrott_poziciok[j] = poz;
}

void Tabla::del_atugrott_pozicio(const Jatekos &j) {
    atugrott_poziciok.erase(j);
}

Poz &Tabla::get_atugrott_pozicio(const Jatekos &j)
{
    return atugrott_poziciok[j];
}

bool Tabla::ures(const Poz& p) const {
    return tabla[p.sor][p.oszlop] == nullptr;
}

bool Tabla::benne_van(const Poz& p) const {
    return p.sor >= 0 && p.sor < 8 &&  p.oszlop >= 0 && p.oszlop < 8;
}

std::vector<Poz> Tabla::babuk_pozicioja() const {
    std::vector<Poz> poziciok;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Poz p = Poz(i, j);
            if (!ures(p))
                poziciok.push_back(p);
        }
    }
    return poziciok;
}

std::vector<Poz> Tabla::egyszinu_babuk_pozicioja(const Jatekos& jatekos) const {
    std::vector<Poz> poziciok;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Poz p = Poz(i, j);
            if (!ures(p) && operator[](p)->get_szin() == jatekos.szin)
                poziciok.push_back(p);
        }
    }
    return poziciok;
}

bool Tabla::uresek(std::vector<Poz> poziciok) {
    for (size_t i = 0; i < poziciok.size(); i++) {
        if (!ures(poziciok[i]))
            return false;
    }
    return true;
}

bool Tabla::sakkban_van(const Jatekos &j) {
    std::vector<Poz> ellenseges_poz = egyszinu_babuk_pozicioja(j.ellenfel());
    for (auto poz : ellenseges_poz) {
        if(operator[](poz)->uti_a_kiralyt(poz, *this))
            return true;
    }
    return false;
}

Szamolo Tabla::babuk_szama_tipusonkent() {
    Szamolo babuk_szama;
    std::vector<Poz> poziciok = babuk_pozicioja();
    for (auto poz : poziciok) {
        Babu* babu = operator[](poz);
        babuk_szama.novel(Jatekos(babu->get_szin()), babu->get_tipus());
    }
    return babuk_szama;
}

bool Tabla::elegtelen_anyag() {
    return KiralyvsKiraly() || KiralyFutovsKiralyFuto() || KiralyvsKiralyFuto() || KiralyvsKiralyHuszar();
}


bool Tabla::KiralyvsKiraly() {
    Szamolo sz = babuk_szama_tipusonkent();
    return sz.get_osszes() == 2;
}

bool Tabla::KiralyvsKiralyFuto() {
    Szamolo sz = babuk_szama_tipusonkent();
    return sz.get_osszes() == 3 && (sz.mennyi_feher(futo) == 1 || sz.mennyi_fekete(futo) == 1);
}

bool Tabla::KiralyvsKiralyHuszar() {
    Szamolo sz = babuk_szama_tipusonkent();
    return sz.get_osszes() == 3 && (sz.mennyi_feher(huszar) == 1 || sz.mennyi_fekete(huszar) == 1);
}

bool Tabla::KiralyFutovsKiralyFuto() {
    Szamolo sz = babuk_szama_tipusonkent();

    if (sz.get_osszes() != 4 || sz.mennyi_feher(huszar) != 1 || sz.mennyi_fekete(huszar) != 1)
        return false;

    Poz feher_futo = holvan(futo, feher);
    Poz fekete_futo = holvan(futo, fekete);
    return feher_futo.szin() != fekete_futo.szin();
}

Poz Tabla::holvan(BabuTipus babutipus, const Szin& szin) {
    std::vector<Poz> poziciok = egyszinu_babuk_pozicioja(szin);
    for (auto poz : poziciok) {
        Babu* babu = operator[](poz);
        if (babu->get_tipus() == babutipus)
            return poz;
    }
    return Poz();
}

bool Tabla::kiralyoldali_sanc_jog(const Jatekos &j) const {
    unsigned kezdosor = j.szin == feher ? 7 : 0;
    if (ures(Poz(kezdosor, 4)) || ures(Poz(kezdosor, 7)))
        return false;

    return !operator()(kezdosor, 4)->mozgott && !operator()(kezdosor, 7)->mozgott;
}

bool Tabla::kiralynooldali_sanc_jog(const Jatekos &j) const {
    unsigned kezdosor = j.szin == feher ? 7 : 0;
    if (ures(Poz(kezdosor, 4)) || ures(Poz(kezdosor, 0)))
        return false;

    return !operator()(kezdosor, 4)->mozgott && !operator()(kezdosor, 0)->mozgott;
}

bool Tabla::enpassant_jog(const Jatekos &j) {
    Poz atugrott = get_atugrott_pozicio(j.ellenfel()); // !!!! Lehet mashogy kene
    if (atugrott.oszlop == -1 && atugrott.sor == -1) {
        return false;
    }
    Poz lehetseges_uto_poziciok[2];
    if (j.szin == feher) {
        lehetseges_uto_poziciok[0] = atugrott + Eltolas::delkelet;
        lehetseges_uto_poziciok[1] = atugrott + Eltolas::delnyugat;
    } else {
        lehetseges_uto_poziciok[0] = atugrott + Eltolas::eszakkelet;
        lehetseges_uto_poziciok[1] = atugrott + Eltolas::eszaknyugat;
    }

    for (auto poz : lehetseges_uto_poziciok) {
        if (!benne_van(poz) || ures(poz)) {
            continue;
        }
        const Babu* babu = operator[](poz);
        if (babu->get_szin() == j.szin && babu->get_tipus() == paraszt) {
            EnPassant lepes(poz, atugrott);
            if (lepes.ervenyes(*this))
                return true;
        }
    }

    return false;
}

Tabla::Tabla(const Tabla& tabla) : tabla(8, std::vector<Babu*>(8, 0)) {
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            if (!tabla.ures(Poz(i, j)))
                this->tabla[i][j] = tabla.tabla[i][j]->copy();
            else
                this->tabla[i][j] = nullptr;
        }
    }
}
