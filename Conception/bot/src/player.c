#include "../lib/player.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/

/* initialisation du joueur */
player_t * initplayer(int owner)
{
	player_t * main_player = malloc(sizeof(player_t));
	
	char name[MAX_STR] = "Player";

	if ( owner == OWNER_1 )
	{
		strcat(name,"1");
	}
	if ( owner == OWNER_2 )
	{
		strcat(name,"2");
	}

	strcpy(main_player->name,name);
	main_player->owner = owner;
	main_player->xp = 100000;
	main_player->debut=DELAI_INITIAL;
	main_player->characters = malloc(sizeof(tab_charactere_t));
	main_player->file_attente = malloc(sizeof(tab_charactere_t));

	/*vérification des bonne alloction mémoire*/
	if(main_player->characters == NULL || main_player->file_attente == NULL){
		free(main_player->characters);
		free(main_player->file_attente);
		free(main_player);
		return NULL;
	}
	/* Mise à NULL des pointeur pour éviter des pointeur fous*/
	for(int i=0;i<MAX_POSSESSED;i++){
		main_player->characters->tab[i]=NULL;
		main_player->file_attente->tab[i]=NULL;
	}
	main_player->characters->nb=0;
	main_player->file_attente->nb=0;

	init_building(&(main_player->building),owner);

	return main_player;
}

/* libérer la memoire... */
void destroy_player(player_t ** player)
{	
	/* on detruit chaque pointeurs sur character_t contenu dans le tab */
	for ( int i=0; i< (*player)->characters->nb ;i++)
	{
		free((*player)->characters->tab[i]);
		(*player)->characters->tab[i] = NULL;
	}
	for ( int i=0; i< (*player)->file_attente->nb ;i++)
	{
		free((*player)->file_attente->tab[i]);
		(*player)->file_attente->tab[i] = NULL;
	}

	/* on detruit le pointeur sur struct building */
	free( (*player)->building );
	(*player)->building = NULL;

	/* on detruit le pointeur sur les characters */
	free((*player)->characters);
	free((*player)->file_attente);
	(*player)->characters = NULL;

	/* destruction du pointeur sur le joueur */
	free((*player));
	(*player) = NULL;
}

booleen_t buy_character(player_t ** player, character_t tab_character[NB_AGE*NB_CHARACTER], int newCha)
{

	/* verification préliminaire */

	/* si l'objet player n'existe pas */
	if( !exist((*player)) )
	{
		return FALSE;
	}
	
	/* verification des informations donnée en parametre */
	if(newCha < 0 || newCha > NB_CHARACTER)
	{
		return FALSE;
	}

	/* on peut passer au traitement */
	/* le joueur souhaite acheter a l'age X le personnage Y */

	/* on verifie que la>characters n'est pas pleine */
	if ( (*player)->characters->nb+(*player)->file_attente->nb >= MAX_POSSESSED )
	{
		printf("ERREUR :>characters pleine impossible de rajouter un personnage !\n");
		return FALSE;
	}

	if ( (*player)->gold - tab_character[(*player)->building->level*NB_AGE+newCha].cost < 0 ){
		printf("ERREUR : Pas assez de gold pour acheter ce character\n");
		return FALSE;
	}
	/* on alloue de la mémoire pour une place dans le tableau de pointeur sur character_t */

	(*player)->file_attente->tab[(*player)->file_attente->nb] = malloc(sizeof(character_t));

	if( (*player)->file_attente->tab[(*player)->file_attente->nb] == NULL )
	{
		printf("ERREUR : allocation du pointeur sur character dans la>characters !\n");
		return FALSE;
	}

	
	/* passage par une variable locale pour plus de lisibilté */
	int nb_character = (*player)->file_attente->nb;

	/* on ajoute le characters a notre tableau */
	copie_character( &(*player)->file_attente->tab[nb_character], &tab_character[(*player)->building->level*NB_CHARACTER+newCha]);

	/* on soustrait le cout du character au gold du joueur */
	(*player)->gold -= (*player)->file_attente->tab[nb_character]->cost;

	/* on affecte au character le numéro OWNER pour s'avoir qui est le propriétaire */
	(*player)->file_attente->tab[nb_character]->owner = (*player)->owner;

	if((*player)->owner == OWNER_2){
		(*player)->file_attente->tab[nb_character]->x = POS_DEP_AD;
	}else{
		(*player)->file_attente->tab[nb_character]->x = POS_DEP;
	}

	/* on incremente le nombre de character dans le tableau */
	(*player)->file_attente->nb++;
	
	envoie_char(player);
	return TRUE;
}

void envoie_char(player_t ** player){
	/*Formation des troupes*/
	if((*player)->file_attente->nb > 0){
		(*player)->delai=(*player)->file_attente->tab[0]->time;
		if((*player)->debut==DELAI_INITIAL)
			(*player)->debut=time(NULL);
		(*player)->fin=time(NULL);
		if(difftime((*player)->fin,(*player)->debut)>= (*player)->delai){
			(*player)->characters->tab[(*player)->characters->nb]=(*player)->file_attente->tab[0];
			for(int i = 0; i<(*player)->file_attente->nb-1;i++){
				(*player)->file_attente->tab[i]=(*player)->file_attente->tab[i+1];
			}
			(*player)->file_attente->nb--;
			(*player)->characters->nb++;
			(*player)->debut=DELAI_INITIAL;
		}
	}
}

/* verifier qu'un pointeur passer en parametre existe */
booleen_t exist(void * type)
{
	return (type == NULL) ? FALSE : TRUE;
}

/* recuperer les gold et xp a la mort d'un character */
booleen_t get_ressources(player_t * player1, player_t * player2)
{
	if (player1 == NULL || player2 == NULL)
	{
		return FALSE;
	}

	if(player1->characters==NULL || player2->characters==NULL)
		return FALSE;

	int gain;
	for(int i=0;i < player1->characters->nb;i++){
		if ( player1->characters->tab[i]->pv <= 0 )
		{
			/*
			* le character appartient au player1
			* et les ressources vont donc au player2
			*/
			player2->gold += gain =( player1->characters->tab[i]->cost * player1->characters->tab[i]->ratio_ressources );
			player2->xp+=gain;
		}
	}
	for(int i=0;i < player2->characters->nb;i++){
		if(player2->characters->tab[i]->pv <=0)
		{
			/*
			* le character appartient au player2
			* et les ressources vont donc au player1
			*/
			player1->gold += gain =( player2->characters->tab[i]->cost * player2->characters->tab[i]->ratio_ressources );
			player1->xp+=gain;
		}
	}
	return TRUE;
}


booleen_t afficher_player(player_t * player)
{
    if ( player == NULL )
    {
        return FALSE;
    }
    printf("<----- Player ----->\n");
	printf("Nom : %s\nPV : %d\nXP : %d\nGOLD : %f\nOwner : %d\n",player->name,player->building->pv,player->xp,player->gold,player->owner);
	printf("debut : %ld, fin : %ld delai : %d difftime: %f\n\n",player->debut,player->fin,player->delai,difftime(player->fin,player->debut));
    afficher_building(player->building);
    afficher_characters(player->characters);
	afficher_characters(player->file_attente);
    return TRUE;
}


