#ifndef _HELP_H_
#define _HELP_H_

#include "common.h"

booleen_t afficher_player(player_t * player);
booleen_t afficher_characters_player(tab_charactere_t * characters);

void afficher_character(character_t character);
booleen_t afficher_all_character(character_t * tab);

booleen_t afficher_building(player_t * player);

#endif