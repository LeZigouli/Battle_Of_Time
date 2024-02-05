#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "common.h"

player_t * initplayer(int difficulty, int owner);
void destroy_player(player_t ** player);
booleen_t buy_character(player_t ** player, character_t tab_character[NB_AGE*NB_CHARACTER], int currently_age, int x, int y);
booleen_t invalid_characters(player_t * player);
booleen_t delete_character(player_t ** player, player_t ** player2 );
booleen_t exist(void * type);
booleen_t tasser_tab( player_t **  player, int indice_dep);
booleen_t get_ressources(player_t ** player1, player_t ** player2, character_t * character);

#endif