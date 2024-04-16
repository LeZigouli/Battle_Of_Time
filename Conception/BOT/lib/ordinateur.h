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

#include "player.h"

#define MAX_DELAI 15 /*en secondes*/
#define MIN_DELAI 1
#define MAX_DELAI_ULTI 900 /* 15 min*/
#define MIN_DELAI_ULTI 300 /*  5 min*/
#

typedef struct 
{
    int owner;
    int difficulte;
    int delai;
    int xp;
    int delai_ulti;
    tab_charactere_t * characters;
	building_t * building;
}ordi_t;

ordi_t * init_ordi();
int detr_ordi(ordi_t ** ordi);
int envoie_char_ordi(ordi_t * ordi, character_t * tab);

booleen_t give_ressources(player_t * player,ordi_t * ordi);

void afficher_ordi(ordi_t * ordi);

void jeu_ordi(ordi_t * o, player_t * p, character_t * tab);

#endif