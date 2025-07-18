#include "tabla.h"
#include "babu.h"
#include "poz.h"
#include "jatekos.h"
#include "szamolo.h"

Tabla::Tabla() : tabla(8, std::vector<Babu*>(8, 0))  {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            tabla[i][j] = nullptr;
}

Tabla::~Tabla() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete tabla[i][j];
}

Babu*& Tabla::operator[](const Poz& p) {
    return tabla[p.get_sor()][p.get_oszlop()];
}

Babu* Tabla::operator[](const Poz& p) const {
    return tabla[p.get_sor()][p.get_oszlop()];
}


void Tabla::init() {
    tabla[0][0] = new Bastya(fekete);
    tabla[0][1] = new Huszar(fekete);
    tabla[0][2] = new Futo(fekete);
    tabla[0][3] = new Kiralyno(fekete);
    tabla[0][4] = new Kiraly(fekete);
    tabla[0][5] = new Futo(fekete);
    tabla[0][6] = new Huszar(fekete);
    tabla[0][7] = new Huszar(fekete);

    tabla[7][0] = new Bastya(feher);
    tabla[7][1] = new Huszar(feher);
    tabla[7][2] = new Futo(feher);
    tabla[7][3] = new Kiralyno(feher);
    tabla[7][4] = new Kiraly(feher);
    tabla[7][5] = new Futo(feher);
    tabla[7][6] = new Huszar(feher);
    tabla[7][7] = new Huszar(feher);

    for (int i = 0; i < 8; i++) {
        tabla[1][i] = new Paraszt(fekete);
        tabla[6][i] = new Paraszt(feher);
    }
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
    return tabla[p.get_sor()][p.get_oszlop()] == nullptr;
}

bool Tabla::benne_van(const Poz& p) const {
    return p.get_sor() >= 0 && p.get_sor() < 8 &&  p.get_oszlop() >= 0 && p.get_oszlop() < 8;
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

Tabla::Tabla(const Tabla& t) : tabla(8, std::vector<Babu*>(8, 0)) {
    for (size_t i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            this->tabla[i][j] = t.tabla[i][j]->copy();
    }
}
