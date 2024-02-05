#include "../lib/common.h"
#include "../lib/building.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/

/* recuperer les gold et xp a la mort d'un character */
booleen_t get_ressources(player_t ** player1, player_t ** player2, character_t * character)
{
	if ( (*player1) == NULL || (*player2) == NULL || character == NULL )
	{
		return FALSE;
	}

	if ( character->pv > 0 )
	{
		/* si le character n'est pas mort */
		return FALSE;
	}

	if ( character->owner == (*player1)->owner )
	{
		/*
		 * le character appartient au player1
		 * et les ressources vont donc au player2
		*/
		(*player1)->gold += ( character->cost * character->ratio_ressources );
	}
	else if ( character->owner == (*player2)->owner )
	{
		/*
		 * le character appartient au player2
		 * et les ressources vont donc au player1
		*/
		(*player2)->gold += ( character->cost * character->ratio_ressources );
	}
	else
	{
		/* erreur dans la distribution des ressources sur la mort du character */
		return FALSE;
	}

	return TRUE;
}

/* verifier si les characters sont valides */
booleen_t invalid_characters(player_t * player)
{
	return ( player->characters == NULL || player->characters->nb == 0) ? TRUE : FALSE;
}

/* initialisation du joueur */
player_t * initplayer(int difficulty, int owner)
{
	player_t * main_player = malloc(sizeof(player_t));
	
	char name[MAX_STR] = "Player ";

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
booleen_t delete_character(player_t ** player, player_t ** player2)
{
	/* verification préliminaire */
	if( player == NULL || (*player) == NULL || player2==NULL || (*player2)==NULL )
	{
		return FALSE;
	}

	if( invalid_characters( (*player) ) || invalid_characters( (*player2) ) )
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

			/* on apppelle juste avant la fonction pour donne les
			 * ressources sur la mort du character
			 */
			if ( get_ressources( player,player2,(*player)->characters->tab[i] ) == FALSE)
			{
				printf("Erreur au retour de la fonction GET_RESSOURCES \n");
			}

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

	int nb_avant2 = (*player2)->characters->nb;

	/* on fais la meme chose pour le deuxieme player */

	for( int i=0; i<(*player2)->characters->nb; i++ )
	{
		if ( (*player2)->characters->tab[i]->pv <= 0 )
		{
			/*
			 * si un character est mort, on le free et on decremente le nb de character contenu
			 * dans le tableau
 			 */

			/* on apppelle juste avant la fonction pour donne les
			 * ressources sur la mort du character
			 */
			if ( get_ressources( player,player2,(*player2)->characters->tab[i] ) == FALSE )
			{
				printf("Erreur au retour de la fonction GET_RESSOURCES \n");
			}

			free((*player2)->characters->tab[i]);
			(*player2)->characters->tab[i] = NULL;

			/* 
			 * il faut penser a tasser le tableau pour pas perdre d'information car on s'arrete
			 * sur le premier qui valide la condition
			 */

			if( tasser_tab(player2,i) )
			{
				printf("\nLe tableau a bien ete tasse !\n");
			}	

			(*player2)->characters->nb-=1;
		}
	}

	return ( nb_avant == (*player)->characters->nb || nb_avant2 == (*player2)->characters->nb ) ? FALSE : TRUE;
}





















































