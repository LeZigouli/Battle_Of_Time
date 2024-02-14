#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#define COEF_LEVEL_UP_MAX_GOLD_COST 1.5

/* LIMITE DU NOMBRE DE FOIS QU'ON PEUT AMELIORER LE BUILDING */
#define MAX_LEVEL_UP 5

/* NUMERO OWNER */
#define OWNER_1 1
#define OWNER_2 2

typedef enum age_s { Prehistoire, Antiquite, Moyen_Age, Ere_Moderne, Ere_Futuriste }age_t;
typedef enum monstre_Prehistoire_s { combattant_massue, combattant_caillou, gorille, combattant_dinosaure }monstre_Prehistoire_t;
typedef enum monstre_Antiquite_s { legionnaire_epee, legionnauire_lance, legionnaire_cheval, legionnaire_hippopotame }monstre_Antiquite_t;
typedef enum monstre_Moyen_Age_s { chevalier_epee_bouclier,chevalier_fronde, chevalier_tortue, chevalier_poulet }monstre_Moyen_Age_t;
typedef enum monstre_Ere_Moderne_s { samurai, soldat_militaire, avatar, panzer }monstre_Ere_Moderne_t;
typedef enum monstre_Ere_futuriste_s { soldat_sabre_laser, gros_poulet, banane_geante, alien }monstre_Ere_futuriste_t;
typedef enum class_character_s { melee, marksman, tank, specialist }class_character_t;

/* definition d'un type booleen */
typedef enum booleen_s { FALSE, TRUE } booleen_t;


/* definition des structure */

typedef struct building_s{

	int pv;
	int owner;
	int dammage;
	int max_pv;
	int GOLD_cost;
	int level;

}building_t;

typedef struct character_s character_t;
struct character_s{

	int pv;
	char name[MAX_STR];
	int time; 
	int cost; 
	int max_pv;
	float ratio_ressources;
	int dammage;
	int owner; 
	char description[MAX_DESCRIPTION];
	int x;
	int y;
	int vector;

	/* pointeur sur fonction pour le deplacement */
	void (*deplacement_gauche)(character_t **);
	void (*deplacement_droit)(character_t **);

	/* pointeur sur fonction pour attaquer */
	booleen_t (*attack_character)(character_t **, character_t **);
	booleen_t (*attack_building)(building_t **, character_t **);

};

/* liste pour chaque joueur des personnages qu'ils possèdent */
typedef struct tab_charactere_s{

	character_t * tab[MAX_POSSESSED];
	int nb;

}tab_charactere_t;

typedef struct{

	char name[MAX_STR];
	int xp;
	float gold; 
	tab_charactere_t * characters;
	int owner;
	building_t * building;

}player_t;


/* fonction */

#endif