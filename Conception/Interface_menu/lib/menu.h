#ifndef _MENU_H_
#define _MENU_H_

/**************/
/*--Includes--*/
/**************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/************/
/*--Macros--*/
/************/
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define MENU_WIDTH 400
#define MENU_HEIGHT 60
#define SPACING 30   /*Espace entre chaque sous-menu*/

#define MENU_D_WIDTH 200
#define MENU_D_HEIGHT 400
#define MENU_ITEM_HEIGHT 50
#define MENU_ITEM_WIDTH 150

/*Code couleur */
#define COLOR (SDL_Color){255, 255, 255}

/*Énumération des états de menu*/
enum MenuState {
    MENU_PRINCIPAL,
    MENU_SOUS_JOUER,
    MENU_SOUS_REPRENDRE,
    MENU_SOUS_PARAMETRES,  /*Ajout du sous-menu "Paramètres"*/
    MENU_SOUS_RESOLUTION,
    MENU_SOUS_PARAMETRES_OPTION2,
    MENU_SOUS_PARAMETRES_OPTION3,
    MENU_SOUS_RETOUR,
    MENU_SOUS_QUITTER
};

/*Structure pour un élément de menu déroulant*/
typedef struct {
    const char* label;
    SDL_Rect rect;
} MenuItem;

/***************/
/*--Fonctions--*/
/***************/
void afficherMenu(SDL_Renderer*, TTF_Font*, const char*, int, int, int, int);
void afficherSousMenu(SDL_Renderer* , TTF_Font*, const char*, const char*, const char*, const char*,const char*);
void afficherSousMenuResolution(SDL_Renderer* rendu, MenuItem* item, TTF_Font* police, const char* texte1, const char* texte2, int currentIndexItem);
void mettreAJourPositionMenu(int*, int*);
void mettreAJourPositionSousMenu(int*, int*);
void initMenuItem(MenuItem* item, const char* label, int x, int y);
void afficherMenuDeroulant(SDL_Renderer* renderer, MenuItem* item, TTF_Font* police, int currentIndexItem);





#endif