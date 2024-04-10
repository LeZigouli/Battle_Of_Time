#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
#define DELAI_INITAL -1

typedef enum age_s { Prehistoire, Antiquite, Moyen_Age, Ere_Moderne, Ere_Futuriste }age_t;
typedef enum monstre_Prehistoire_s { combattant_massue, combattant_caillou, gorille, combattant_dinosaure }monstre_Prehistoire_t;
typedef enum monstre_Antiquite_s { legionnaire_epee, legionnauire_lance, legionnaire_cheval, legionnaire_hippopotame }monstre_Antiquite_t;
typedef enum monstre_Moyen_Age_s { chevalier_epee_bouclier,chevalier_fronde, chevalier_tortue, chevalier_poulet }monstre_Moyen_Age_t;
typedef enum monstre_Ere_Moderne_s { samurai, soldat_militaire, avatar, panzer }monstre_Ere_Moderne_t;
typedef enum monstre_Ere_futuriste_s { soldat_sabre_laser, gros_poulet, banane_geante, alien }monstre_Ere_futuriste_t;
typedef enum class_character_s { melee, marksman, tank, specialist }class_character_t;

/* definition d'un type booleen */
typedef enum booleen_s { FALSE, TRUE } booleen_t;


/* fonction */

#endif