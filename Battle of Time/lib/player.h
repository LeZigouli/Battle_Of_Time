/**
 * \file player.h
 * \brief Contient les élements utilisés par les autres fichiers 
 * \author Proudy Vincent
 * \date 10 avril 2024
 * \version 1.0
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "tab_character.h"


/**
 * \struct player_t
 * \brief Structure représentant un joueur.
 */
typedef struct {
    char name[MAX_STR]; /**< Nom du joueur */
    int xp; /**< Expérience du joueur */
    int delai; /**< Délai pour former les troupes */
    unsigned long int debut; /**< Début du délai */
    unsigned long int fin; /**< Fin du délai */
    float gold; /**< Quantité d'or du joueur */
    int owner; /**< Numéro propriétaire du joueur */
    tab_charactere_t * characters; /**< Tableau des personnages du joueur */
    tab_charactere_t * file_attente; /**< File d'attente des personnages à former */
    building_t * building; /**< Bâtiment du joueur */
} player_t;

player_t * initplayer(int owner);
void destroy_player(player_t ** player);
booleen_t buy_character(player_t ** player, character_t tab_character[NB_AGE*NB_CHARACTER], int newCha);
void envoie_char(player_t ** player);


booleen_t exist(void * type);
booleen_t get_ressources(player_t * player1, player_t * player2);

booleen_t afficher_player(player_t * player);

#endif