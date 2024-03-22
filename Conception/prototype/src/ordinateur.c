/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 09 févrirer 2024
 * 
 * 
*/
#include "../lib/ordinateur.h"
#define MAX_DELAI 15 /*en secondes*/
#define MIN_DELAI 1
unsigned long int debut,fin;

/* fonction pour creer le batiment de l'ordinateur */
booleen_t init_building_or(ordi_t ** ordi)
{
	/* verification préliminaire */
	if ( (*ordi) == NULL || ordi == NULL )
	{
		return FALSE;
	}

	/* allocation dynamique */
	(*ordi)->building = malloc(sizeof(building_t));

	if ( (*ordi)->building == NULL )
	{
		printf("ERREUR : allocation building !\n");
		return FALSE;
	}

	/* affectation */
	(*ordi)->building->dammage = 33;
	(*ordi)->building->GOLD_cost = 500;
	(*ordi)->building->level = 1;
	(*ordi)->building->pv = 300;
	(*ordi)->building->max_pv = (*ordi)->building->pv;
	(*ordi)->building->owner = (*ordi)->owner;

	return TRUE;
}

booleen_t upgrade_building_or(ordi_t ** ordi){
    if(ordi && (*ordi) && (*ordi)->building){
        if((*ordi)->building->level<MAX_LEVEL_UP)
        {
            /* a chaque upgrade on augmente les stat par le coef_level_up */
            (*ordi)->building->dammage *= COEF_LEVEL_UP_DAMMAGE;
            (*ordi)->building->max_pv *= COEF_LEVEL_UP_MAX_PV;
            (*ordi)->building->GOLD_cost *= COEF_LEVEL_UP_MAX_GOLD_COST;
            (*ordi)->building->pv += (*ordi)->building->max_pv*((COEF_LEVEL_UP_MAX_PV-1)/COEF_LEVEL_UP_MAX_PV);

            /* actualise le niveau du building */
            (*ordi)->building->level ++;
            
            (*ordi)->gold=0;
            return TRUE;
        }
    }
    return FALSE;
}

ordi_t * init_ordi(int difficulte){
    ordi_t * ordi=malloc(sizeof(ordi_t));
    ordi->owner=OWNER_2;
    init_building_or(&ordi);
    ordi->characters=malloc(sizeof(tab_charactere_t)*MAX_POSSESSED);
    ordi->characters->nb=0;
    ordi->difficulte=difficulte;
    ordi->delai=-1;
    ordi->gold=0;
    return ordi;
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
    return 0;
}

int envoie_char(ordi_t ** ordi, character_t * tab){
    character_t * new=malloc(sizeof(character_t));
    if(new!=NULL){
        int newCha;
        if((*ordi)->characters->nb < MAX_POSSESSED){
            newCha=rand()%NB_CHARACTER;
            copie_character(&new,&tab[((*ordi)->building->level-1) *NB_CHARACTER+newCha]);
            (*ordi)->characters->tab[(*ordi)->characters->nb]=new;
            (*ordi)->characters->nb++;
            (*ordi)->gold+= new->cost*new->ratio_ressources;
            return EXIT_SUCCESS;
        }
    }
    /*Liberation de l'espace mémoir dans le cas où (*ordi)->characters->nb == Max possesed*/
    free(new);
    return EXIT_FAILURE;    
}

booleen_t give_ressources(player_t ** player,ordi_t ** ordi){
    if((*ordi)->characters->tab[0]!=NULL){
        if((*ordi)->characters->tab[0]->pv <= 0){
            (*player)->gold+=(*ordi)->characters->tab[0]->ratio_ressources * (*ordi)->characters->tab[0]->cost;
            free((*ordi)->characters->tab[0]);
            (*ordi)->characters->tab[0]=NULL;
            (*ordi)->characters->nb--;
            for(int i=0;i<(*ordi)->characters->nb;i++)
                (*ordi)->characters->tab[i]=(*ordi)->characters->tab[i+1];
            return TRUE;
        }
    }
    if((*player)->characters->tab[0]!=NULL){
         if((*player)->characters->tab[0]->pv <= 0){
            free((*player)->characters->tab[0]);
            (*player)->characters->tab[0]=NULL;
            (*player)->characters->nb--;
            for(int i=0;i<(*player)->characters->nb;i++)
                (*player)->characters->tab[i]=(*player)->characters->tab[i+1];
            return TRUE;
         }
    }
    return FALSE;
}

booleen_t afficher_building_or(ordi_t * ordi)
{
    if ( ordi == NULL )
    {
        return FALSE;
    }

    printf("Building :\n{\n");
    printf("Owner : %d \nDammage : %d\nPV : %d\nGOLD_cost : %d\nLevel : %d\n",ordi->building->owner, ordi->building->dammage,ordi->building->pv, ordi->building->GOLD_cost, ordi->building->level);
    printf("<-------------------->\n\n");

    return TRUE;
}

void afficher_ordi(ordi_t * ordi){
    int i;
    printf("{\n");
    printf("Troupe :\n{\n");
    if(ordi->characters!=NULL){
        for(i=0;i<ordi->characters->nb;i++){
            if(ordi->characters->tab[i]!=NULL){
                printf("{");
                printf("pv: %d\tnom: %s}\n",ordi->characters->tab[i]->pv,ordi->characters->tab[i]->name);
            }
        }
    }
    printf("}\n");
    afficher_building_or(ordi);
    printf("}\n");
}

void jeu_ordi(ordi_t * o, player_t * p, character_t * tab){
    srand(time(NULL));
    if(o->delai < 0){
        o->delai=rand()%(MAX_DELAI/(o->difficulte+1));
        debut=time(NULL);
    }
    if(o->gold > o->building->GOLD_cost-((o->difficulte*15)/100)*o->building->GOLD_cost)
        upgrade_building_or(&o);

    fin=time(NULL);
    if(difftime(fin,debut) >= o->delai){
        envoie_char(&o,tab);
        debut=time(NULL);
        o->delai=rand()%(MAX_DELAI/(o->difficulte+1))+MIN_DELAI;
    }
    give_ressources(&p,&o);
}