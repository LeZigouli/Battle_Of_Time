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

    FILE * fd_player, * fd_ordi;

    /* on ouvre le fichier */
    if ( (fd_player = fopen(FICHIER_1,"w")) == NULL)
    {
        fprintf(stderr,"Erreur Sauvegarde (creation fichier : %s)\n",FICHIER_1);
        return FALSE;
    }

    /* verification des structures en parametres */
    if ( ordi == NULL || player == NULL )
    {
        fprintf(stderr,"Erreur Sauvegarde (Parametre inexistant)\n");
        return FALSE;
    }

    if ( (fd_ordi = fopen(FICHIER_2,"w")) == NULL )
    {
        fprintf(stderr,"Erreur Sauvegarde (creation fichier : %s)\n",FICHIER_2);
        return FALSE;
    }

    /***************************/
    /* on sauvegarde le player */
    /***************************/

    /* on ecrit les informations contenus dans le player */
    fprintf(fd_player,"%f %d %s %d %d %ld %ld\n",   player->gold,     
                                                    player->owner,
                                                    player->name,  
                                                    player->xp,
                                                    player->delai,
                                                    player->debut,
                                                    player->fin);

    /* ecriture des infos du building du player */
    fprintf(fd_player,"%d %d %d %d %d\n",  player->building->dammage,
                                    player->building->level,
                                    player->building->max_pv,
                                    player->building->XP_cost,
                                    player->building->pv);

    /* on ecrit le tableau de characters */

    /* on ecrit d'abord le nombre de charactere contenus dans notre notre
     * tableau, ce qui va nous permettre apres de boucler dessus dans le 
     * chargement et la sauvegardes
     */
    fprintf(fd_player,"%d\n",player->characters->nb);

    /* on ecrit les characters */
    for( int i=0; i<player->characters->nb; i++ )
    {
        if ( i == 0 )
        {
            /* pour le premier on sauvegarde ses pv */
            fprintf(fd_player,"%d ",   player->characters->tab[i]->pv);
        }
        fprintf(fd_player,"%d %d %d %d\n",  player->characters->tab[i]->age *NB_CHARACTER + player->characters->tab[i]->classe,
                                            player->characters->tab[i]->age *NB_CHARACTER + player->characters->tab[i]->x,
                                            player->characters->tab[i]->age *NB_CHARACTER + player->characters->tab[i]->y,
                                            player->characters->tab[i]->age *NB_CHARACTER + player->characters->tab[i]->x_pred
                                            );
    }

    /* puis le tableau de characters dans la file d'attente */
    fprintf(fd_player,"%d\n",player->file_attente->nb);

    /* on ecrit les characters contenus dans la file d'attente */
    for( int i=0; i<player->file_attente->nb; i++ )
    {
        fprintf(fd_player,"%d\n",    (player->file_attente->tab[i]->age *NB_CHARACTER + player->file_attente->tab[i]->classe));
    }

    fclose(fd_player);

    /************************/
    /* on sauvegarde l'ordi */
    /************************/

    /* ecriture la structure ordi */
    fprintf(fd_ordi,"%d %d %d %d %d\n", ordi->owner,
                                        ordi->difficulte,
                                        ordi->delai,
                                        ordi->xp,
                                        ordi->delai_ulti);

    /* ensuite on fait comme le joueur pour les deux tableaux */
    fprintf(fd_ordi,"%d %d %d %d %d\n", ordi->building->dammage,
                                        ordi->building->level,
                                        ordi->building->max_pv,
                                        ordi->building->XP_cost,
                                        ordi->building->pv);

    /* on ecrit le tableau de characters */

    /* on ecrit d'abord le nombre de charactere contenus dans notre notre
     * tableau, ce qui va nous permettre apres de boucler dessus dans le 
     * chargement et la sauvegardes
     */
    fprintf(fd_ordi,"%d\n",ordi->characters->nb);

    /* on ecrit les characters */
    for( int i=0; i<ordi->characters->nb; i++ )
    {
        if ( i == 0 )
        {
            /* pour le premier on sauvegarde ses pv */
            fprintf(fd_ordi,"%d ",ordi->characters->tab[i]->pv);
        }

        fprintf(fd_ordi,"%d %d %d %d\n",ordi->characters->tab[i]->age *NB_CHARACTER + ordi->characters->tab[i]->classe,
                                        ordi->characters->tab[i]->age *NB_CHARACTER + ordi->characters->tab[i]->x,
                                        ordi->characters->tab[i]->age *NB_CHARACTER + ordi->characters->tab[i]->y,
                                        ordi->characters->tab[i]->age *NB_CHARACTER + ordi->characters->tab[i]->x_pred
                                        );
    }

    printf("\nSauvegarde terminée...\n");
    /* on oublie pas de fermé le fichier */
    fclose(fd_ordi);
    return TRUE;
}

/*
 * Charger le joueur et l'ordinateur depuis un fichier
 *
 * Parametre resultat : 1 joueur et 1 ordinateur
 * retour             : 1 si OK sinon 0
*/
booleen_t load(ordi_t ** ordi, player_t ** player, character_t * tab){

    FILE * fd_player, * fd_ordi;

    /* on ouvre le fichier */
    if ( (fd_player = fopen(FICHIER_1,"r")) == NULL )
    {
        fprintf(stderr,"Erreur chargement (fichier %s ne peut pas etre lu)\n",FICHIER_1);
        return FALSE;
    }

    if ( (fd_ordi = fopen(FICHIER_2,"r")) == NULL )
    {
        fprintf(stderr,"Erreur chargement (fichier %s ne peut pas etre lu)\n",FICHIER_2);
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

    if (((*ordi)->building = malloc(sizeof(building_t))) == NULL )
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE; 
    }

    if (((*ordi)->characters = malloc(sizeof(tab_charactere_t))) == NULL )
    {
        fprintf(stderr,"Erreur chargement (allocation dynamique)\n");
        return FALSE;  
    }
    printf("Malloc terminé !\n");
    /******************************/
    /* On va lire dans le fichier */
    /*******************************/

        /******************/
        /* Pour le player */
        /******************/

    /* on lit la structure player */
    fscanf(fd_player, "%f %d %s %d %d %ld %ld\n",   &(*player)->gold,
                                                    &((*player)->owner),
                                                    (char *)(*player)->name,  
                                                    &((*player)->xp),
                                                    &((*player)->delai),
                                                    &((*player)->debut),
                                                    &((*player)->fin));

    /* on lit la structure building */
    fscanf(fd_player,"%d %d %d %d %d\n",    &(*player)->building->dammage,
                                            &(*player)->building->level,
                                            &(*player)->building->max_pv,
                                            &(*player)->building->XP_cost,
                                            &(*player)->building->pv);
    printf("OK pour les stats\n");
    /* on lit le nombre de de de personnage dans le tableau 
     * characters qui va nous permettre de boucler dessus
     * pour lire
     */

    afficher_player(*player);

    fscanf(fd_player,"%d\n",&(*player)->characters->nb);
    int pv, x, y, x_pred;
    printf("NB character = %d",(*player)->characters->nb);
    for (int i = 0; i < (*player)->characters->nb; i++) {
        (*player)->characters->tab[i] = malloc(sizeof(character_t)); // Allocation mémoire
        
        if ( i == 0 )
        {
            /* pour le premier on prend ses pv */
            fscanf(fd_player,"%d",      &pv);
        }

        fscanf(fd_player, "%d %d %d %d\n",    &((*player)->characters->tab[i]->classe), &x, &y, &x_pred);
        copie_character(&(*player)->characters->tab[i], &tab[(*player)->characters->tab[i]->classe]);
        (*player)->characters->tab[i]->owner=OWNER_1;
        (*player)->characters->tab[i]->pv = pv;
        (*player)->characters->tab[i]->x = x;
        (*player)->characters->tab[i]->y = y;
        (*player)->characters->tab[i]->x_pred = x_pred;
    }
    printf("OK pour le tab characters\n");
    fscanf(fd_player,"%d\n",&(*player)->file_attente->nb);

    for (int i = 0; i < (*player)->file_attente->nb; i++) {

        (*player)->file_attente->tab[i] = malloc(sizeof(character_t)); // Allocation mémoire

        fscanf(fd_player, "%d\n",    &((*player)->file_attente->tab[i]->classe));

        copie_character(&(*player)->file_attente->tab[i], &tab[(*player)->file_attente->tab[i]->classe]);
        (*player)->file_attente->tab[i]->owner=OWNER_1;
        
    }
    printf("OK pour les file d'attente\n");
    fclose(fd_player);
    printf("Joueur terminé !\n");
        /***************/
        /* pour l'ordi */
        /***************/

    /* recuperation ordi */
    fscanf(fd_ordi, "%d %d %d %d %d\n", &((*ordi)->owner),
                                        &((*ordi)->difficulte),
                                        &((*ordi)->delai),
                                        &((*ordi)->xp),
                                        &((*ordi)->delai_ulti));

    /* recuperation building de l'ordi */
    fscanf(fd_ordi,"%d %d %d %d %d\n",  &(*ordi)->building->dammage,
                                        &(*ordi)->building->level,
                                        &(*ordi)->building->max_pv,
                                        &(*ordi)->building->XP_cost,
                                        &(*ordi)->building->pv);

    /* on recupere les infos pour le tableau de character */
    fscanf(fd_ordi,"%d\n", &(*ordi)->characters->nb);
    
    for (int i = 0; i < (*ordi)->characters->nb; i++) {

        (*ordi)->characters->tab[i] = malloc(sizeof(character_t)); // Allocation mémoire

        if ( i == 0 )
        {
            /* pour le premier on prend ses pv */
            fscanf(fd_ordi,"%d",&pv);
        }
        
        fscanf(fd_ordi, "%d %d %d %d\n",    &((*ordi)->characters->tab[i]->classe),
                                            &x,
                                            &y,
                                            &x_pred);
        copie_character(&(*ordi)->characters->tab[i], &tab[(*ordi)->characters->tab[i]->classe]);
        (*ordi)->characters->tab[i]->owner=ORDINATEUR;
        (*ordi)->characters->tab[i]->pv = pv;
        (*ordi)->characters->tab[i]->x = x;
        (*ordi)->characters->tab[i]->y = y;
        (*ordi)->characters->tab[i]->x_pred = x_pred;
    }

    (*player)->building->owner = (*player)->owner;
    (*ordi)->building->owner   = (*ordi)->owner;

    fclose(fd_ordi);

    printf("\nChargement reussi...\n");
    return TRUE;
} 