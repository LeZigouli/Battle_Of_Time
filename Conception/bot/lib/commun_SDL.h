#ifndef _COMMUN_H_
#define _COMMUN_H_

/**************/
/*--Includes--*/
/**************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <regex.h>

/************/
/*--Macros--*/
/************/
/*Dimensions des images de fonds*/
#define IMAGE_WIDTH 3840 
#define IMAGE_HEIGHT 720
/*Vitesse de du déplacement de la caméra*/
#define SCROLL_SPEED 30
/*Dimensions de base de la fenêtre*/
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
/*Taille des éléments du menu*/
#define MENU_WIDTH 250
#define MENU_HEIGHT 60
#define MENU_DECALAGE 50 /*Décalage pour abaisser le menu*/
#define SPACING 30   /*Espace entre chaque sous-menu*/

#define ELEMENT_WIDTH 100 /*Largeur d'un élément*/
#define ELEMENT_HEIGHT 50 /*Hauteur d'un élément*/
#define ELEMENT_SPACING 20 /*Espacement entre les éléments*/

#define POS_DEP 170 /*Spawn des caractères du joueur*/
#define POS_DEP_AD IMAGE_WIDTH - 300 /*Spawn des caractères de l'adversaire*/

#define MOVEMENT_DURATION 100 /*Durée du mouvement en millisecondes des sprites*/

/*Code couleur */
#define BLACK (SDL_Color){0, 0, 0}
#define WHITE (SDL_Color){255, 255, 255}
#define GREEN (SDL_Color){0, 255, 0}
#define RED   (SDL_Color){255, 0, 0}

/*Structure menu Resolution*/
typedef struct {
    SDL_Rect rect; // Rectangle représentant l'élément
    char* info; // Informations spécifiques à l'élément
    int w;
    int h;
} element_t;

/*Énumération des états de menu*/
typedef enum etat_s {
    PAGE_ACCUEIL,
    MENU_PRINCIPAL,
    MENU_SOUS_JOUER,
    MENU_SOUS_OPTIONS,
    MENU_SOUS_RESOLUTION,
    MENU_SOUS_CREDITS,
    MENU_SOUS_SON,
    MENU_SOUS_SOLO,
    MENU_SOUS_ENLIGNE,
    MENU_SOUS_REJOINDRE,
    MENU_SOUS_CREER,
    MENU_SOUS_CREER_VALIDE,
    MENU_DIFFICULTE,
    JOUER,
    OPTION_JEU,
    MENU_SAUVEGARDER,
    JOUER_RESEAU_CREER,
    JOUER_CHARGER,
    JOUER_RESEAU_REJOINDRE
}etat_t;

/*Énumération des ages du jeu*/
typedef enum age_s { Prehistoire, Antiquite, Moyen_Age, Ere_Moderne, Ere_Futuriste }age_t;

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

void destruction_SDL(SDL_Texture* parametre, SDL_Texture* gold, SDL_Texture* xp, SDL_Texture* textureFond, 
                     SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age, SDL_Texture* moderne,
                     SDL_Texture* futuriste, TTF_Font* police, TTF_Font* police_texte, SDL_Renderer* rendu,
                     SDL_Window* fenetre, Mix_Chunk* click, Mix_Chunk* music, SDL_Texture* sprite_hud[], SDL_Texture* building[]);


#endif