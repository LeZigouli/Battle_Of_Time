#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "building.h"

typedef struct character_s character_t;
struct character_s{

	int pv;
	char name[MAX_STR];
	int time; 
	int cost; 
	int max_pv;
	float ratio_ressources;
	int dammage;
	int owner; 
	char description[MAX_DESCRIPTION];
	int x;
	int y;
	int vector;
	char sprite[MAX_DESCRIPTION]="../img/";

	/* pointeur sur fonction pour le deplacement */
	void (*deplacement_gauche)(character_t **);
	void (*deplacement_droit)(character_t **);

	/* pointeur sur fonction pour attaquer */
	booleen_t (*attack_character)(character_t **, character_t **);
	booleen_t (*attack_building)(building_t **, character_t **);

};

character_t * initcharacter();
booleen_t copie_character(character_t ** destination, character_t * src);
booleen_t destroy_tab_character(character_t ** tab );

booleen_t character_attack_character(character_t ** destination, character_t ** src);
booleen_t character_attack_building(building_t ** destination, character_t ** src);

void deplacement_gauche(character_t ** character);
void deplacement_droit(character_t ** character);


#endif