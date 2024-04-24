/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 12 avril 2024
 * \version 1.0
 * 
*/
#ifndef _ORDINATEUR_H_
#define _ORDINATEUR_H_

#include "player.h"

#define MAX_DELAI 15 /*en secondes*/
#define MIN_DELAI 1
#define MAX_DELAI_ULTI 900 /* 15 min*/
#define MIN_DELAI_ULTI 300 /*  5 min*/

/**
 * @brief Structure représentant un adversaire contrôlé par l'ordinateur.
 */
typedef struct {
    int owner; /**< Numéro du propriétaire */
    int difficulte; /**< Niveau de difficulté */
    int delai; /**< Délai pour former les troupes */
    int xp; /**< Points d'expérience */
    int delai_ulti; /**< Délai pour l'utilisation de l'ultime */
    tab_charactere_t * characters; /**< Tableau de personnages */
    building_t * building; /**< Bâtiment */
} ordi_t;

ordi_t * init_ordi();
int detr_ordi(ordi_t ** ordi);
int envoie_char_ordi(ordi_t * ordi, character_t * tab);

booleen_t give_ressources(player_t * player,ordi_t * ordi);

void afficher_ordi(ordi_t * ordi);

void jeu_ordi(ordi_t * o, player_t * p, character_t * tab);

#endif