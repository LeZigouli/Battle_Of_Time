#include "../lib/common.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/


booleen_t afficher_characters_player(tab_charactere_t * characters)
{

    if ( characters == NULL )
    {
        return FALSE;
    }

    printf("<----- characters possedees ----->\n");
    for ( int i=0; i<characters->nb; i++)
    {
        printf("[%d] :: %s\n",i,characters->tab[i]->name);
    }
    printf("<-------------------------------->\n\n");

    return TRUE;
}

booleen_t afficher_player(player_t * player)
{
    if ( player == NULL )
    {
        return FALSE;
    }
    printf("<----- Player ----->\n");
	printf("Nom : %s\nPV : %d\nXP : %d\nGOLD : %f\nOwner : %d\n\n",player->name,player->building->pv,player->xp,player->gold,player->owner);

    return TRUE;

}

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

booleen_t afficher_building(player_t * player)
{
    if ( player == NULL )
    {
        return FALSE;
    }

    printf("<----- building ----->\n");
    printf("Owner : %d \nDammage : %d\nPV : %d\nGOLD_cost : %d\nLevel : %d\n",player->building->owner, player->building->dammage,player->building->pv, player->building->GOLD_cost, player->building->level);
    printf("<-------------------->\n\n");

    return TRUE;
}















