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

enum class Menu {
    nincs,
    paraszt_atvaltozas,
    szunet,
    vege
};

struct RGBA {
    Uint8 r, g, b, a;
    RGBA(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0) :r(r), g(g), b(b), a(a) {}
};

class Gomb {
    Uint16 x1, y1, x2, y2, d;
    std::string felirat;
    TTF_Font *font;
    RGBA hatter_szin, szegely_szin;
    SDL_Color felirat_szin;
public:
    Gomb(Uint16 x1 = 0, Uint16 y1 = 0, Uint16 x2 = 0, Uint16 y2 = 0, Uint16 d = 0, std::string felirat = " ", TTF_Font *font = nullptr, RGBA h = RGBA(), RGBA sze = RGBA(), SDL_Color f = (SDL_Color){0, 0, 0}) : x1(x1), y1(y1), x2(x2), y2(y2), d(d), felirat(felirat), font(font), hatter_szin(h), szegely_szin(sze), felirat_szin(f) {}
    void rajzol(SDL_Renderer* renderer) {
        roundedBoxRGBA(renderer, x1 - d, y1 - d, x2 + d, y2 + d, 5, szegely_szin.r, szegely_szin.g, szegely_szin.b, szegely_szin.a);
        roundedBoxRGBA(renderer, x1, y1, x2, y2, 5, hatter_szin.r, hatter_szin.g, hatter_szin.b, hatter_szin.a);

        SDL_Surface* felirat = TTF_RenderUTF8_Blended(font, this->felirat.c_str(), felirat_szin);
        SDL_Texture* felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
        SDL_Rect szoveg_hely = {
            x1 + (x2 - x1 - felirat->w) / 2,
            y1 + (y2 - y1 - felirat->h) / 2,
            felirat->w,
            felirat->h
        };
        SDL_RenderCopy(renderer, felirat_t, NULL, &szoveg_hely);
        SDL_FreeSurface(felirat);
        SDL_DestroyTexture(felirat_t);
    }

    bool tartalmaz(int x, int y) const {
        return x >= x1 && x <= x2 && y >= y1 && y <= y2;
    }
};

class Ablak {
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font *font;
    TTF_Font *font_kicsi;
    std::map<std::string, SDL_Texture*> kepek;
    RGBA menu_hatter;
    RGBA menu_szegely;
    RGBA gomb_szegely;
    Gomb ujrakezdes;
    Gomb kilepes;
    Gomb folytatas;
    int meret;

    JatekAllas jatek;
    Menu menu;
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
    void paraszt_atvaltozas_menu();
    void vege_menu();
    void szunet_menu();
    void ujrainditas();
    ~Ablak();
};

#endif // ABLAK_H