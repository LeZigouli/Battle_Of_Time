#include "character.c"
#include "common.h"

typedef struct{

	char name[MAX_STR];
	int pv;
	long int xp;
	int gold; 
	t_character possessed[MAX_POSSESSED];
	int owner;

}t_player;


t_player * init_player(int difficulty){

	t_player * main_player = malloc(sizeof(t_player));

	strcpy(main_player->name,"Player 1");
	main_player->owner = 1;
	main_player->xp = 0;

	switch(difficulty){
		case EASY:
			main_player->gold = 600;
			break;
		case MEDIUM:
			main_player->gold = 400;
			break;

		case HARD:
			main_player->gold = 200;
			break;
		
		default:
			printf("Erreur a l'initialisation du JOUEUR ( difficulty )\n");
			break;
	}

	return main_player;

}

void memory(t_player ** a){
	
}
