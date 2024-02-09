/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/
#include "../lib/ordinateur.h"

ordi_t * init_ordi(int difficulte){
    ordi_t * ordi=malloc(sizeof(ordi_t));
    ordi->owner=OWNER_2;
    init_bulding(&ordi);
    ordi->characters=NULL;
}

int envoie_char(ordi_t ** ordi,age_t current ){
    srand(time(NULL));
    if((*ordi)->characters==NULL){
        (*ordi)->characters=malloc(sizeof(character_t)*MAX_POSSESSED);
        (*ordi)->characters->nb=0;
    }
    if((*ordi)->characters->nb < MAX_POSSESSED){
        
         newCha=rand()%NB_CHARACTER;
        
    }

}
