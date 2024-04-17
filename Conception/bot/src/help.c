/**
 * \file help.c
 * \brief Contient les fonction permettant l'aide au developpement.
 * \author Proudy Vincent
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/
#include "../lib/help.h"

/**
 * @brief Affiche les caractéristiques d'un personnage.
 * 
 * @param character Le personnage à afficher.
 */
void afficher_character_tab_tab(character_t character)
{
    printf("age : %d\n",character.age);
    printf("classe : %d\n",character.classe);
    printf("cost : %d\n",character.cost);
    printf("dammag : %d\n",character.dammage);
    printf("max_pv : %d\n",character.max_pv);
    printf("owner : %d\n",character.owner);
    printf("pv : %d\n",character.pv);
    printf(" : %s\n",character.sprite);
    printf("ratio ressource : %lf\n",character.ratio_ressources);
    printf("time : %d\n",character.time);
    printf("vecteur : %d\n",character.vector);
    printf("x : %d\n",character.x);
    printf("y : %d\n",character.y);

}

/**
 * @brief Affiche toutes les caractéristiques des personnages dans un tableau.
 * 
 * @param tab Le tableau de personnages à afficher.
 * @return TRUE si le tableau n'est pas NULL, FALSE sinon.
 */
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
            afficher_character_tab_tab(tab[i*NB_CHARACTER+j]);
            printf("\n\n");
        }
    }

    return TRUE;

}





