#ifndef _MENU_H_
#define _MENU_H_

/**************/
/*--Includes--*/
/**************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

/************/
/*--Macros--*/
/************/
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define MENU_WIDTH 250
#define MENU_HEIGHT 60
#define MENU_DECALAGE 50 /*Décalage pour abaisser le menu*/
#define SPACING 30   /*Espace entre chaque sous-menu*/

#define MENU_ITEM_HEIGHT 30
#define MENU_ITEM_PADDING 10

/*Structure pour stocker les informations sur les éléments du menu*/
typedef struct {
    SDL_Rect rect;
    char text[100];
    bool isHovered;
} MenuItem;

/*Code couleur */
#define COLOR (SDL_Color){0, 0, 0}

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
    const char label[100];
    SDL_Rect rect;
} Resolu_Item;

/***************/
/*--Fonctions--*/
/***************/
void afficherMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte, int x, int y, int largeur, int hauteur);
void afficherSousMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3, const char* texte4,const char* texte5);
void afficherSousMenuResolution(SDL_Renderer* rendu, Resolu_Item* item, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, int currentIndexItem);
void initMenuItem(Resolu_Item* item, const char* label, int x, int y);
void afficherMenuDeroulant(SDL_Renderer* renderer, Resolu_Item* item, TTF_Font* police, int currentIndexItem);
void afficherTitre(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, int x, int y, int largeur, int hauteur);
MenuItem* creerMenu(SDL_Window* fenetre, const char* item1, const char* item2, const char* item3, const char* item4, const char* item5);
void detruireMenu(MenuItem ** items);
void ligneHorizontale(int x, int y, int w, Uint32 coul);




#endif