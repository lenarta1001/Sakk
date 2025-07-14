#ifndef BABU_H
#define BABU_H

#include <iostream>
#include <vector>

#include "szin.h"
#include "poz.h"
#include "lepes.h"

class Tabla;

class Babu {
protected:
    Szin szin;
    bool mozgott;
public:
    Babu(Szin sz, bool m = false) : szin(sz), mozgott(m) {}
    virtual Lepesek lepesek(const Poz& kezdo, Tabla& tabla) = 0;
    virtual Babu* copy() = 0;
    Szin get_szin() { return szin; }
    virtual ~Babu() {}
};

class Paraszt : public Babu {
public:
    Paraszt(Szin sz, bool m = false) : Babu(sz, m) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla);
    Babu* copy() { return new Paraszt(szin, mozgott); }
};


class Bastya : public Babu {
public:
    Bastya(Szin sz, bool m = false) : Babu(sz, m) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla);
    Babu* copy() { return new Bastya(szin, mozgott); }
};

class Futo : public Babu {
public:
    Futo(Szin sz, bool m = false) : Babu(sz, m) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla);
    Babu* copy() { return new Futo(szin, mozgott); }
};

class Huszar : public Babu {
public:
    Huszar(Szin sz, bool m = false) : Babu(sz, m) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla);
    Babu* copy() { return new Huszar(szin, mozgott); }
};

class Kiraly : public Babu {
public:
    Kiraly(Szin sz, bool m = false) : Babu(sz, m) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla) ;
    Babu* copy() { return new Kiraly(szin, mozgott); }
};

class Kiralyno : public Babu {
public:
    Kiralyno(Szin sz, bool m = false) : Babu(sz, m) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla);
    Babu* copy() { return new Kiralyno(szin, mozgott); }
};
#endif // BABU_H
