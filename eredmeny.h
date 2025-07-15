#ifndef EREDMENY_H
#define EREDMENY_H

#include "jatekos.h"
#include <string>

class Eredmeny {
    Jatekos nyertes;
    std::string ok;
public:
    Eredmeny(Jatekos j, std::string o) : nyertes(j), ok(o) {}
    Eredmeny() : nyertes(none), ok("") {}
}
