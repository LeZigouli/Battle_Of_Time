#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "common.h"

character_t * initcharacter();
booleen_t copie_character(character_t ** destination, character_t * src);
booleen_t destroy_tab_character(character_t ** tab );

booleen_t character_attack_character(character_t ** destination, character_t ** src);
booleen_t character_attack_building(building_t ** destination, character_t ** src);

void deplacement_gauche(character_t ** character);
void deplacement_droit(character_t ** character);


#endif