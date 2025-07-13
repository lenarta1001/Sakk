#include "tabla.h"
#include "babu.h"

Tabla::Tabla() {
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

bool Tabla::ures(const Poz& p) const {
    return tabla[p.get_sor()][p.get_oszlop()] == nullptr;
}

bool Tabla::benne_van(const Poz& p) const {
    return p.get_sor() >= 0 && p.get_sor() < 8 &&  p.get_oszlop() >= 0 && p.get_oszlop() < 8;
}
