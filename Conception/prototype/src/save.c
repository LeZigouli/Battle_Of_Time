/**
 * \file save.c
 * \brief Contient les fonction pour sauvarder / charger une partie depuis un fichier
 * \author Proudy Vincent
 * \date 10 avril 2024
 * 
*/


#include "../lib/save.h"

/*
 * Sauvegarder le joueur et l'ordinateur dans un fichier
 *
 * Parametre : 1 joueur et 1 ordinateur
 * retour    : 1 si OK sinon 0
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
    fprintf(fd,"%d %s %d %d %ld %ld\n",     player->owner,
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
        fprintf(fd,"%d %s\n",   player->characters->tab[i]->age *NB_CHARACTER + player->characters->tab[i]->classe,
                                player->characters->tab[i]->name);
    }

    /* puis le tableau de characters dans la file d'attente */
    fprintf(fd,"%d\n",player->file_attente->nb);

    /* on ecrit les characters contenus dans la file d'attente */
    for( int i=0; i<player->file_attente->nb; i++ )
    {
        fprintf(fd,"%d %s\n",   player->file_attente->tab[i]->age *NB_CHARACTER + player->file_attente->tab[i]->classe,
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
        fprintf(fd,"%d %s\n",   ordi->characters->tab[i]->age *NB_CHARACTER + ordi->characters->tab[i]->classe,
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
 * retour             : 1 si OK sinon 0
*/
booleen_t load(ordi_t ** ordi, player_t ** player){

    FILE * fd;

    /* on ouvre le fichier */
    if ( (fd = fopen(FICHIER,"r")) == NULL )
    {
        fprintf(stderr,"Erreur chargement (fichier %s ne peut pas etre lu)\n",FICHIER);
        return FALSE;
    }

    /********************************************/
    /* on alloue la mémoire pour ordi et player */
    /********************************************/

        /**********/
        /* joueur */
        /**********/
    if ( ((*player) = malloc(sizeof(player_t))) == NULL)
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE;
    }

    /* les deux tableaux de characters */
    if ( ((*player)->characters = malloc(sizeof(tab_charactere_t))) == NULL)
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE; 
    }

    if ( ((*player)->file_attente = malloc(sizeof(tab_charactere_t))) == NULL)
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE; 
    }

    /* on mets les pointeurs a nul pour eviter les pointeurs fous */
    for(int i=0;i<MAX_POSSESSED;i++){
        (*player)->characters->tab[i]=NULL;
        (*player)->file_attente->tab[i]=NULL;
	}
    /* on mets le nombre a 0 */
	(*player)->characters->nb=0;
	(*player)->file_attente->nb=0;

    /* on creer creer le pointeurs sur le building */
    if  (((*player)->building = malloc(sizeof(building_t))) == NULL)
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE; 
    }

        /********/
        /* ordi */
        /********/

    if (((*ordi) = malloc(sizeof(ordi_t))) == NULL )
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE; 
    }

    if (((*ordi)->characters = malloc(sizeof(tab_charactere_t))) == NULL )
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE;  
    }

    /******************************/
    /* On va lire dans le fichier */
    /*******************************/

        /******************/
        /* Pour le player */
        /******************/

    /* on lit la structure player */
    fscanf(fd, "%d %s %d %d %ld %ld\n",     &((*player)->owner),
                                            (char *)(*player)->name,  
                                            &((*player)->xp),
                                            &((*player)->delai),
                                            &((*player)->debut),
                                            &((*player)->fin));

    /* on lit la structure building */
    fscanf(fd,"%d %d %d %d %d\n",   &(*player)->building->dammage,
                                    &(*player)->building->level,
                                    &(*player)->building->max_pv,
                                    &(*player)->building->XP_cost,
                                    &(*player)->building->pv);

    /* on lit le nombre de de de personnage dans le tableau 
     * characters qui va nous permettre de boucler dessus
     * pour lire
     */
    fscanf(fd,"%d\n",&(*player)->characters->nb);

    for (int i = 0; i < (*player)->characters->nb; i++) {

        (*player)->characters->tab[i] = malloc(sizeof(character_t)); // Allocation mémoire

        fscanf(fd, "%d %s\n",   &((*player)->characters->tab[i]->classe),
                                (char *)(*player)->characters->tab[i]->name);
    }

    fscanf(fd,"%d\n",&(*player)->file_attente->nb);
    
    for (int i = 0; i < (*player)->file_attente->nb; i++) {

        (*player)->file_attente->tab[i] = malloc(sizeof(character_t)); // Allocation mémoire

        fscanf(fd, "%d %s\n",   &((*player)->file_attente->tab[i]->classe),
                                (char *)(*player)->file_attente->tab[i]->name);
    }

        /***************/
        /* pour l'ordi */
        /***************/

    /* recuperation ordi */
    fscanf(fd, "%d %d %d %d %d\n",  &((*ordi)->owner),
                                    &((*ordi)->difficulte),
                                    &((*ordi)->delai),
                                    &((*ordi)->xp),
                                    &((*ordi)->delai_ulti));

    /* recuperation building de l'ordi */
    fscanf(fd,"%d %d %d %d %d\n",   &(*ordi)->building->dammage,
                                    &(*ordi)->building->level,
                                    &(*ordi)->building->max_pv,
                                    &(*ordi)->building->XP_cost,
                                    &(*ordi)->building->pv);

    /* on recupere les infos pour le tableau de character */
    fscanf(fd,"%d\n", &(*ordi)->characters->nb);

    for (int i = 0; i < (*ordi)->characters->nb; i++) {

        (*ordi)->characters->tab[i] = malloc(sizeof(character_t)); // Allocation mémoire

        fscanf(fd, "%d %s\n",   &((*ordi)->characters->tab[i]->classe),
                                (char *)(*ordi)->characters->tab[i]->name);
    }

    printf("\nChargement reussi...\n");
    return TRUE;
} 