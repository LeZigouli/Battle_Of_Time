#include <stdio.h>
#include <stdlib.h>
#include "../lib/ordinateur.h"
#include "../lib/character.h"

/**
 * \file test_ordie.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/

int main(){
    ordi_t *ordi=init_ordi(EASY);
    character_t * tab;
    tab=initcharacter();

    afficher_ordi(ordi);
    envoie_char(&ordi,Prehistoire,&tab);
    afficher_ordi(ordi);
    return 0;
}