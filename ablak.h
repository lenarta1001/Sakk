#ifndef ABLAK_H
#define ABLAK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "babu.h"
#include "jatekallas.h"
#include "tabla.h"

class Ablak {
    SDL_Renderer* renderer;
    SDL_Window* window;
    JatekAllas jatek;
public:
    Ablak();
    void tabla_rajzol();
    void esemenyre_var();
    ~Ablak();
};

#endif // ABLAK_H