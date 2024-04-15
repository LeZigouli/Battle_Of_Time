#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "tab_character.h"


typedef struct{

	char name[MAX_STR];
	int xp;
	int delai;
	unsigned long int debut;
	unsigned long int fin;
	float gold;
	int owner; 
	tab_charactere_t * characters;
	tab_charactere_t * file_attente;
	building_t * building;

}player_t;

player_t * initplayer(int owner);
void destroy_player(player_t ** player);
booleen_t buy_character(player_t ** player, character_t tab_character[NB_AGE*NB_CHARACTER], int newCha);
void envoie_char(player_t ** player);


booleen_t exist(void * type);
booleen_t get_ressources(player_t * player1, player_t * player2);

booleen_t afficher_player(player_t * player);

#endif