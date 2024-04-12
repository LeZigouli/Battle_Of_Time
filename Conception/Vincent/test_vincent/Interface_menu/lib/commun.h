#ifndef _COMMUN_H_
#define _COMMUN_H_

/**************/
/*--Includes--*/
/**************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <regex.h>

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

/*Structure menu Resolution*/
typedef struct {
    SDL_Rect rect; // Rectangle représentant l'élément
    char* info; // Informations spécifiques à l'élément
    int w;
    int h;
} element_t;

/*Énumération des états de menu*/
typedef enum MenuState {
    MENU_PRINCIPAL,
    MENU_SOUS,
    MENU_SOUS_JOUER,
    MENU_SOUS_OPTIONS,
    MENU_SOUS_RESOLUTION,
    MENU_SOUS_CREDITS,
    MENU_SOUS_SON,
    MENU_SOUS_SOLO,
    MENU_SOUS_ENLIGNE,
    MENU_SOUS_REJOINDRE
}etatMenu_t;

#endif