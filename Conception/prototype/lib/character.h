#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <math.h>
#include "building.h"
#define OWNER_INIT -1
#define RATIO_RESSOURCES 1.4
#define TAILLE_SPRITE 64 /* en pixel */
#define TAILLE_ATTAQUE TAILLE_SPRITE*3

typedef struct character_s character_t;
struct character_s{

	int age;
	int classe;
	int cost; 
	int dammage;
	char description[MAX_DESCRIPTION];
	int max_pv;
	char name[MAX_STR];
	int owner;
	int pv;
	float ratio_ressources;
	char sprite[MAX_DESCRIPTION]; 
	int time; 
	int vector;
	int x;
	int y;
};

character_t * initcharacter();
booleen_t copie_character(character_t ** destination, character_t * src);
booleen_t destroy_tab_character(character_t ** tab );

booleen_t character_attack_character(character_t ** destination, character_t ** src);
booleen_t character_attack_building(building_t ** destination, character_t ** src);

void deplacement_gauche(character_t ** character);
void deplacement_droit(character_t ** character);


#endif