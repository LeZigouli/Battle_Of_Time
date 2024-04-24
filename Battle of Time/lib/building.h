/**
 * \file building.h
 * \brief Contient les élements utilisés par le building.c
 * \author Proudy Vincent
 * \date 02 avril 2024
 * \version 1.0
 * 
*/
#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "common.h"

/**
 * @brief Structure représentant un bâtiment.
 */
typedef struct building_s {
    int pv;         /**< Points de vie du bâtiment. */
    int owner;      /**< Propriétaire du bâtiment. */
    int dammage;     /**< Dégâts infligés par le bâtiment. */
    int max_pv;     /**< Points de vie maximum du bâtiment. */
    int XP_cost;    /**< Coût en expérience pour améliorer le bâtiment. */
    int level;      /**< Niveau du bâtiment. */
} building_t;


booleen_t init_building(building_t ** building, int owner);
booleen_t upgrade_building(building_t ** building,int * xp);
booleen_t afficher_building(building_t * building);
int max(int a, int b);

#endif