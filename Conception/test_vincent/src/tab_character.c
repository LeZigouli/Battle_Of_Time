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
        	printf("[%d] :: %s, owner : %d, pv: %4d\n",i,characters->tab[i]->name,characters->tab[i]->owner,characters->tab[i]->pv);
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