/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/common.h"

typedef struct 
{
    /* data */
    int owner;
    tab_charactere_t * characters;
	building_t * building;
}ordi_t;


ordi_t * init_ordi(int difficulte);