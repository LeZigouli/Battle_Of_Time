/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/
#ifndef _ORDINATEUR_H_
#define _ORDINATEUR_H_
#include <time.h>
#include "common.h"
#include "character.h"

typedef struct 
{
    int owner;
    int difficulte;
    int delai;
    int gold;
    tab_charactere_t * characters;
	building_t * building;
}ordi_t;

booleen_t init_building_or(ordi_t ** ordi);
booleen_t upgrade_building_or(ordi_t ** ordi);
booleen_t give_ressources(player_t ** player,ordi_t ** ordi);
ordi_t * init_ordi(int difficulte);
int detr_ordi(ordi_t ** ordi);
int envoie_char(ordi_t ** ordi, character_t * tab);
booleen_t afficher_building_or(ordi_t * ordi);
void afficher_ordi(ordi_t * ordi);

void jeux_ordi(ordi_t * o, player_t * p, character_t * tab);

#endif