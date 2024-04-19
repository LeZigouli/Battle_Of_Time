/**
 * \file tab_character.c
 * \brief Contient les fonctions pour la gestion du tableau de personnage
 * \author Proudy Vincent et Louison Roquain
 * \date 09 avril 2024
 * \version 1.0
 * 
*/

#include "../lib/tab_character.h"

/**
 * @brief Supprime les personnages ayant des points de vie nuls ou négatifs.
 * 
 * @param characters Pointeur vers le tableau de personnages.
 * @return Retourne TRUE si les personnages ont été supprimés avec succès, sinon FALSE.
 */
booleen_t delete_character(tab_charactere_t ** characters){
	
    /* verification préliminaire */
	if( characters == NULL || (*characters) == NULL)
	{
		return FALSE;
	}

	/*
	 * on va chercher dans characters tout character avec des PV <=0
	 * si on en trouve, on le(s) supprime(s)
	 * sinon, on retourne faux
	 */
	int mort=0;

	for( int i=0; i<(*characters)->nb; i++ )
	{
		if ( (*characters)->tab[i]->pv <= 0 )
		{
			/*
			 * si un character est mort, on le free et on decremente le nb de character contenu
			 * dans le tableau
 			 */

			free((*characters)->tab[i]);
			(*characters)->tab[i] = NULL;
			mort++;
		}
		
	}
	
	if( tasser_tab(characters,mort) )
	{
		//printf("\nLe tableau a bien ete tasse !\n");
	}
	(*characters)->nb-=mort;

    return TRUE;
}

/**
 * @brief Tasse le tableau de personnages après suppression.
 * 
 * @param characters Pointeur vers le tableau de personnages.
 * @param nb_mort Nombre de personnages morts à supprimer.
 * @return Retourne TRUE si le tassement est réussi, sinon FALSE.
 */
booleen_t tasser_tab( tab_charactere_t **  characters, int nb_mort)
{
	if( characters==NULL || *characters == NULL )
	{
		return FALSE;
	}
    
	int i;
	/* on tasse le tableau a partir de l'indice de depart */
	for ( i=0; i<(*characters)->nb-nb_mort; i++ )
	{
		(*characters)->tab[i] = (*characters)->tab[i+nb_mort];
	}
	for(i=(*characters)->nb-nb_mort;i<MAX_POSSESSED;i++)
		(*characters)->tab[i] =NULL;

	return TRUE;
}

/**
 * @brief Affiche les personnages possédés.
 * 
 * @param characters Pointeur vers le tableau de personnages.
 * @return Retourne TRUE si l'affichage est réussi, sinon FALSE.
 */
booleen_t afficher_characters(tab_charactere_t * characters)
{

    if ( characters == NULL )
    {
        return FALSE;
    }

    printf("<----- characters possedees ----->\n");
    for ( int i=0; i<characters->nb; i++)
    {
		if(characters->tab[i] != NULL)
        	printf("[%d] :: %s, owner : %d, pv: %4d x: %5d\n",i,characters->tab[i]->name,characters->tab[i]->owner,characters->tab[i]->pv,characters->tab[i]->x);
    }
    printf("<-------------------------------->\n\n");

    return TRUE;
}

/**
 * @brief Réalise l'ultime attaque, mettant les personnages cibles à 0 points de vie.
 * 
 * @param cible Pointeur vers le tableau de personnages cibles.
 * @return Retourne TRUE si l'attaque est réussie, sinon FALSE.
 */
booleen_t ulti(tab_charactere_t ** cible){
	if(cible==NULL || *cible == NULL)
		return FALSE;
	int i;
	for(i=0;i < (*cible)->nb;i++){
		(*cible)->tab[i]->pv=0;
	}
	return TRUE;
}

/**
 * @brief Vérifie s'il y a un espace vide devant le personnage.
 * 
 * @param deriere Personnage précédent.
 * @param devant_x Position X du personnage devant.
 * @param owner Propriétaire du personnage.
 * @return Retourne TRUE s'il y a un espace vide devant, sinon FALSE.
 */
booleen_t vide_devant(character_t * deriere,int devant_x,int owner){
	int dist;
	switch (owner)
	{
	case OWNER_1:
		dist= devant_x - (deriere->vector + deriere->x) - TAILLE_SPRITE;
		if(dist >= deriere->vector)
			return TRUE;
		else
			return FALSE;
		break;
	
	default:
		dist= (deriere->x - deriere->vector) - devant_x - TAILLE_SPRITE;
		if(dist >= deriere->vector)
			return TRUE;
		else
			return FALSE;
		break;
	}
	
	
}

/**
 * @brief Réalise le mouvement d'un personnage.
 * 
 * @param deriere Pointeur vers le personnage à déplacer.
 * @param devant_x Position X du personnage devant.
 */
void mouvement(character_t ** deriere,int devant_x){
	(*deriere)->x_pred=(*deriere)->x;
	if(vide_devant(*deriere,devant_x,(*deriere)->owner))
		if((*deriere)->owner>1)
			deplacement_gauche(deriere);
		else
			deplacement_droit(deriere);
	else{
		if((*deriere)->owner>1)
			(*deriere)->x -= ((*deriere)->x) - devant_x - TAILLE_SPRITE;
		else
			(*deriere)->x += devant_x -  (*deriere)->x - TAILLE_SPRITE;
		if((*deriere)->x < POS_DEP)
			(*deriere)->x= POS_DEP;
		else
			if((*deriere)->x> POS_DEP_AD)
				(*deriere)->x= POS_DEP_AD;
	}
}

/**
 * @brief Effectue le déplacement des personnages.
 * 
 * @param characters Pointeur vers le tableau de personnages.
 * @param first_Adverser Premier adversaire.
 * @param x_building_adverser Position X du bâtiment adversaire.
 */
void deplacement(tab_charactere_t * characters, character_t * first_Adverser, int x_building_adverser){
    int i;
	if(characters !=NULL)
		if(characters->nb>0){
			if(characters->ind_first_vivant!=-1){
				if(first_Adverser==NULL)
					mouvement(&characters->tab[characters->ind_first_vivant],x_building_adverser);
				else
					mouvement(&characters->tab[characters->ind_first_vivant],first_Adverser->x);
					
				for(i=characters->ind_first_vivant+1;i<characters->nb;i++){
					mouvement(&characters->tab[i],characters->tab[i-1]->x);
				}
			}
		}
}

void maj_first_vivant(tab_charactere_t * player, tab_charactere_t * ordi){
	int i;
	player->ind_first_vivant=0;
	ordi->ind_first_vivant=0;
	for(i=0;i<player->nb;i++){
		if(player->tab[i]->pv < 0)
			player->ind_first_vivant++;
	}
	if(player->nb <= player->ind_first_vivant || player->ind_first_vivant >= MAX_POSSESSED)
			player->ind_first_vivant=-1;
	
	for(i=0;i<ordi->nb;i++){
		if(ordi->tab[i]->pv < 0)
			ordi->ind_first_vivant++;

	}
	if(ordi->nb <= ordi->ind_first_vivant || ordi->ind_first_vivant >= MAX_POSSESSED)
			ordi->ind_first_vivant=-1;
}