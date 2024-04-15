#include "../lib/tab_character.h"

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

booleen_t ulti(tab_charactere_t ** cible){
	if(cible==NULL || *cible == NULL)
		return FALSE;
	int i;
	for(i=0;i < (*cible)->nb;i++){
		(*cible)->tab[i]->pv=0;
	}
	return TRUE;
}

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
/* mouvement */
void mouvement(character_t ** deriere,int devant_x){
	if(vide_devant(*deriere,devant_x,(*deriere)->owner))
		if((*deriere)->owner>1)
			deplacement_gauche(deriere);
		else
			deplacement_droit(deriere);
	else
		if((*deriere)->owner>1){
			(*deriere)->x -= ((*deriere)->x) - devant_x - TAILLE_SPRITE;
			if((*deriere)->x < 0)
				(*deriere)->x=0;
			else
				if((*deriere)->x>1500)
					(*deriere)->x=1500;
		}else{
			(*deriere)->x += devant_x -  (*deriere)->x - TAILLE_SPRITE;
			if((*deriere)->x < 0)
				(*deriere)->x=0;
			else
				if((*deriere)->x>1500)
					(*deriere)->x=1500;
		}
}

void deplacement(tab_charactere_t * characters, character_t * first_Adverser, int x_building_adverser){
    int i;
	if(characters !=NULL)
		if(characters->nb>0){
			if(first_Adverser==NULL)
				mouvement(&characters->tab[0],x_building_adverser);
			else
				mouvement(&characters->tab[0],first_Adverser->x);
				
			for(i=1;i<characters->nb;i++){
				mouvement(&characters->tab[i],characters->tab[i-1]->x);
			}
		}
}