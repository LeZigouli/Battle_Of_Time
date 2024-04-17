#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "commun_SDL.h"

/* NOMBRE D'AGE ET NOMBRE DE PERSONNAGE PAR AGE */
#define NB_AGE 5
#define NB_CHARACTER 4

/* LIMITE POUR LES TABLEAUX ET CHAINES DE CARACTERES */
#define MAX_STR 40
#define MAX_POSSESSED 10
#define MAX_DESCRIPTION 100

/* NIVEAU DU JEU */
#define EASY 1
#define MEDIUM 2
#define HARD 3

/* COEFF POUR LEVEL UP BUILDING */
#define COEF_LEVEL_UP_DAMMAGE 1.5
#define COEF_LEVEL_UP_MAX_PV 2.0
#define COEF_LEVEL_UP_MAX_GOLD_COST 3

/* LIMITE DU NOMBRE DE FOIS QU'ON PEUT AMELIORER LE BUILDING */
#define MAX_LEVEL_UP 4

/* NUMERO OWNER */
#define OWNER_1 1
#define OWNER_2 2
#define ORDINATEUR 3

/* INITIALISATION DU DÉLAI D'ATTENTE POUR FORMER LES TROUPES */
#define DELAI_INITIAL -1

/* FIN DE PARTIE */
#define JOUEUR_GAGNE 100
#define ORDI_GAGNE 101
#define AUCUN_GAGNANT 102
#define JOUEUR_EN_LIGNE_GAGNE 103

typedef enum class_character_s { melee, marksman, tank, specialist }class_character_t;

/* definition d'un type booleen */
typedef enum booleen_s { FALSE, TRUE } booleen_t;


/* fonction */

#endif
