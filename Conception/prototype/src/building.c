#include "../lib/common.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/


/* fonction pour creer le batiment d'un joueur */
booleen_t init_building(player_t ** player)
{
	/* verification préliminaire */
	if ( (*player) == NULL || player == NULL )
	{
		return FALSE;
	}

	/* allocation dynamique */
	(*player)->building = malloc(sizeof(building_t));

	if ( (*player)->building == NULL )
	{
		printf("ERREUR : allocation building !\n");
		return FALSE;
	}

	/* affectation */
	(*player)->building->dammage = 33;
	(*player)->building->XP_cost = 5000;
	(*player)->building->level = 1;
	(*player)->building->pv = 300;
	(*player)->building->max_pv = (*player)->building->pv;
	(*player)->building->owner = (*player)->owner;

	return TRUE;
}

booleen_t upgrade_building(player_t ** player)
{
	if ( player == NULL || (*player) == NULL )
	{
		return FALSE;
	}
	if ( (*player)->building == NULL )
	{
		/* si le building n'a pas encore été creer */
		return FALSE;
	}

    if ( (*player)->xp - (*player)->building->XP_cost < 0 )
    {
        printf("ERREUR : pas assez d'XP pour améliorer le batiment !\n");
        return FALSE;
    }

    if ( (*player)->building->level >= MAX_LEVEL_UP )
    {
        printf("ERREUR : Impossible de plus améliorer le batiment, limite atteinte !\n");
        return FALSE;
    }

	/* traitement */

    /* on soustrait le cout en xp du joueur */
    (*player)->xp -= (*player)->building->XP_cost;

	/* a chaque upgrade on augmente les states par le coef_level_up */
    (*player)->building->dammage *= COEF_LEVEL_UP_DAMMAGE;
    (*player)->building->max_pv *= COEF_LEVEL_UP_MAX_PV;
    (*player)->building->pv += (*player)->building->max_pv*((COEF_LEVEL_UP_MAX_PV-1)/COEF_LEVEL_UP_MAX_PV);
    (*player)->building->XP_cost *= COEF_LEVEL_UP_MAX_GOLD_COST;

    /* actualise le niveau du building */
    (*player)->building->level +=1;

	return TRUE;
}