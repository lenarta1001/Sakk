#ifndef EREDMENY_H
#define EREDMENY_H

#include "jatekos.h"
#include <string>

struct Eredmeny {
    Jatekos nyertes;
    std::string eredmeny;
    std::string ok;
    Eredmeny(Jatekos j, std::string e, std::string o) : nyertes(j), eredmeny(e), ok(o) {}
    Eredmeny() : nyertes(none), ok(" ") {}
};

#endif // EREDMENY_H
