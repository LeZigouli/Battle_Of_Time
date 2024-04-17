#ifndef _MENU_H_
#define _MENU_H_

/**************/
/*--Includes--*/
/**************/
#include "commun_SDL.h"
#include "affichage_menu.h"
#include "affichage_jeu.h"
#include "player.h"
#include "ordinateur.h"

/***************/
/*--Fonctions--*/
/***************/

void clic(etat_t* etat, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, 
               int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, 
               int* continuer, int* selecElement, char* effet, int* isValid, const char* textInput, const char* ipPattern, 
               int* textInputActive, int* keyCounts, int x, int y, int* ancienSon, int* ancienReso, player_t* j1,
               character_t* tab_de_charactere, ordi_t* ordi);

void relachement(etat_t* etat, int menuX, int menuY, int w, int h, float* widthFactor, float* heightFactor, int mouseX, int mouseY);
void deplacement_souris(Mix_Chunk* music, int mouseX, SDL_Event evenement, float* widthFactor);
void destruction(int* selecElement, int* index_effet, int* continuer, etat_t* etat, float* widthFactor, float* heightFactor, int* textInputActive, 
                int* isValid, int* keyCounts, int* ancien, int* etatAge, int* ancienSon);
void touches(SDL_Event evenement, int* textInputActive, int* keyCounts, int* isValid, char* textInput,const char* ipPattern);

int validateRegex(const char *input, const char *pattern);

/* fonction de la gestion en jeu */
void reinitialiser_partie(player_t ** player, ordi_t ** ordi);
int fin_partie(player_t * player, ordi_t * ordi, player_t * player_online, int etat);

#endif
