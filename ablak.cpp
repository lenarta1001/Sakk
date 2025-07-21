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

    window = SDL_CreateWindow("Sakk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 768, 0);
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

    SDL_Texture *tabla_kep = betolt_kep("board.png");
    if (tabla_kep == NULL) {
        std::cerr << "Kep betoltési hiba: " << IMG_GetError() << std::endl;
        exit(1);
    }

    SDL_Rect celterulet = { 0, 0, 768, 768 };
    SDL_RenderCopy(renderer, tabla_kep, NULL, &celterulet);
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!jatek.tabla.ures(Poz(i, j))) {
                SDL_Texture *babu_kep = betolt_kep(jatek.tabla(i, j)->kep());
                if (babu_kep == NULL) {
                    std::cerr << "Kep betoltési hiba: " << IMG_GetError() << std::endl;
                    exit(1);
                }
                SDL_Rect celterulet = { 96*j, 96*i, 96, 96 };
                SDL_RenderCopy(renderer, babu_kep, NULL, &celterulet);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

SDL_Texture *Ablak::betolt_kep(const std::string &fajlnev) {
    if (kepek.count(fajlnev) > 0) {
        return kepek[fajlnev];
    }

    SDL_Texture* kep = IMG_LoadTexture(renderer, fajlnev.c_str());
    if (kep == NULL) {
        std::cerr << "Kép betöltési hiba: " << fajlnev << " - " << IMG_GetError() << std::endl;
        exit(1);
    }
    kepek[fajlnev] = kep;
    return kep;
}

void Ablak::kiemeles_rajzol() {
    for (size_t i = 0; i < elerhetok.size(); i++) {
        Lepes* lepes = elerhetok[i];
        int oszlop = lepes->veg.oszlop;
        int sor = lepes->veg.sor;
        boxRGBA(renderer, 96*oszlop, 96*sor, 96*(oszlop+1), 96*(sor+1), 125, 255, 125, 125);
    }
    SDL_RenderPresent(renderer);
}

void Ablak::button_down_esemenykezelo(SDL_Event event) {
    Poz poz = melyik_negyzet(event.button.x, event.button.y);
    if (kivalasztott.oszlop == -1 && kivalasztott.sor == -1) {
        kezdo_kivalasztva(poz);
    } else {
        veg_kivalasztva(poz);
    }
}

Poz Ablak::melyik_negyzet(unsigned x, unsigned y) {
    return Poz(y / 96, x / 96);
}

void Ablak::esemenyre_var() {
    
    bool fut = true;
    while (fut) {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                fut = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    fut = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    button_down_esemenykezelo(event);
                }
                break;
        }
        SDL_Delay(16);
    }
}

void Ablak::kezdo_kivalasztva(const Poz& poz) {
    Lepesek ervenyesek = jatek.ervenyes_lepesek(poz);
    if (!ervenyesek.empty()) {
        kivalasztott = poz;
        elerhetok.clear();
        elerhetok = ervenyesek;
        kiemeles_rajzol();
    }
}
 
void Ablak::veg_kivalasztva(const Poz& poz) {
    kivalasztott = Poz(-1, -1);
    for (auto& lepes : elerhetok) {
        if (lepes->veg == poz) {
            jatek.lep(lepes);
            break;
        }
    }
    tabla_rajzol();
}

Ablak::~Ablak() {
    for (auto& par : kepek) {
        SDL_DestroyTexture(par.second);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}