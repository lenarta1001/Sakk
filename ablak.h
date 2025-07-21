#ifndef ABLAK_H
#define ABLAK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "babu.h"
#include "jatekallas.h"
#include "tabla.h"
#include "poz.h"
#include "lepes.h"

class Ablak {
    SDL_Renderer* renderer;
    SDL_Window* window;
    std::map<std::string, SDL_Texture*> kepek;

    JatekAllas jatek;
    Poz kivalasztott;
    Lepesek elerhetok;
public:
    Ablak();
    void tabla_rajzol();
    SDL_Texture* betolt_kep(const std::string& fajlnev);
    void esemenyre_var();
    void kiemeles_rajzol(); 
    void button_down_esemenykezelo(SDL_Event event);
    void kezdo_kivalasztva(const Poz& p);
    void veg_kivalasztva(const Poz& p);
    Poz melyik_negyzet(unsigned x, unsigned y);
    ~Ablak();
};

#endif // ABLAK_H