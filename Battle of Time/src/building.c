/**
 * \file building.c
 * \brief Contient les fonction pour la gestion des batiments
 * \author Proudy Vincent
 * \date 02 avril 2024
 * \version 1.0
 * 
*/
#include "../lib/building.h"

/**
 * \brief Initialise le bâtiment d'un joueur avec des valeurs par défaut.
 * 
 * \param building Pointeur vers le bâtiment à initialiser.
 * \param owner Propriétaire du bâtiment.
 * \return TRUE si l'initialisation s'est déroulée avec succès, FALSE sinon.
 */
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
	(*building)->dammage = 10;
	(*building)->XP_cost = 10000;
	(*building)->level = Prehistoire;
	(*building)->pv = 250;
	(*building)->max_pv = (*building)->pv;
	(*building)->owner = owner;

	return TRUE;
}

/**
 * \brief Améliore le bâtiment d'un joueur en fonction de l'expérience accumulée.
 * 
 * \param building Pointeur vers le bâtiment à améliorer.
 * \param xp Pointeur vers l'expérience accumulée par le joueur.
 * \return TRUE si l'amélioration s'est déroulée avec succès, FALSE sinon.
 */
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

/**
 * \brief Affiche les caractéristiques du bâtiment.
 * 
 * \param building Le bâtiment à afficher.
 * \return TRUE si l'affichage s'est déroulé avec succès, FALSE sinon.
 */
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

/**
 * \brief Détermine le maximum entre deux entiers.
 * 
 * \param a Premier entier.
 * \param b Second entier.
 * \return La valeur maximale entre a et b.
 */
int max(int a, int b){
	if(a>=b)
		return a;
	else
		return b;
}

/**
 * \brief Détermine le minimum entre deux entiers.
 * 
 * \param a Premier entier.
 * \param b Second entier.
 * \return La valeur minimale entre a et b.
 */
int min(int a, int b){
	if(a<=b)
		return a;
	else
		return b;
}