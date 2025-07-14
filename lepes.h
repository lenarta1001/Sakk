#ifndef LEPES_H
#define LEPES_H

#include <vector>
#include "poz.h"


class Tabla;

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
