#ifndef LEPES_H
#define LEPES_H

#include <vector>
#include "poz.h"
#include "eltolas.h"

class Tabla;
class Babu;

class Lepes {
public:
    Poz kezdo;
    Poz veg;
    Lepes(const Poz& k, const Poz& v) : kezdo(k), veg(v) {}
    virtual Lepes* copy() = 0;
    virtual void elvegez(Tabla& t) const = 0;
    virtual bool ervenyes(Tabla& tabla) const;
    virtual ~Lepes() {}
};

class NormalLepes : public Lepes {
public:
    NormalLepes(const Poz& k, const Poz& v) : Lepes(k, v) {}
    Lepes* copy() { return new NormalLepes(kezdo, veg); }
    void elvegez(Tabla& t) const;
    ~NormalLepes() {}
};

class ParasztAtvaltozas : public Lepes {
    Babu* mive;
public:
    ParasztAtvaltozas(const Poz& k, const Poz& v, Babu* mive) : Lepes(k, v), mive(mive) {}
    ParasztAtvaltozas(const ParasztAtvaltozas& p);
    Lepes* copy();
    void elvegez(Tabla& t) const;
    ~ParasztAtvaltozas();
};

class KiralyOldaliSanc : public Lepes {
    Poz bastya_kezdo;
    Poz bastya_veg;
    Eltolas irany;
public:
    KiralyOldaliSanc(const Poz& k) : Lepes(k, Poz(k.get_sor(), 6)), bastya_kezdo(k.get_sor(), 7), bastya_veg(k.get_sor(), 5), irany(Eltolas::kelet) {}
    Lepes* copy() { return new KiralyOldaliSanc(kezdo, veg, bastya_kezdo, bastya_veg, irany); }
    void elvegez(Tabla& t) const;
    bool ervenyes(Tabla& tabla) const;
    ~KiralyOldaliSanc() {}
};

class KiralynoOldaliSanc : public Lepes {
    Poz bastya_kezdo;
    Poz bastya_veg;
    Eltolas irany;
public:
    KiralynoOldaliSanc(const Poz& k) : Lepes(k, Poz(k.get_sor(), 2)), bastya_kezdo(k.get_sor(), 0), bastya_veg(k.get_sor(), 3), irany(Eltolas::nyugat) {}
    Lepes* copy() { return new KiralynoOldaliSanc(kezdo, veg, bastya_kezdo, bastya_veg, irany); }
    void elvegez(Tabla& t) const;
    ~KiralynoOldaliSanc() {}
};

class Lepesek : public std::vector<Lepes*> {
public:
    Lepesek(size_t db = 0) : std::vector<Lepes*>(db) {}
    Lepesek(const Lepesek& l) {
        for (size_t i = 0; i < l.size(); i++) {
            push_back(l[i]->copy());
        }
    }
    ~Lepesek() {
        for (size_t i = 0; i < size(); i++) {
            delete (*this)[i];
        }
    }

};

#endif // LEPES_H
