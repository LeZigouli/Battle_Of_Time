#ifndef _JEU_AFF_H_
#define _JEU_AFF_H_

/**************/
/*--Includes--*/
/**************/
#include "commun_SDL.h"
#include "affichage_menu.h"
#include "player.h"
#include "ordinateur.h"

/***************/
/*--Fonctions--*/
/***************/
void afficherHUD(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police_texte, SDL_Texture* parametre, 
                 SDL_Texture* upgrade, SDL_Texture* gold, SDL_Texture* xp, player_t* joueur, SDL_Texture** image);

void afficherJeuFond(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* fond_jeu, int* cameraX, int* cameraY);

void gestionAffichageFondJeu(SDL_Renderer* rendu, SDL_Window* fenetre, int* etatAge, 
                             SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age,
                             SDL_Texture* moderne, SDL_Texture* futuriste, player_t* j1, ordi_t* o,
                             int* cameraX, int* cameraY);

void afficherOptionJeu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre);

void img_charactere_inser(tab_charactere_t * characters,building_t * building, SDL_Texture* img_c[], SDL_Texture* tab[]);

void affichageSprite(SDL_Renderer* rendu, player_t* j1, ordi_t* o, SDL_Rect* playerImg, SDL_Rect* ordiImg, int attaque,
                     SDL_Rect playerPosition[], SDL_Rect ordiPosition[], int* upgrade_j, character_t* tab_de_charactere,
                     SDL_Texture* image[], SDL_Texture* img_char[], SDL_Texture* img_c_ordi[], Uint32 currentTime, Uint32* lastMovement,
                     int w, int h, int* cameraX, int* cameraY);

#endif