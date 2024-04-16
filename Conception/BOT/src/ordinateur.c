/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 09 févrirer 2024
 * 
 * 
*/

/* ulti + prev jeux*/

#include "../lib/ordinateur.h"


unsigned long int debut,fin,d_ulti,f_ulti;

ordi_t * init_ordi(){
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

int detr_ordi(ordi_t ** ordi){
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

int envoie_char_ordi(ordi_t * ordi, character_t * tab){
    character_t * new=malloc(sizeof(character_t));
    if(new!=NULL){
        int newCha;
        if(ordi->characters->nb < MAX_POSSESSED){
            newCha=rand()%NB_CHARACTER;
            copie_character(&new,&tab[(ordi->building->level)*NB_CHARACTER+newCha]);
            ordi->characters->tab[ordi->characters->nb]=new;
            ordi->characters->tab[ordi->characters->nb]->owner=ORDINATEUR;
            ordi->characters->tab[ordi->characters->nb]->x=IMAGE_WIDTH;
            ordi->characters->nb++;
            ordi->xp+= new->cost*new->ratio_ressources;
            return EXIT_SUCCESS;
        }
        /*Liberation de l'espace mémoir dans le cas où ordi->characters->nb == Max possesed*/
        free(new);
    }
    return EXIT_FAILURE;    
}

booleen_t give_ressources(player_t * player,ordi_t * ordi){
    int gain=0;
    if(ordi->characters->tab[0]!=NULL){
        if(ordi->characters->tab[0]->pv <= 0){
            gain=ordi->characters->tab[0]->ratio_ressources * ordi->characters->tab[0]->cost;
            player->gold+= gain;
            player->xp += gain;
        }
    }
    return FALSE;
}



void afficher_ordi(ordi_t * ordi){
    printf("{  ################## ORDINATEUR ################## \n");
    printf("Troupe :\n{\n");
    if(ordi->characters!=NULL){
        afficher_characters(ordi->characters);
    }
    afficher_building(ordi->building);
}

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
    give_ressources(p,o);

}