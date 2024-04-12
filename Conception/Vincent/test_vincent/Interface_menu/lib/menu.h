#ifndef _MENU_H_
#define _MENU_H_

/**************/
/*--Includes--*/
/**************/
#include "commun.h"
#include "affichage_menu.h"

/*Pour la gestion du volume*/
SDL_bool estLache;
int volume;    
SDL_Rect* volumeBar;
SDL_Rect* volumeCursor;

/***************/
/*--Fonctions--*/
/***************/
int initialisation(void);
TTF_Font* chargementPolice(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* textureFond, char* path, int taille);
Mix_Chunk* chargementAudio(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* textureFond, char* path);
SDL_Texture* chargementImg(SDL_Renderer* rendu, SDL_Window* fenetre, char* path);
SDL_Rect creationRectangle(SDL_Window* fenetre, int x, int y, int largeur, int hauteur);


void clic_menu(etatMenu_t* etatMenu, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, int* continuer, int* selecElement, char* effet, int* isValid,  const char* textInput, const char* ipPattern, int* textInputActive, int* keyCounts);
void relachement_menu(etatMenu_t* etatMenu, int menuX, int menuY, int w, int h, float* widthFactor, float* heightFactor, int mouseX, int mouseY);
void deplacement_menu(Mix_Chunk* music, int mouseX, SDL_Event evenement, float* widthFactor);
void destruction_menu(int* selecElement, int* index_effet, int* continuer, etatMenu_t* etatMenu, float* widthFactor, float* heightFactor, int* textInputActive, int* isValid, int* keyCounts);

int validateRegex(const char *input, const char *pattern);

#endif