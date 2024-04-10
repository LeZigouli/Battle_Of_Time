#include "../lib/save.h"

/*
 * Sauvegarder le joueur et l'ordinateur dans un fichier
 *
 * Parametre : 1 joueur et 1 ordinateur
 * retour    : 1 si bien passé sinon 0
 */
booleen_t save(ordi_t * ordi, player_t * player){
    FILE * fd;

    /* on ouvre le fichier */
    if ( (fd = fopen(FICHIER,"w")) == NULL)
    {
        fprintf(stderr,"Erreur Sauvegarde (chargement/creation fichier : %s)\n",FICHIER);
        return FALSE;
    }

    /* verification des structures en parametres */
    if ( ordi == NULL || player == NULL )
    {
        fprintf(stderr,"Erreur Sauvegarde (Parametre inexistant)\n");
        return FALSE;
    }

    /***************************/
    /* on sauvegarde le player */
    /***************************/

    /* on ecrit les informations contenus dans le player */
    fprintf(fd,"%d %s %d %d %lg %lg %d\n",  player->owner,
                                            player->name,  
                                            player->xp,
                                            player->delai,
                                            player->debut,
                                            player->fin);

    /* ecriture des infos du building du player */
    fprintf(fd,"%d %d %d %d %d\n",  player->building->dammage,
                                    player->building->level,
                                    player->building->max_pv,
                                    player->building->XP_cost,
                                    player->building->pv);

    /* on ecrit le tableau de characters */

    /* on ecrit d'abord le nombre de charactere contenus dans notre notre
     * tableau, ce qui va nous permettre apres de boucler dessus dans le 
     * chargement et la sauvegardes
     */
    fprintf(fd,"%d\n",player->characters->nb);

    /* on ecrit les characters */
    for( int i=0; i<player->characters->nb; i++ )
    {
        fprintf(fd,"%d %s\n",   player->characters->tab[i]->indice,
                                player->characters->tab[i]->name);
    }

    /* puis le tableau de characters dans la file d'attente */
    fprintf(fd,"%d\n",player->file_attente->nb);

    /* on ecrit les characters contenus dans la file d'attente */
    for( int i=0; i<player->file_attente->nb; i++ )
    {
        fprintf(fd,"%d %s\n",   player->file_attente->tab[i]->indice,
                                player->file_attente->tab[i]->name);
    }

    /************************/
    /* on sauvegarde l'ordi */
    /************************/

    /* ecriture la structure ordi */
    fprintf(fd,"%d %d %d %d %d\n",  ordi->owner,
                                    ordi->difficulte,
                                    ordi->delai,
                                    ordi->xp,
                                    ordi->delai_ulti);

    /* ensuite on fait comme le joueur pour les deux tableaux */
    fprintf(fd,"%d %d %d %d %d\n",  ordi->building->dammage,
                                    ordi->building->level,
                                    ordi->building->max_pv,
                                    ordi->building->XP_cost,
                                    ordi->building->pv);

    /* on ecrit le tableau de characters */

    /* on ecrit d'abord le nombre de charactere contenus dans notre notre
     * tableau, ce qui va nous permettre apres de boucler dessus dans le 
     * chargement et la sauvegardes
     */
    fprintf(fd,"%d\n",ordi->characters->nb);

    /* on ecrit les characters */
    for( int i=0; i<ordi->characters->nb; i++ )
    {
        fprintf(fd,"%d %s\n",   ordi->characters->tab[i]->indice,
                                ordi->characters->tab[i]->name);
    }

    printf("\nSauvegarde terminée...\n");
    /* on oublie pas de fermé le fichier */
    fclose(fd);
    return TRUE;

}

/*
 * Charger le joueur et l'ordinateur depuis un fichier
 *
 * Parametre resultat : 1 joueur et 1 ordinateur
 * retour             : 1 si bien passé sinon 0
 */
booleen_t load(ordi_t ** ordi, player_t ** player){

    FILE * fd;

    /* on ouvre le fichier */
    if ( (fd = fopen(FICHIER,"r")) == NULL )
    {
        
    }

}