#include "../lib/common.h"

/*******************/
/* variable global */
/*******************/


/************/
/* fonction */
/************/

/* fonction où la src inflige ses degats a la destination character */
booleen_t character_attack_character(character_t ** destination, character_t ** src)
{
    if( (*destination) == NULL || destination == NULL || src == NULL || (*src) == NULL )
    {
        /* les pointeurs sont invalides */
        return FALSE;
    }

    (*destination)->pv -= (*src)->dammage;

    return TRUE;
}

/* fonction où la src inflige ses degats a la destination building */
booleen_t character_attack_building(building_t ** destination, character_t ** src)
{
    if( (*destination) == NULL || destination == NULL || src == NULL || (*src) == NULL )
    {
        /* les pointeurs sont invalides */
        return FALSE;
    }

    (*destination)->pv -= (*src)->dammage;

    return TRUE;
}

void deplacement_gauche(character_t ** character)
{
    (*character)->x -= (*character)->vector;
}

void deplacement_droit(character_t ** character)
{
    (*character)->x += (*character)->vector;
}

/* fonction pour initialiser tous les personnages */
character_t * initcharacter()
{
    character_t * tab = malloc((NB_AGE * NB_CHARACTER )* sizeof(character_t));   
    
    if( tab != NULL ){
        /* Initialisation de chaque personnage */

        /*********************/
        /* AGE PREHISTORIQUE */
        /*********************/

        /* combattant massue */
        strcpy(tab[Prehistoire * NB_CHARACTER + combattant_massue].name,"combattant massue");
        tab[Prehistoire * NB_CHARACTER + combattant_massue].time = 5;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].cost = 100;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].pv = 100;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].ratio_ressources = 1.25;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].dammage = 20;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].owner = -1;
        strcpy(tab[Prehistoire * NB_CHARACTER + combattant_massue].description,"Ceci est la description");
        tab[Prehistoire * NB_CHARACTER + combattant_massue].x = 0;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].y = 0;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].max_pv = tab[Prehistoire * NB_CHARACTER + combattant_massue].pv;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;


        /* combattant caillou */
        strcpy(tab[Prehistoire * NB_CHARACTER + combattant_caillou].name,"combattant caillou");
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].time = 7;
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].cost = 150;
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].pv = 125;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].ratio_ressources = 1.25;
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].dammage = 33;
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].owner = -1;
        strcpy(tab[Prehistoire * NB_CHARACTER + combattant_caillou].description,"Ceci est la description");
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].x = 0;
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].y = 0;
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].max_pv = tab[Prehistoire * NB_CHARACTER + combattant_massue].pv;
        tab[Prehistoire * NB_CHARACTER + combattant_caillou].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;


        /* gorille */
        strcpy(tab[Prehistoire * NB_CHARACTER + gorille].name,"gorille");
        tab[Prehistoire * NB_CHARACTER + gorille].time = 7;
        tab[Prehistoire * NB_CHARACTER + gorille].cost = 150;
        tab[Prehistoire * NB_CHARACTER + gorille].pv = -125;
        tab[Prehistoire * NB_CHARACTER + gorille].ratio_ressources = 1.25;
        tab[Prehistoire * NB_CHARACTER + gorille].dammage = 33;
        tab[Prehistoire * NB_CHARACTER + gorille].owner = -1;
        strcpy(tab[Prehistoire * NB_CHARACTER + gorille].description,"Ceci est la description");
        tab[Prehistoire * NB_CHARACTER + gorille].x = 0;
        tab[Prehistoire * NB_CHARACTER + gorille].y = 0;
        tab[Prehistoire * NB_CHARACTER + gorille].max_pv = tab[Prehistoire * NB_CHARACTER + gorille].pv;
        tab[Prehistoire * NB_CHARACTER + gorille].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* combattant dinosaure */
        strcpy(tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].name,"combattant dinosaure");
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].time = 7;
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].cost = 150;
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].pv = 125;
        tab[Prehistoire * NB_CHARACTER +combattant_dinosaure].ratio_ressources = 1.25;
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].dammage = 33;
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].owner = -1;
        strcpy(tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].description,"Ceci est la description");
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].x = 0;
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].y = 0;
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].max_pv = tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].pv;
        tab[Prehistoire * NB_CHARACTER + combattant_dinosaure].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /*************/
        /* ANTIQUITE */
        /*************/

        /* legionnaire epee */
        strcpy(tab[Antiquite * NB_CHARACTER + legionnaire_epee].name,"legionnaire epee");
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].time = 7;
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].cost = 150;
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].pv = 125;
        tab[Antiquite * NB_CHARACTER +legionnaire_epee].ratio_ressources = 1.25;
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].dammage = 33;
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].owner = -1;
        strcpy(tab[Antiquite * NB_CHARACTER + legionnaire_epee].description,"Ceci est la description");
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].x = 0;
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].y = 0;
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].max_pv = tab[Antiquite * NB_CHARACTER + legionnaire_epee].pv;
        tab[Antiquite * NB_CHARACTER + legionnaire_epee].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* legionnaire lance */
        strcpy(tab[Antiquite * NB_CHARACTER + legionnauire_lance].name,"legionnaire lance");
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].time = 7;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].cost = 150;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].pv = 125;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].ratio_ressources = 1.25;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].dammage = 33;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].owner = -1;
        strcpy(tab[Antiquite * NB_CHARACTER + legionnauire_lance].description,"Ceci est la description");
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].x = 0;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].y = 0;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].max_pv = tab[Antiquite * NB_CHARACTER + legionnauire_lance].pv;
        tab[Antiquite * NB_CHARACTER + legionnauire_lance].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* legionnaire cheval */
        strcpy(tab[Antiquite * NB_CHARACTER + legionnaire_cheval].name,"legionnaire cheval");
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].time = 7;
        tab[Prehistoire * NB_CHARACTER + legionnaire_cheval].cost = 150;
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].pv = 125;
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].ratio_ressources = 1.25;
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].dammage = 33;
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].owner = -1;
        strcpy(tab[Antiquite * NB_CHARACTER + legionnaire_cheval].description,"Ceci est la description");
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].x = 0;
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].y = 0;
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].max_pv = tab[Antiquite * NB_CHARACTER + legionnaire_cheval].pv;
        tab[Antiquite * NB_CHARACTER + legionnaire_cheval].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* legionnaire hippopotame */
        strcpy(tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].name,"legionnaire hippopotame");
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].time = 7;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].cost = 150;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].pv = 125;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].ratio_ressources = 1.25;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].dammage = 33;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].owner = -1;
        strcpy(tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].description,"Ceci est la description");
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].x = 0;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].y = 0;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].max_pv = tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].pv;
        tab[Antiquite * NB_CHARACTER + legionnaire_hippopotame].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /*************/
        /* MOYEN-AGE */
        /*************/

        /* chevalier epee bouclier */
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].name,"chevalier epee bouclier");
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].time = 7;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].cost = 150;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].pv = 125;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].ratio_ressources = 1.25;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].dammage = 33;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].owner = -1;
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].description,"Ceci est la description");
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].x = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].y = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].max_pv = tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].pv;
        tab[Moyen_Age * NB_CHARACTER + chevalier_epee_bouclier].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* chevalier fronde */
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].name,"chevalier fronde");
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].time = 7;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].cost = 150;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].pv = 125;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].ratio_ressources = 1.25;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].dammage = 33;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].owner = -1;
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].description,"Ceci est la description");
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].x = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].y = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].max_pv = tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].pv;
        tab[Moyen_Age * NB_CHARACTER + chevalier_fronde].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* chevalier_tortue */
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].name,"chevalier tortue");
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].time = 7;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].cost = 150;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].pv = 125;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].ratio_ressources = 1.25;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].dammage = 33;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].owner = -1;
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].description,"Ceci est la description");
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].x = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].y = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].max_pv = tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].pv;
        tab[Moyen_Age * NB_CHARACTER + chevalier_tortue].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* chevalier_poulet */
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].name,"chevalier poulet");
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].time = 7;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].cost = 150;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].pv = 125;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].ratio_ressources = 1.25;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].dammage = 33;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].owner = -1;
        strcpy(tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].description,"Ceci est la description");
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].x = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].y = 0;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].max_pv = tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].pv;
        tab[Moyen_Age * NB_CHARACTER + chevalier_poulet].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /***************/
        /* ERE MODERNE */
        /***************/

        /* samurai */
        strcpy(tab[Ere_Moderne * NB_CHARACTER + samurai].name,"samurai");
        tab[Ere_Moderne * NB_CHARACTER + samurai].time = 7;
        tab[Ere_Moderne * NB_CHARACTER + samurai].cost = 150;
        tab[Ere_Moderne * NB_CHARACTER + samurai].pv = 125;
        tab[Ere_Moderne * NB_CHARACTER + samurai].ratio_ressources = 1.25;
        tab[Ere_Moderne * NB_CHARACTER + samurai].dammage = 33;
        tab[Ere_Moderne * NB_CHARACTER + samurai].owner = -1;
        strcpy(tab[Ere_Moderne * NB_CHARACTER + samurai].description,"Ceci est la description");
        tab[Ere_Moderne * NB_CHARACTER + samurai].x = 0;
        tab[Ere_Moderne * NB_CHARACTER + samurai].y = 0;
        tab[Ere_Moderne * NB_CHARACTER + samurai].max_pv = tab[Ere_Moderne * NB_CHARACTER + samurai].pv;
        tab[Ere_Moderne * NB_CHARACTER + samurai].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* soldat militaire */
        strcpy(tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].name,"soldat militaire");
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].time = 7;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].cost = 150;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].pv = 125;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].ratio_ressources = 1.25;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].dammage = 33;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].owner = -1;
        strcpy(tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].description,"Ceci est la description");
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].x = 0;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].y = 0;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].max_pv = tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].pv;
        tab[Ere_Moderne * NB_CHARACTER + soldat_militaire].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* avatar*/
        strcpy(tab[Ere_Moderne * NB_CHARACTER + avatar].name,"avatar");
        tab[Ere_Moderne * NB_CHARACTER + avatar].time = 7;
        tab[Ere_Moderne * NB_CHARACTER + avatar].cost = 150;
        tab[Ere_Moderne * NB_CHARACTER + avatar].pv = 125;
        tab[Ere_Moderne * NB_CHARACTER + avatar].ratio_ressources = 1.25;
        tab[Ere_Moderne * NB_CHARACTER + avatar].dammage = 33;
        tab[Ere_Moderne * NB_CHARACTER + avatar].owner = -1;
        strcpy(tab[Ere_Moderne * NB_CHARACTER + avatar].description,"Ceci est la description");
        tab[Ere_Moderne * NB_CHARACTER + avatar].x = 0;
        tab[Ere_Moderne * NB_CHARACTER + avatar].y = 0;
        tab[Ere_Moderne * NB_CHARACTER + avatar].max_pv = tab[Ere_Moderne * NB_CHARACTER + avatar].pv;
        tab[Ere_Moderne * NB_CHARACTER + avatar].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* panzer */
        strcpy(tab[Ere_Moderne * NB_CHARACTER + panzer].name,"panzer");
        tab[Ere_Moderne * NB_CHARACTER + panzer].time = 7;
        tab[Ere_Moderne * NB_CHARACTER + panzer].cost = 150;
        tab[Ere_Moderne * NB_CHARACTER + panzer].pv = 125;
        tab[Ere_Moderne * NB_CHARACTER + panzer].ratio_ressources = 1.25;
        tab[Ere_Moderne * NB_CHARACTER + panzer].dammage = 33;
        tab[Ere_Moderne * NB_CHARACTER + panzer].owner = -1;
        strcpy(tab[Ere_Moderne * NB_CHARACTER + panzer].description,"Ceci est la description");
        tab[Ere_Moderne * NB_CHARACTER + panzer].x = 0;
        tab[Ere_Moderne * NB_CHARACTER + panzer].y = 0;
        tab[Ere_Moderne * NB_CHARACTER + panzer].max_pv = tab[Ere_Moderne * NB_CHARACTER + panzer].pv;
        tab[Ere_Moderne * NB_CHARACTER + panzer].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /*****************/
        /* ERE FUTURISTE */
        /*****************/

        /* soldat sabre laser */
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].name,"soldat sabre laser");
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].time = 7;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].cost = 150;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].pv = 125;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].ratio_ressources = 1.25;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].dammage = 33;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].owner = -1;
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].description,"Ceci est la description");
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].x = 0;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].y = 0;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].max_pv = tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].pv;
        tab[Ere_Futuriste * NB_CHARACTER + soldat_sabre_laser].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* gros poulet */
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].name,"gros poulet");
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].time = 7;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].cost = 150;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].pv = 125;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].ratio_ressources = 1.25;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].dammage = 33;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].owner = -1;
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].description,"Ceci est la description");
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].x = 0;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].y = 0;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].max_pv = tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].pv;
        tab[Ere_Futuriste * NB_CHARACTER + gros_poulet].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* banane geante */
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + banane_geante].name,"banane geante");
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].time = 7;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].cost = 150;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].pv = 125;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].ratio_ressources = 1.25;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].dammage = 33;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].owner = -1;
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + banane_geante].description,"Ceci est la description");
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].x = 0;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].y = 0;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].max_pv = tab[Ere_Futuriste * NB_CHARACTER + banane_geante].pv;
        tab[Ere_Futuriste * NB_CHARACTER + banane_geante].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
        /* alien */
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + alien].name,"alien");
        tab[Ere_Futuriste * NB_CHARACTER + alien].time = 7;
        tab[Ere_Futuriste * NB_CHARACTER + alien].cost = 150;
        tab[Ere_Futuriste * NB_CHARACTER + alien].pv = 125;
        tab[Ere_Futuriste * NB_CHARACTER + alien].ratio_ressources = 1.25;
        tab[Ere_Futuriste * NB_CHARACTER + alien].dammage = 33;
        tab[Ere_Futuriste * NB_CHARACTER + alien].owner = -1;
        strcpy(tab[Ere_Futuriste * NB_CHARACTER + alien].description,"Ceci est la description");
        tab[Ere_Futuriste * NB_CHARACTER + alien].x = 0;
        tab[Ere_Futuriste * NB_CHARACTER + alien].y = 0;
        tab[Ere_Futuriste * NB_CHARACTER + alien].max_pv = tab[Ere_Futuriste * NB_CHARACTER + alien].pv;
        tab[Ere_Futuriste * NB_CHARACTER + alien].vector = 2;
        /* pointeur sur fonction */
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_droit = deplacement_droit;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].deplacement_gauche = deplacement_gauche;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_character = character_attack_character;
        tab[Prehistoire * NB_CHARACTER + combattant_massue].attack_building = character_attack_building;

        
    }
    return tab;
}

/* detruire la memoire du tableau de character */
booleen_t destroy_tab_character(character_t ** tab )
{
    free((*tab));
    (*tab) = NULL;
    return TRUE;
}


booleen_t copie_character(character_t ** destination, character_t * src)
{
    afficher_character(**destination);
    //afficher_character(*src);
    if((*destination) == NULL || src == NULL){
        printf("Erreur : copie character un des pointeurs NULL \n");
        return FALSE;
    }
    
    (*destination)->pv = src->pv;
    strcpy((*destination)->name,src->name);
    (*destination)->time = src->time;
    (*destination)->cost = src->cost;
    (*destination)->max_pv = src->max_pv;
    (*destination)->ratio_ressources = src->ratio_ressources;
    (*destination)->dammage = src->dammage;
    (*destination)->owner = src->owner;
    strcpy((*destination)->description,src->description);
    (*destination)->x = src->x;
    (*destination)->y = src->y;
    (*destination)->vector = src->vector;

    return TRUE;
}



