#ifndef _MENU_H_
#define _MENU_H_

/**************/
/*--Includes--*/
/**************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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

#define ELEMENT_WIDTH 100 // Largeur d'un élément
#define ELEMENT_HEIGHT 50 // Hauteur d'un élément
#define ELEMENT_SPACING 20 // Espacement entre les éléments

/*Code couleur */
#define COLOR (SDL_Color){0, 0, 0}

/*Énumération des états de menu*/
typedef enum MenuState {
    MENU_PRINCIPAL,
    MENU_SOUS,
    MENU_SOUS_JOUER,
    MENU_SOUS_REPRENDRE,
    MENU_SOUS_OPTIONS,
    MENU_SOUS_RESOLUTION,
    MENU_SOUS_CREDITS,
    MENU_SOUS_SON,
}etatMenu_t;

/*Structure menu Resolution*/
typedef struct {
    SDL_Rect rect; // Rectangle représentant l'élément
    char* info; // Informations spécifiques à l'élément
    int w;
    int h;
} element_t;

/*Pour la gestion du volume*/
SDL_bool estLache;
int volume;    
SDL_Rect* volumeBar;
SDL_Rect* volumeCursor;

/***************/
/*--Fonctions--*/
/***************/
int initialisation(void);
void affichage(etatMenu_t etatMenu, SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police , int menuX, int menuY, element_t* elm_reso, int* selecElement, const char* effet);
TTF_Font* chargementPolice(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* textureFond, char* path, int taille);
Mix_Chunk* chargementAudio(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* textureFond, char* path);
SDL_Texture* chargementImg(SDL_Renderer* rendu, SDL_Window* fenetre, char* path);
void afficherMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte, int x, int y, int largeur, int hauteur);
void afficherSousMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3, const char* texte4,const char* texte5);
void afficherSousMenuResolution(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre);
void afficherTitre(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, int x, int y, int largeur, int hauteur);
void initElements(SDL_Renderer* rendu, SDL_Window* fenetre, element_t* elm_reso);
void resolution(SDL_Renderer* rendu, SDL_Window* fenetre , TTF_Font* police, element_t* elm_reso, int* selecElement);
void afficherSousMenuCredits(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police);
void afficherSousMenuOption(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3);
void afficherSousMenuSon(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte);

void clic_menu(etatMenu_t* etatMenu, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, int* continuer, int* selecElement, char* effet);
void relachement_menu(etatMenu_t* etatMenu, int menuX, int menuY, int w, int h, float* widthFactor, float* heightFactor, int mouseX, int mouseY);
void deplacement_menu(Mix_Chunk* music, int mouseX, SDL_Event evenement, float* widthFactor);
void destruction_menu(int* selecElement, int* index_effet, int* continuer, etatMenu_t* etatMenu, float* widthFactor, float* heightFactor);

#endif