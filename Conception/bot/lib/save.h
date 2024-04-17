#ifndef _SAVE_H_
#define _SAVE_H_

#include "ordinateur.h"
#define MAX_SAVE 5

/*
 * Chemin fichier de sauvagerde / chargement
 */
#define FICHIER_1 "save/save1.txt"
#define FICHIER_2 "save/save2.txt"

booleen_t save(ordi_t * ordi, player_t * player);
booleen_t load(ordi_t ** ordi, player_t ** player, character_t * tab);

#endif