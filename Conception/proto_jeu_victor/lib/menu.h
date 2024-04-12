#ifndef _MENU_H_
#define _MENU_H_

/**************/
/*--Includes--*/
/**************/
#include "commun_SDL.h"
#include "affichage_menu.h"
#include "affichage_jeu.h"

/***************/
/*--Fonctions--*/
/***************/

void clic_menu(etatMenu_t* etatMenu, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, int* continuer, int* selecElement, char* effet, int* isValid,  const char* textInput, const char* ipPattern, int* textInputActive, int* keyCounts, int x, int y, int* ancienSon, int* ancienReso);
void relachement_menu(etatMenu_t* etatMenu, int menuX, int menuY, int w, int h, float* widthFactor, float* heightFactor, int mouseX, int mouseY);
void deplacement_menu(Mix_Chunk* music, int mouseX, SDL_Event evenement, float* widthFactor);
void destruction_menu(int* selecElement, int* index_effet, int* continuer, etatMenu_t* etatMenu, float* widthFactor, float* heightFactor, int* textInputActive, int* isValid, int* keyCounts, int* ancien, age_t* etatAge, int* ancienSon);
void touches_menu(SDL_Event evenement, int* textInputActive, int* keyCounts, int* isValid, char* textInput,const char* ipPattern);

int validateRegex(const char *input, const char *pattern);


#endif