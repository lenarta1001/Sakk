#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "ablak.h"
#include "tabla.h"
#include "jatekos.h"
#include "szin.h"

Ablak::Ablak() : jatek(feher, Tabla::init()) {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL_Init hiba: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Sakk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 784, 784, 0);
    if (window == NULL) {
        std::cerr << "Ablak letrehozasi hiba: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        std::cerr << "Renderer létrehozasi hiba: " << SDL_GetError() << std::endl;
        exit(1);
    }
    tabla_rajzol();
}

void Ablak::tabla_rajzol() {
    SDL_RenderClear(renderer);

    SDL_Texture *tabla_kep = IMG_LoadTexture(renderer, "board.png");
    if (tabla_kep == NULL) {
        std::cerr << "Kep betoltési hiba: " << IMG_GetError() << std::endl;
        exit(1);
    }

    SDL_Rect celterulet = { 0, 0, 784, 784 };
    SDL_RenderCopy(renderer, tabla_kep, NULL, &celterulet);
    SDL_DestroyTexture(tabla_kep);
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!jatek.tabla.ures(Poz(i, j))) {
                SDL_Texture *babu_kep = jatek.tabla(i, j)->kep(renderer);
                if (babu_kep == NULL) {
                    std::cerr << "Kep betoltési hiba: " << IMG_GetError() << std::endl;
                    exit(1);
                }
                SDL_Rect celterulet = { 8 + 96*j, 8 + 96*i, 96, 96 };
                SDL_RenderCopy(renderer, babu_kep, NULL, &celterulet);
                SDL_DestroyTexture(babu_kep);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Ablak::esemenyre_var() {
    SDL_Event event;
    bool fut = true;
    while (fut) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                fut = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    fut = false;
                break;
        }
    }
}
 
Ablak::~Ablak() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}