/**
 * \file tab_character.h
 * \brief Definition de la structure contenant plusieur character_t et ses fonction d'accès.
 * \author Proudy Vincent et Roquain Louison
 * \date 09 avril 2024
 * \version 1.0
 * 
*/

#ifndef TAB_CHARACTER_H_
#define TAB_CHARACTER_H_


#include "character.h"


/**
 * \struct tab_charactere_t
 * \brief Structure qui contient un tableau de charactere.
 */
typedef struct tab_charactere_s {
    character_t * tab[MAX_POSSESSED]; /**< Tableau de personnages */
    int nb; /**< Nombre de personnages dans le tableau */
    int ind_first_vivant;
} tab_charactere_t;

void deplacement(tab_charactere_t * characters, character_t * first_Adverser, int x_building_adverser);
booleen_t delete_character(tab_charactere_t ** characters);
booleen_t tasser_tab( tab_charactere_t **  characters, int nb_mort);
booleen_t afficher_characters(tab_charactere_t * characters);
booleen_t ulti(tab_charactere_t ** cible);
void maj_first_vivant(tab_charactere_t * player, tab_charactere_t * ordi);

#endif