#ifndef ELTOLAS_H
#define ELTOLAS_H

struct Eltolas {
    static Eltolas del;
    static Eltolas kelet;
    static Eltolas eszak;
    static Eltolas nyugat;
    static Eltolas eszakkelet;
    static Eltolas eszaknyugat;
    static Eltolas delkelet;
    static Eltolas delnyugat;
    int dsor, doszlop;
    Eltolas(int ds, int dsz) : dsor(ds), doszlop(dsz) {}
    Eltolas operator*(double c) const;
    Eltolas operator+(const Eltolas& e) const;

};

#endif // ELTOLAS_H
