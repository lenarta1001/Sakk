#ifndef LEPES_H
#define LEPES_H

#include <vector>
#include "poz.h"
#include "eltolas.h"

class Tabla;
class Babu;

enum LepesTipus {
    normal,
    dupla,
    paraszt_atvaltozas,
    kr_sanc,
    krno_sanc,
    en_passant,
};

class Lepes {
public:
    Poz kezdo;
    Poz veg;
    LepesTipus tipus;
    Lepes(const Poz& k, const Poz& v, LepesTipus tipus) : kezdo(k), veg(v), tipus(tipus) {}
    virtual Lepes* copy() = 0;
    virtual void elvegez(Tabla& tabla) const = 0;
    virtual bool ervenyes(Tabla& tabla) const;
    virtual bool parasztlepes_utes(Tabla& tabla) const = 0;
    virtual ~Lepes() {}
};

class NormalLepes : public Lepes {
public:
    NormalLepes(const Poz& k, const Poz& v) : Lepes(k, v, normal) {}
    Lepes* copy() { return new NormalLepes(kezdo, veg); }
    void elvegez(Tabla& tabla) const;
    bool parasztlepes_utes(Tabla& tabla) const;
    ~NormalLepes() {}
};

class DuplaLepes : public Lepes {
    Poz atugrott;
public:
    DuplaLepes(const Poz& k, const Poz& v) : Lepes(k, v, dupla), atugrott((k.sor + v.sor) / 2, k.oszlop) {}
    Lepes* copy() { return new DuplaLepes(kezdo, veg); }
    void elvegez(Tabla& tabla) const;
    bool parasztlepes_utes(Tabla& tabla) const;
    ~DuplaLepes() {}
};

class ParasztAtvaltozas : public Lepes {
    Babu* mive;
public:
    ParasztAtvaltozas(const Poz& k, const Poz& v, Babu* mive) : Lepes(k, v, paraszt_atvaltozas), mive(mive) {}
    ParasztAtvaltozas(const ParasztAtvaltozas& p);
    Lepes* copy();
    void elvegez(Tabla& tabla) const;
    bool parasztlepes_utes(Tabla& tabla) const;
    ~ParasztAtvaltozas();
};

class KiralyOldaliSanc : public Lepes {
    Poz bastya_kezdo;
    Poz bastya_veg;
    Eltolas irany;
public:
    KiralyOldaliSanc(const Poz& k) : Lepes(k, Poz(k.sor, 6), kr_sanc), bastya_kezdo(k.sor, 7), bastya_veg(k.sor, 5), irany(Eltolas::kelet) {}
    Lepes* copy() { return new KiralyOldaliSanc(kezdo); }
    void elvegez(Tabla& tabla) const;
    bool ervenyes(Tabla& tabla) const;
    bool parasztlepes_utes(Tabla& tabla) const;
    ~KiralyOldaliSanc() {}
};

class KiralynoOldaliSanc : public Lepes {
    Poz bastya_kezdo;
    Poz bastya_veg;
    Eltolas irany;
public:
    KiralynoOldaliSanc(const Poz& k) : Lepes(k, Poz(k.sor, 2), krno_sanc), bastya_kezdo(k.sor, 0), bastya_veg(k.sor, 3), irany(Eltolas::nyugat) {}
    Lepes* copy() { return new KiralynoOldaliSanc(kezdo); }
    void elvegez(Tabla& tabla) const;
    bool ervenyes(Tabla& tabla) const;
    bool parasztlepes_utes(Tabla& tabla) const;
    ~KiralynoOldaliSanc() {}
};

class EnPassant : public Lepes {
    Poz leutott_poz;
public:
    EnPassant(const Poz& k, const Poz& v) : Lepes(k, v, en_passant), leutott_poz(k.sor, v.oszlop) {}
    Lepes* copy() { return new EnPassant(kezdo, veg); }
    void elvegez(Tabla& tabla) const;
    bool parasztlepes_utes(Tabla& tabla) const;
    ~EnPassant() {}
};

class Lepesek : public std::vector<Lepes*> {
public:
    Lepesek(size_t db = 0) : std::vector<Lepes*>(db) {}
    Lepesek& operator=(const Lepesek& l) {
        if (this != &l) {
            for (auto& lepes : *this) {
                delete lepes;
            }

            for (auto& lepes : l) {
                push_back(lepes->copy());
            }
        }
        return *this;
    }
    Lepesek(const Lepesek& l) {
        for (auto& lepes : l) {
            push_back(lepes->copy());
        }
    }

    void clear() {
        for (auto& lepes : *this) {
            delete lepes;
        }
        std::vector<Lepes*>::clear();
    }

    ~Lepesek() {
        for (auto& lepes : *this) {
                delete lepes;
        }
    }

};

#endif // LEPES_H
