#include "../lib/common.h"
#include "../lib/building.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/

/* verifier si les characters sont valides */
booleen_t invalid_characters(player_t * player)
{
	return ( player->characters == NULL || player->characters->nb == 0 || player->characters->tab == NULL ) ? TRUE : FALSE;
}

/* initialisation du joueur */
player_t * initplayer(int difficulty)
{
	player_t * main_player = malloc(sizeof(player_t));

	strcpy(main_player->name,"Player 1");
	main_player->owner = 1;
	main_player->xp = 0;
	main_player->characters = NULL;

	switch(difficulty){
		case EASY:
			main_player->gold = 800;
			break;
		case MEDIUM:
			main_player->gold = 600;
			break;

		case HARD:
			main_player->gold = 400;
			break;
		
		default:
			printf("Erreur a l'initialisation du JOUEUR ( difficulty )\n");
			break;
	}

	init_building(&main_player);

	return main_player;
}

/* verifier qu'un pointeur passer en parametre existe */
booleen_t exist(void * type)
{
	return (type == NULL) ? FALSE : TRUE;
}

booleen_t buy_character(player_t ** player, character_t tab_character[NB_AGE*NB_CHARACTER], int currently_age, int x, int y)
{

	/* verification préliminaire */

	/* si l'objet player n'existe pas */
	if( !exist((*player)) )
	{
		return FALSE;
	}

	/* si les characters n'a pas été encore initialiser, alors on le fait ici */
	if( !exist((*player)->characters) )
	{
		(*player)->characters = malloc(sizeof(character_t *) * MAX_POSSESSED);
		(*player)->characters->nb = 0;

		if( (*player)->characters == NULL )
		{
			printf("ERREUR : allocation dynamique>characters character !\n");
			return FALSE;
		}
	}
	
	/* verification des informations donnée en parametre */
	if( x < 0 || x >NB_AGE || y < 0 || y > NB_CHARACTER || currently_age < 0 || currently_age > NB_AGE)
	{
		return FALSE;
	}

	if( currently_age != x )
	{
		return FALSE;
	}

	/* on peut passer au traitement */
	/* le joueur souhaite acheter a l'age X le personnage Y */

	/* on verifie que la>characters n'est pas pleine */
	if ( (*player)->characters->nb >= MAX_POSSESSED )
	{
		printf("ERREUR :>characters pleine impossible de rajouter un personnage !\n");
		return FALSE;
	}

	if ( (*player)->gold - tab_character[x*NB_AGE+y].cost < 0 ){
		printf("ERREUR : Pas assez de gold pour acheter ce character\n");
		return FALSE;
	}
	/* on alloue de la mémoire pour une place dans le tableau de pointeur sur character_t */

	(*player)->characters->tab[(*player)->characters->nb] = malloc(sizeof(character_t));

	if( (*player)->characters->tab[(*player)->characters->nb] == NULL )
	{
		printf("ERREUR : allocation du pointeur sur character dans la>characters !\n");
	}  

	/* passage par une variable locale pour plus de lisibilté */
	int nb_character = (*player)->characters->nb;

	/* on ajoute le characters a notre tableau */
	(*(*player)->characters->tab[nb_character]) = tab_character[x*NB_CHARACTER+y];

	/* on soustrait le cout du character au gold du joueur */
	(*player)->gold -= (*player)->characters->tab[nb_character]->cost;

	/* on affecte au character le numéro OWNER pour s'avoir qui est le propriétaire */
	(*player)->characters->tab[nb_character]->owner = (*player)->owner;

	/* on incremente le nombre de character dans le tableau */
	(*player)->characters->nb+=1;

	return TRUE;
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

	/* on detruit le pointeur sur struct building */
	free( (*player)->building );
	(*player)->building = NULL;

	/* on detruit le pointeur sur les characters */
	free((*player)->characters);
	(*player)->characters = NULL;

	/* destruction du pointeur sur le joueur */
	free((*player));
	(*player) = NULL;
}

/* fonction pour tasser les éléments d'un tableau */
booleen_t tasser_tab( player_t **  player, int indice_dep)
{
	if( !exist((*player)) )
	{
		return FALSE;
	}

	if( invalid_characters( (*player) ) )
	{
		return FALSE;
	}

	/* on tasse le tableau a partir de l'indice de depart */
	for ( int i=indice_dep; i<(*player)->characters->nb; i++ )
	{
		(*player)->characters->tab[i] = (*player)->characters->tab[i+1];
	}

	return TRUE;
}

/* supprimer les personnages qui sont mort */
booleen_t delete_character(player_t ** player)
{
	/* verification préliminaire */
	if( player == NULL || (*player) == NULL )
	{
		return FALSE;
	}

	if( invalid_characters( (*player) ) )
	{
		return FALSE;
	}

	/*
	 * on va chercher dans la>characters un character avec des PV <=0
	 * si on trouve, on le supprime
	 * sinon, on retourne faux
	 */

	int nb_avant = (*player)->characters->nb;

	for( int i=0; i<(*player)->characters->nb; i++ )
	{
		if ( (*player)->characters->tab[i]->pv <= 0 )
		{
			/*
			 * si un character est mort, on le free et on decremente le nb de character contenu
			 * dans le tableau
 			 */
			free((*player)->characters->tab[i]);
			(*player)->characters->tab[i] = NULL;

			/* 
			 * il faut penser a tasser le tableau pour pas perdre d'information car on s'arrete
			 * sur le premier qui valide la condition
			 */

			if( tasser_tab(player,i) )
			{
				printf("\nLe tableau a bien ete tasse !\n");
			}	

			(*player)->characters->nb-=1;
		}
	}

	return ( nb_avant == (*player)->characters->nb ) ? FALSE : TRUE;
}





















































