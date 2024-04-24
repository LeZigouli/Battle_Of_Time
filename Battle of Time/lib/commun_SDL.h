/**
 * \file commun_SDL.h
 * \brief Contient les élements utilisés par les autres fichiers SDL
 * \author Poirier Victor
 * \date 10 avril 2024
 * \version 1.0
 * 
*/
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


/*Dimensions des images de fonds*/
#define IMAGE_WIDTH 3840 /**< Largeur des images de fond */
#define IMAGE_HEIGHT 720 /**< Hauteur des images de fond */
/*Vitesse du déplacement de la caméra*/
#define SCROLL_SPEED 30 /**< Vitesse du défilement */
/*Dimensions de base de la fenêtre*/
#define WINDOW_WIDTH 1080 /**< Largeur de la fenêtre */
#define WINDOW_HEIGHT 720 /**< Hauteur de la fenêtre */
/*Taille des éléments du menu*/
#define MENU_WIDTH 250 /**< Largeur des éléments de menu */
#define MENU_HEIGHT 60 /**< Hauteur des éléments de menu */
#define MENU_DECALAGE 50 /**< Décalage pour abaisser le menu */
#define SPACING 30 /**< Espace entre chaque sous-menu */

#define ELEMENT_WIDTH 100 /**< Largeur d'un élément */
#define ELEMENT_HEIGHT 50 /**< Hauteur d'un élément */
#define ELEMENT_SPACING 20 /**< Espacement entre les éléments */

#define POS_DEP 170 /**< Position d'apparition des personnages du joueur */
#define POS_DEP_AD IMAGE_WIDTH - 300 /**< Position d'apparition des personnages adverses */

#define MOVEMENT_DURATION 100 /**< Durée du mouvement du sprite en millisecondes */
#define DELAI_ULTI 180000 /**< Délai entre deux utilisations d'ultime */

#define AUCUN_ACTION -1 /**< Aucune action */
#define ACHAT_CHARACTER 0 /**< Achat d'un personnage */
#define PASSAGE_AGE 1 /**< Transition d'âge */
#define ULTI 2 /**< Action ultime */

/*Couleurs */
#define BLACK (SDL_Color){0, 0, 0} /**< Couleur noire */
#define WHITE (SDL_Color){255, 255, 255} /**< Couleur blanche */
#define GREEN (SDL_Color){0, 255, 0} /**< Couleur verte */
#define RED (SDL_Color){255, 0, 0} /**< Couleur rouge */

/*Structure du menu Resolution*/
typedef struct {
    SDL_Rect rect; /**< Rectangle représentant l'élément */
    char *info; /**< Informations spécifiques à l'élément */
    int w; /**< Largeur de l'élément */
    int h; /**< Hauteur de l'élément */
} element_t;

/*Énumération des états de menu*/
typedef enum etat_s {
    PAGE_ACCUEIL, /**< Page d'accueil */
    MENU_PRINCIPAL, /**< Menu principal */
    MENU_SOUS_JOUER, /**< Sous-menu Jouer */
    MENU_SOUS_OPTIONS, /**< Sous-menu Options */
    MENU_SOUS_RESOLUTION, /**< Sous-menu Résolution */
    MENU_SOUS_CREDITS, /**< Sous-menu Crédits */
    MENU_SOUS_SON, /**< Sous-menu Son */
    MENU_SOUS_SOLO, /**< Sous-menu Solo */
    MENU_SOUS_ENLIGNE, /**< Sous-menu En ligne */
    MENU_SOUS_REJOINDRE, /**< Sous-menu Rejoindre */
    MENU_SOUS_CREER, /**< Sous-menu Créer */
    MENU_SOUS_CREER_VALIDE, /**< Sous-menu Valider la création */
    MENU_DIFFICULTE, /**< Menu de sélection de la difficulté */
    JOUER, /**< Jouer */
    ULTIME,
    OPTION_JEU, /**< Options du jeu */
    MENU_SAUVEGARDER, /**< Menu de sauvegarde */
    JOUER_RESEAU_CREER, /**< Jouer en réseau (création) */
    JOUER_CHARGER, /**< Charger une partie */
    JOUER_RESEAU_REJOINDRE, /**< Jouer en réseau (rejoindre) */
    FIN_PARTIE /**< Fin de partie */
} etat_t;

/*Énumération pour le survol des éléments*/
typedef enum survol_s {
    PERSO1, /**< Personnage 1 */
    PERSO2, /**< Personnage 2 */
    PERSO3, /**< Personnage 3 */
    PERSO4, /**< Personnage 4 */
    XP, /**< Expérience */
    ULTIM /**< Ultime */
} survol_t;

/*Énumération des âges du jeu*/
typedef enum age_s {Prehistoire, Antiquite, Moyen_Age, Ere_Moderne, Ere_Futuriste} age_t;

/*Pour la gestion du volume*/
SDL_bool estLache; /**< Drapeau indiquant si le bouton est relâché */
int volume; /**< Niveau de volume */
SDL_Rect *volumeBar; /**< Barre de volume */
SDL_Rect *volumeCursor; /**< Curseur de volume */


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
                     SDL_Window* fenetre, Mix_Chunk* click, Mix_Chunk* music, SDL_Texture* sprite_hud[], 
                     SDL_Texture* building[], SDL_Texture* win, SDL_Texture* lose, SDL_Texture* boum);

#endif
