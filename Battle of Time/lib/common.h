/**
 * \file common.h
 * \brief Contient les élements utilisés par les autres fichiers
 * \author Proudy Vincent
 * \date 09 avril 2024
 * \version 1.0
 * 
*/
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "commun_SDL.h"

/**
 * @brief Nombre d'âges et nombre de personnages par âge.
 */
#define NB_AGE 5
#define NB_CHARACTER 4

/**
 * @brief Limite pour les tableaux et chaînes de caractères.
 */
#define MAX_STR 40
#define MAX_POSSESSED 10
#define MAX_DESCRIPTION 100

/**
 * @brief Niveaux de difficulté du jeu.
 */
#define EASY 1
#define MEDIUM 2
#define HARD 3

/**
 * @brief Coefficients pour le niveau de mise à niveau du bâtiment.
 */
#define COEF_LEVEL_UP_DAMMAGE 2.0
#define COEF_LEVEL_UP_MAX_PV 2.0
#define COEF_LEVEL_UP_MAX_GOLD_COST 3

/**
 * @brief Limite du nombre de fois qu'on peut améliorer le bâtiment.
 */
#define MAX_LEVEL_UP 4

/**
 * @brief Numéros de propriétaire.
 */
#define OWNER_1 1
#define OWNER_2 2
#define ORDINATEUR 3

/**
 * @brief Initialisation du délai d'attente pour former les troupes.
 */
#define DELAI_INITIAL -1

/**
 * @brief Codes de fin de partie.
 */
#define JOUEUR_GAGNE 100
#define ORDI_GAGNE 101
#define AUCUN_GAGNANT 102
#define JOUEUR_EN_LIGNE_GAGNE 103

/**
 * @brief Énumération représentant les classes de personnage.
 */
typedef enum class_character_s {
    melee,      /**< Personnage de mêlée. */
    marksman,   /**< Personnage tireur d'élite. */
    tank,       /**< Personnage tank. */
    specialist  /**< Personnage spécialiste. */
} class_character_t;

/**
 * @brief Définition d'un type booléen.
 */
typedef enum booleen_s {
    FALSE,  /**< Valeur booléenne fausse. */
    TRUE    /**< Valeur booléenne vraie. */
} booleen_t;

#endif
