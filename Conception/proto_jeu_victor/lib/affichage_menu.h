#ifndef _MENU_AFF_H_
#define _MENU_AFF_H_

/**************/
/*--Includes--*/
/**************/
#include "commun_SDL.h"
#include "gestion.h"
#include "player.h"
#include "ordinateur.h"

/***************/
/*--Fonctions--*/
/***************/
void affichage(etat_t etat, int* etatAge, SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police , TTF_Font* police_texte, 
               int menuX, int menuY, element_t* elm_reso, int* selecElement, const char* effet, char* textInput, 
               int* isValid, int* keyCounts, SDL_Texture* parametre, SDL_Texture* gold, SDL_Texture* xp,
               SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age,
               SDL_Texture* moderne, SDL_Texture* futuriste, player_t* joueur, SDL_Texture** image, SDL_Texture* upgrade,
               ordi_t* ordi);

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

#endif