#ifndef BABU_H
#define BABU_H

#include <iostream>
#include <vector>

#include "szin.h"
#include "poz.h"
#include "lepes.h"

class Tabla;

enum BabuTipus {
    kiraly,
    kiralyno,
    futo,
    huszar,
    bastya,
    paraszt
};

class Babu {
protected:
    Szin szin;
    bool mozgott;
    BabuTipus tipus;
public:
    Babu(Szin sz, bool m = false, BabuTipus tipus = paraszt) : szin(sz), mozgott(m), tipus(tipus) {}
    virtual Lepesek lepesek(const Poz& kezdo, Tabla& tabla) const = 0;
    virtual Babu* copy() const = 0;
    Szin get_szin() const { return szin; }
    bool get_mozgott() const { return mozgott; }
    BabuTipus get_tipus() const { return tipus; }
    virtual bool uti_a_kiralyt(const Poz& poz, Tabla& tabla) const;
    virtual char fen_char() const = 0;
    virtual ~Babu() {}
};

class Paraszt : public Babu {
    Eltolas irany;
public:
    Paraszt(Szin sz, bool m = false) : Babu(sz, m, paraszt) {
        irany = szin == Szin::feher ? Eltolas::eszak : Eltolas::del;
    }
    Lepesek elore_lepesek(const Poz& kezdo, Tabla& tabla) const;
    Lepesek atlos_lepesek(const Poz& kezdo, Tabla& tabla) const;
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla) const;
    Babu* copy() const { return new Paraszt(szin, mozgott); }
    bool uti_a_kiralyt(const Poz& poz, Tabla& tabla) const;
    char fen_char() const { return  szin == feher ? 'P' : 'p'; }
};


class Bastya : public Babu {
public:
    Bastya(Szin sz, bool m = false) : Babu(sz, m, bastya) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla) const;
    Babu* copy() const { return new Bastya(szin, mozgott); }
    char fen_char() const { return  szin == feher ? 'R' : 'r'; }
};

class Futo : public Babu {
public:
    Futo(Szin sz, bool m = false) : Babu(sz, m, futo) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla) const;
    Babu* copy() const { return new Futo(szin, mozgott); }
    char fen_char() const { return  szin == feher ? 'B' : 'b'; }
};

class Huszar : public Babu {
public:
    Huszar(Szin sz, bool m = false) : Babu(sz, m, futo) {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla) const;
    Babu* copy() const { return new Huszar(szin, mozgott); }
    char fen_char() const { return  szin == feher ? 'N' : 'n'; }
};

class Kiraly : public Babu {
public:
    Kiraly(Szin sz, bool m = false) : Babu(sz, m, futo)  {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla) const;
    Babu* copy() const { return new Kiraly(szin, mozgott); }
    bool sancolhat_kiraly_oldalon(Poz kezdo, Tabla& tabla) const;
    bool sancolhat_kiralyno_oldalon(Poz kezdo, Tabla& tabla) const;
    char fen_char() const { return  szin == feher ? 'K' : 'k'; }
};

class Kiralyno : public Babu {
public:
    Kiralyno(Szin sz, bool m = false) : Babu(sz, m, kiralyno)  {}
    Lepesek lepesek(const Poz& kezdo, Tabla& tabla) const;
    Babu* copy() const { return new Kiralyno(szin, mozgott); }
    char fen_char() const { return  szin == feher ? 'Q' : 'q'; }
};
#endif // BABU_H
