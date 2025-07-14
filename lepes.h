#ifndef LEPES_H
#define LEPES_H

#include "poz.h"

class Tabla;

class Lepes {
protected:
    Poz kezdo;
    Poz veg;
public:
    Lepes(const Poz& k, const Poz& v) : kezdo(k), veg(v) {}
    virtual Lepes* copy() = 0;
    virtual void elvegez(Tabla& t);
    virtual ~Lepes() {}
};

class NormalLepes : public Lepes {
public:
    NormalLepes(const Poz& k, const Poz& v) : Lepes(k, v) {}
    Lepes* copy() { return new NormalLepes(kezdo, veg); }
    void elvegez(Tabla& t);
};

class Lepesek : public std::vector<Lepes*> {
public:
    Lepesek(size_t db = 0) : std::vector<Lepes*>(db) {}
    Lepesek(const Lepesek& l) {
        for (size_t i = 0; i < l.size(); i++) {

        }
    }
    ~Lepesek() {
        for (size_t i = 0; i < size(); i++) {
            delete (*this)[i];
        }
    }
};

#endif // LEPES_H
