/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 12 avril 2024
 * \version 1.0
 * 
*/
#include "../lib/ordinateur.h"


unsigned long int debut,fin,d_ulti,f_ulti;

/**
 * \fn ordi_t * init_ordi()
 * \brief Initialise et retourne un nouvel objet ordinateur.
 * \return Un pointeur vers l'ordinateur initialisé ou NULL en cas d'échec.
 */
ordi_t * init_ordi()
{
    ordi_t * ordi=malloc(sizeof(ordi_t));
    if(ordi !=NULL){
        ordi->owner=ORDINATEUR;
        if(init_building(&ordi->building,ORDINATEUR)){
            ordi->characters=malloc(sizeof(tab_charactere_t));
            if(ordi->characters!=NULL){
                ordi->characters->nb=0;
                for(int i=0; i<MAX_POSSESSED;i++)
                    ordi->characters->tab[i]=NULL;
                ordi->delai=DELAI_INITIAL;
                ordi->xp=0;
                ordi->delai_ulti=DELAI_INITIAL;
                srand(time(NULL));
                return ordi;
            }
            free(ordi->building);
        }
        free(ordi);
        ordi=NULL;
    }
    return NULL;
}

/**
 * \fn int detr_ordi(ordi_t ** ordi)
 * \brief Libère la mémoire allouée pour l'ordinateur.
 * \param ordi Un pointeur vers le pointeur de l'ordinateur à libérer.
 * \return EXIT_SUCCESS si la libération est réussie, EXIT_FAILURE sinon.
 */
int detr_ordi(ordi_t ** ordi)
{
    int i;
    free((*ordi)->building);
    if((*ordi)->characters!=NULL){
        for(i=0;i<(*ordi)->characters->nb;i++)
            free((*ordi)->characters->tab[i]);
        free((*ordi)->characters);
    }
    free(*ordi);
    *ordi=NULL;
    return EXIT_SUCCESS;
}

/**
 * \fn int envoie_char_ordi(ordi_t * ordi, character_t * tab)
 * \brief Envoie un personnage de l'ordinateur.
 * \param ordi L'ordinateur qui envoie le personnage.
 * \param tab Le tableau de personnages disponibles.
 * \return EXIT_SUCCESS si l'envoi réussit, EXIT_FAILURE sinon.
 */
int envoie_char_ordi(ordi_t * ordi, character_t * tab)
{
    character_t * new=malloc(sizeof(character_t));
    if(new!=NULL){
        int newCha;
        if(ordi->characters->nb < MAX_POSSESSED){
            newCha=rand()%NB_CHARACTER;
            copie_character(&new,&tab[(ordi->building->level)*NB_CHARACTER+newCha]);
            ordi->characters->tab[ordi->characters->nb]=new;
            ordi->characters->tab[ordi->characters->nb]->owner=ORDINATEUR;
            ordi->characters->tab[ordi->characters->nb]->x= POS_DEP_AD;
            ordi->characters->nb++;
            return EXIT_SUCCESS;
        }
        /*Liberation de l'espace mémoir dans le cas où ordi->characters->nb == Max possesed*/
        free(new);
    }
    return EXIT_FAILURE;    
}

/**
 * \fn booleen_t give_ressources(player_t * player,ordi_t * ordi)
 * \brief Donne des ressources au joueur à partir de l'ordinateur.
 * \param player Le joueur à qui donner les ressources.
 * \param ordi L'ordinateur qui fournit les ressources.
 * \return FALSE si l'opération échoue, TRUE sinon.
 */
booleen_t give_ressources(player_t * player,ordi_t * ordi)
{
    int gain=0;
    if(ordi->characters->tab[0]!=NULL){
        if(ordi->characters->tab[0]->pv <= 0){
            gain=ordi->characters->tab[0]->ratio_ressources * (ordi->characters->tab[0]->cost * 2);
            player->gold+= gain/3;
            player->xp += gain;
            ordi->xp+=gain;
        }
    }
    return FALSE;
}

/**
 * \brief Fonction principale de jeu de l'ordinateur.
 * \param o L'ordinateur.
 * \param p Le joueur.
 * \param tab Le tableau de personnages disponibles.
 */
void jeu_ordi(ordi_t * o, player_t * p, character_t * tab){
    if(o->delai == DELAI_INITIAL){
        o->delai=rand()%(MAX_DELAI/(o->difficulte))+MIN_DELAI;
        debut=time(NULL);
    }
    if(o->delai_ulti == DELAI_INITIAL){
        o->delai_ulti=rand()%(MAX_DELAI_ULTI-MIN_DELAI_ULTI)+MIN_DELAI_ULTI;
        d_ulti=time(NULL);
    }
    
    if(o->xp > o->building->XP_cost-((o->difficulte*8)/100)*o->building->XP_cost)
        upgrade_building(&o->building,&o->xp);
    
    fin=time(NULL);
    f_ulti=fin;
    if(difftime(fin,debut) >= o->delai){
        envoie_char_ordi(o,tab);
        o->delai=DELAI_INITIAL;
    }
    if(difftime(f_ulti,d_ulti) >= o->delai_ulti){
        ulti(&p->characters);
        o->delai_ulti=DELAI_INITIAL;
    }
}