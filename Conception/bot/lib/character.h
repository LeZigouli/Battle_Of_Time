/**
 * \file character.h
 * \brief Contient les élements utilisés par le character.c
 * \author Proudy Vincent
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <math.h>
#include "building.h"
/**
 * @brief Valeur initiale pour le propriétaire d'un personnage.
 */
#define OWNER_INIT -1

/**
 * @brief Ratio utilisé pour le calcul des ressources.
 */
#define RATIO_RESSOURCES 1.4

/**
 * @brief Taille d'un sprite en pixels.
 */
#define TAILLE_SPRITE 64

/**
 * @brief Taille de l'attaque en pixels.
 */
#define TAILLE_ATTAQUE (TAILLE_SPRITE * 3)

/**
 * @brief Structure représentant un personnage.
 */
typedef struct character_s {
    int age;                        /**< Âge du personnage. */
    int classe;                     /**< Classe du personnage. */
    int cost;                       /**< Coût du personnage. */
    int dammage;                     /**< Dégâts infligés par le personnage. */
    char description[MAX_DESCRIPTION]; /**< Description du personnage. */
    int max_pv;                     /**< Points de vie maximum du personnage. */
    char name[MAX_STR];             /**< Nom du personnage. */
    int owner;                      /**< Propriétaire du personnage. */
    int pv;                         /**< Points de vie actuels du personnage. */
    float ratio_ressources;          /**< Ratio de ressources du personnage. */
    char sprite[MAX_DESCRIPTION];   /**< Sprite du personnage. */
    int time;                       /**< Temps de jeu du personnage. */
    int vector;                     /**< Vecteur du personnage. */
    int x;                          /**< Position horizontale du personnage. */
    int x_pred;                     /**< Position horizontale précédente du personnage. */
    int y;                          /**< Position verticale du personnage. */
} character_t;

character_t * initcharacter();
booleen_t copie_character(character_t ** destination, character_t * src);
booleen_t destroy_tab_character(character_t ** tab );

booleen_t character_attack_character(character_t ** destination, character_t ** src);
booleen_t character_attack_building(building_t ** destination, character_t ** src);

void deplacement_gauche(character_t ** character);
void deplacement_droit(character_t ** character);


#endif