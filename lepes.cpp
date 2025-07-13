#include "lepes.h"
#include "tabla.h"

void NormalLepes::elvegez(Tabla &t) {
    Babu* babu = t[kezdo];
    delete t[veg];
    t[veg] = babu;
    t[kezdo] = babu;
}
