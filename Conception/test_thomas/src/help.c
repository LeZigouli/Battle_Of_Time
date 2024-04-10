#include "../lib/help.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/






void afficher_character(character_t character)
{
    printf("Name : %s \n",character.name);
    printf("Dammage : %d\n",character.dammage);
    printf("PV : %d\n",character.pv);
    printf("Time : %d\n",character.time);
}

booleen_t afficher_all_character(character_t * tab)
{
    if ( tab == NULL )
    {
        return FALSE;
    }

    for( int i=0; i<NB_AGE; i++)
    {
        for( int j = 0;j<NB_CHARACTER;j++)
        {
            printf("----------------[%d][%d]----------------\n",i,j);
            afficher_character(tab[i*NB_CHARACTER+j]);
            printf("\n\n");
        }
    }

    return TRUE;

}





