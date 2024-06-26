/**
 * \file affichage_menu.h
 * \brief Contient les élements utilisés par le affichage_menu.c
 * \author Poirier Victor
 * \date 18 avril 2024
 * \version 1.0
 * 
*/
#ifndef _MENU_AFF_H_
#define _MENU_AFF_H_

/**************/
/*--Includes--*/
/**************/
#include "commun_SDL.h"
#include "gestion.h"
#include "player.h"
#include "ordinateur.h"
#include "../socket/serveur.h"

/***************/
/*--Fonctions--*/
/***************/
void affichage(etat_t* etat, int* etatAge, SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police , TTF_Font* police_texte, 
               int menuX, int menuY, element_t* elm_reso, int* selecElement, const char* effet, char* textInput, 
               int* isValid, int* keyCounts, SDL_Texture* parametre, SDL_Texture* gold, SDL_Texture* xp,
               SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age,
               SDL_Texture* moderne, SDL_Texture* futuriste, player_t* joueur, SDL_Texture** sprite_hud, SDL_Texture* upgrade,
               ordi_t* ordi, int* cameraX, int* cameraY, SDL_Texture* ultim, SDL_Texture* building[], int fin_partie, SDL_Texture * win,
               SDL_Texture * lose, character_t* tab_charactere, int survol, Uint32 delai_ulti, Uint32 diff_time, int** troupe_formee,
               Uint32 currentTime, Uint32** lastTroupe, int** nb, player_t * j2, SDL_Texture* image_ultim, float* alpha);

void afficherMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte, int x, int y, int largeur, int hauteur);
void afficherSousMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3, const char* texte4);
void afficherSousMenuResolution(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre);
void afficherTitre(SDL_Renderer* rendu, SDL_Window* fenetre, int x, int y, int largeur, int hauteur);
void initElements(SDL_Renderer* rendu, SDL_Window* fenetre, element_t* elm_reso);
void resolution(SDL_Renderer* rendu, SDL_Window* fenetre , TTF_Font* police, element_t* elm_reso, int* selecElement);
void afficherSousMenuCredits(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police);
void afficherSousMenuOption(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3);
void afficherSousMenuSon(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte);
void afficherSousMenuJouer(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police);
void afficherSousMenuSolo(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police);
void afficherSousMenuEnLigne(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police);
void afficherSousMenuRejoindre(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police, char* textInput, int* isValid, int* keyCounts);
void afficherSousMenuDifficulte(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police);
void afficherSousMenuCreer(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police);

#endif
