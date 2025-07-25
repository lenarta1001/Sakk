#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "ablak.h"
#include "tabla.h"
#include "jatekos.h"
#include "szin.h"

Ablak::Ablak() : menu_hatter(45, 32, 60, 200), menu_szegely(126, 66, 111, 200), gomb_szegely(79, 57, 95, 255), meret(768), menu(Menu::nincs), jatek(feher, Tabla::init()) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL_Init hiba: " << SDL_GetError() << std::endl;
    }
    TTF_Init();

    window = SDL_CreateWindow("Sakk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, meret, meret, 0);
    if (window == NULL) {
        std::cerr << "Ablak letrehozasi hiba: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        std::cerr << "Renderer létrehozasi hiba: " << SDL_GetError() << std::endl;
        exit(1);
    }
    font = TTF_OpenFont("seguisb.ttf", 40);
    font_kicsi = TTF_OpenFont("seguisb.ttf", 22);

    tabla_rajzol();
}

void Ablak::tabla_rajzol() {
    SDL_RenderClear(renderer);

    SDL_Texture *tabla_kep = betolt_kep("board.png");
    if (tabla_kep == NULL) {
        std::cerr << "Kep betoltési hiba: " << IMG_GetError() << std::endl;
        exit(1);
    }

    SDL_Rect celterulet = { 0, 0, meret, meret };
    SDL_RenderCopy(renderer, tabla_kep, NULL, &celterulet);
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!jatek.tabla.ures(Poz(i, j))) {
                SDL_Texture *babu_kep = betolt_kep(jatek.tabla(i, j)->kep());
                if (babu_kep == NULL) {
                    std::cerr << "Kep betoltési hiba: " << IMG_GetError() << std::endl;
                    exit(1);
                }
                SDL_Rect celterulet = { meret / 8 * j, meret / 8 * i, meret / 8, meret / 8 };
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
    for (auto lepes : elerhetok) {
        int oszlop = lepes->veg.oszlop;
        int sor = lepes->veg.sor;
        boxRGBA(renderer, meret / 8 * oszlop, meret / 8 * sor, meret / 8 * (oszlop+1), meret / 8 * (sor+1), 125, 255, 125, 125);
    }
    SDL_RenderPresent(renderer);
}

void Ablak::paraszt_atvaltozas_menu() {
    int szelesseg = meret / 1.8;
    int magassag = meret / 3.5;
    int x = (meret - szelesseg) / 2;
    int y = (meret - magassag) / 2;
    int r = meret / 100;
    roundedBoxRGBA(renderer, x - r, y - r, x + szelesseg + r , y + magassag + r, 20, menu_szegely.r, menu_szegely.g, menu_szegely.b, menu_szegely.a);
    roundedBoxRGBA(renderer, x, y, x + szelesseg, y + magassag, 20, menu_hatter.r, menu_hatter.g, menu_hatter.b, menu_hatter.a);
    SDL_Color betuszin = {245, 245, 245};
    
    SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, "VÁLASSZ EGY BÁBUT", betuszin);
    SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    SDL_Rect cel = {x + (szelesseg - felirat->w) / 2, y + (magassag / 2 - felirat->h) / 2, felirat->w, felirat->h };

    SDL_RenderCopy(renderer, felirat_t, NULL, &cel);

    std::string szin = jatek.akt_jatekos.szin == feher ? "white" : "black";
    std::string kepek[4] = {"queen.png", "bishop.png", "rook.png", "knight.png"};

    szelesseg = meret / 8;
    magassag = meret / 8;
    y = meret / 8 * 4;
    for (int i = 0; i < 4; i++) {
        SDL_Texture* kep = betolt_kep(szin + "-" + kepek[i]);
        if (kep == NULL) {
            std::cerr << "Kep betoltési hiba: " << IMG_GetError() << std::endl;
            exit(1);
        }
        x = meret / 8 * (2 + i);          
        SDL_Rect celterulet = { x, y,  szelesseg,  magassag};
        SDL_RenderCopy(renderer, kep, NULL, &celterulet);
    }
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    SDL_RenderPresent(renderer);
}

void Ablak::vege_menu() {
    int szelesseg = meret / 1.8;
    int magassag = meret / 3;
    int x = (meret - szelesseg) / 2;
    int y = (meret - magassag) / 2;
    int r = meret / 100;
    roundedBoxRGBA(renderer, x - r, y - r, x + szelesseg + r , y + magassag + r, 20, menu_szegely.r, menu_szegely.g, menu_szegely.b, menu_szegely.a);
    roundedBoxRGBA(renderer, x, y, x + szelesseg, y + magassag, 20, menu_hatter.r, menu_hatter.g, menu_hatter.b, menu_hatter.a);
    SDL_Color betuszin = {245, 245, 245};

    SDL_Surface *eredmeny = TTF_RenderUTF8_Blended(font, jatek.eredmeny.eredmeny.c_str(), betuszin);
    SDL_Texture *eredmeny_t = SDL_CreateTextureFromSurface(renderer, eredmeny);
    SDL_Surface *ok = TTF_RenderUTF8_Blended(font, jatek.eredmeny.ok.c_str(), betuszin);
    SDL_Texture *ok_t = SDL_CreateTextureFromSurface(renderer, ok);

    SDL_Rect cel1 = {x + (szelesseg - eredmeny->w) / 2, y + (magassag / 3 - eredmeny->h) / 2, eredmeny->w, eredmeny->h };
    SDL_Rect cel2 = {x + (szelesseg - ok->w) / 2, y + magassag / 3 + (magassag / 6 - ok->h) / 2, ok->w, ok->h };
    
    SDL_RenderCopy(renderer, eredmeny_t, NULL, &cel1);
    SDL_RenderCopy(renderer, ok_t, NULL, &cel2);
    
    kilepes = Gomb(x + szelesseg / 8, y + magassag / 3 * 2, x + szelesseg / 8 * 3, y + magassag / 3 * 2 + magassag / 4, r, "KILÉPÉS", font_kicsi, menu_hatter, gomb_szegely, betuszin);
    ujrakezdes = Gomb(x + szelesseg / 8 * 5, y + magassag / 3 * 2, x + szelesseg / 8 * 7, y + magassag / 3 * 2 + magassag / 4, r, "ÚJ JÁTÉK", font_kicsi, menu_hatter, gomb_szegely, betuszin);

    kilepes.rajzol(renderer);
    ujrakezdes.rajzol(renderer);

    SDL_FreeSurface(ok);
    SDL_FreeSurface(eredmeny);
    SDL_DestroyTexture(ok_t);
    SDL_DestroyTexture(eredmeny_t);
    SDL_RenderPresent(renderer);
}

void Ablak::szunet_menu() {
    int szelesseg = meret / 1.8;
    int magassag = meret / 3;
    int x = (meret - szelesseg) / 2;
    int y = (meret - magassag) / 2;
    int r = meret / 100;
    roundedBoxRGBA(renderer, x - r, y - r, x + szelesseg + r , y + magassag + r, 20, menu_szegely.r, menu_szegely.g, menu_szegely.b, menu_szegely.a);
    roundedBoxRGBA(renderer, x, y, x + szelesseg, y + magassag, 20, menu_hatter.r, menu_hatter.g, menu_hatter.b, menu_hatter.a);
    SDL_Color betuszin = {245, 245, 245};

    SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, "ÚJRAKEZDED?", betuszin);
    SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);

    SDL_Rect cel = {x + (szelesseg - felirat->w) / 2, y + (magassag / 2 - felirat->h) / 2, felirat->w, felirat->h };
    
    SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
    
    folytatas = Gomb(x + szelesseg / 8, y + magassag / 8 * 5, x + szelesseg / 8 * 3, y + magassag / 8 * 7, r, "FOLYTATÁS", font_kicsi, menu_hatter, gomb_szegely, betuszin);
    ujrakezdes = Gomb(x + szelesseg / 8 * 5, y + magassag / 8 * 5, x + szelesseg / 8 * 7, y + magassag / 8 * 7, r, "ÚJ JÁTÉK", font_kicsi, menu_hatter, gomb_szegely, betuszin);

    folytatas.rajzol(renderer);
    ujrakezdes.rajzol(renderer);

    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    SDL_RenderPresent(renderer);
}

void Ablak::button_down_esemenykezelo(SDL_Event event) {
    switch (menu) {
        case Menu::nincs: {
            Poz poz = melyik_negyzet(event.button.x, event.button.y);
            if (kivalasztott.oszlop == -1 && kivalasztott.sor == -1) {
                kezdo_kivalasztva(poz);
            } else {
                veg_kivalasztva(poz);
            }
            break;
        }
        case Menu::szunet: {
            if (folytatas.tartalmaz(event.button.x, event.button.y)) {
                tabla_rajzol();
                menu = Menu::nincs;
            } else if (ujrakezdes.tartalmaz(event.button.x, event.button.y)) {
                ujrainditas();
                menu = Menu::nincs;
            }
            break;
        }
        case Menu::vege: {
            if (kilepes.tartalmaz(event.button.x, event.button.y)) {
                fut = false;
            } else if (ujrakezdes.tartalmaz(event.button.x, event.button.y)) {
                ujrainditas();
                menu = Menu::nincs;
            }
            break;
        }
    }
}

Poz Ablak::melyik_negyzet(unsigned x, unsigned y) {
    return Poz(y / 96, x / 96);
}

void Ablak::esemenyre_var() {
    bool fut = true;
    while (fut) {
        if (jatek.vege) {
            menu = Menu::vege;
            vege_menu();
            jatek.vege = false; 
        }
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                fut = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    szunet_menu();
                    menu = Menu::szunet;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    button_down_esemenykezelo(event);
                }
                break;
        }
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
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void Ablak::ujrainditas() {
    jatek.tabla = Tabla::init();
    jatek.akt_jatekos = feher;
    kivalasztott = Poz(-1, -1);
    elerhetok.clear();
    tabla_rajzol();
}
