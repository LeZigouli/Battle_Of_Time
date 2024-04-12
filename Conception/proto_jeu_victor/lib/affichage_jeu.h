#ifndef _JEU_AFF_H_
#define _JEU_AFF_H_

/**************/
/*--Includes--*/
/**************/
#include "commun_SDL.h"
#include "affichage_menu.h"

/***************/
/*--Fonctions--*/
/***************/
void afficherHUD(SDL_Renderer* rendu, SDL_Window* fenetre);
void afficherJeuFond(SDL_Renderer* rendu, SDL_Window* fenetre, char* path);
void gestionAffichageFondJeu(SDL_Renderer* rendu, SDL_Window* fenetre, age_t etatAge);
void afficherOptionJeu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre);

#endif