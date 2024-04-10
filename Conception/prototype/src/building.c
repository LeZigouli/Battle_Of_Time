#include "../lib/building.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/

/* fonction pour creer le batiment d'un joueur */
booleen_t init_building(building_t ** building, int owner)
{
	/* verification préliminaire */
	if ( building == NULL)
	{
		return FALSE;
	}

	/* allocation dynamique */
	*building = malloc(sizeof(building_t));

	if ( *building == NULL )
	{
		printf("ERREUR : allocation building !\n");
		return FALSE;
	}

	/* affectation */
	(*building)->dammage = 33;
	(*building)->XP_cost = 1000;
	(*building)->level = Prehistoire;
	(*building)->pv = 300;
	(*building)->max_pv = (*building)->pv;
	(*building)->owner = owner;

	return TRUE;
}

booleen_t upgrade_building(building_t ** building,int * xp)
{
	booleen_t joueur=FALSE;
	if ( building == NULL || (*building) == NULL )
	{
		return FALSE;
	}
	if((*building)->owner != ORDINATEUR)
		joueur=TRUE;
	if(joueur){
		if (*xp - (*building)->XP_cost < 0 )
		{
			printf("ERREUR : pas assez d'XP pour améliorer le batiment !\n");
			return FALSE;
		}
		
	}
	if ( (*building)->level < MAX_LEVEL_UP )
	{
		/* traitement */
		if(joueur)
			/* on soustrait le cout en xp du joueur */
			*xp -= (*building)->XP_cost;
		else
			*xp=0;
		/* a chaque upgrade on augmente les states par le coef_level_up */
		(*building)->dammage *= COEF_LEVEL_UP_DAMMAGE;
		(*building)->max_pv *= COEF_LEVEL_UP_MAX_PV;
		(*building)->pv += (*building)->max_pv*((COEF_LEVEL_UP_MAX_PV-1)/COEF_LEVEL_UP_MAX_PV);
		(*building)->XP_cost *= COEF_LEVEL_UP_MAX_GOLD_COST;

		/* actualise le niveau du building */
		(*building)->level++;
		return TRUE;
	}
	if(joueur)
		printf("ERREUR : Impossible de plus améliorer le batiment, limite atteinte !\n");
	return FALSE;
}

booleen_t afficher_building(building_t * building)
{
    if ( building == NULL )
    {
        return FALSE;
    }

    printf("<----- building ----->\n");
    printf("Owner : %d \nDammage : %d\nPV : %d\nXP_cost : %d\nLevel : %d\n",building->owner,building->dammage,building->pv,building->XP_cost,building->level);
    printf("<-------------------->\n\n");

    return TRUE;
}