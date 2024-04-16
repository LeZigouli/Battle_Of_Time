#include "../lib/character.h"

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
    if(destination == NULL || src == NULL || (*destination) == NULL || (*src) == NULL )
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



int calcule_prix(int n) {
    int term = 50;
    for (int i = 1; i < n; ++i) {
        switch(i % 4)
        {
        case 1:
            term = (int) (term * 1.5);
            break;
        case 2:
        case 3:
            term = (int) (term *2);
            break;
        
        default:
            term = (int) (term /3);
            break;
        }
    }
    return term;
}

int temp_former(int n) {
    if (n == 1 || n == 2) {
        return 2;
    }
    if (n == 3) {
        return 4;
    }
    if (n % 3 == 0) {
        return temp_former(n - 1);
    }
    if (n % 3 == 1) {
        return temp_former(n - 2);
    }
    if (n % 3 == 2) {
        return temp_former(n - 3) + temp_former(n - 2) + temp_former(n - 1);
    }
    return 0;  // Ce cas ne devrait jamais se produire
}

/* fonction pour initialiser tous les personnages */
character_t * initcharacter()
{
    character_t * tab = malloc((NB_AGE * NB_CHARACTER ) * sizeof(character_t));   
    
    if( tab != NULL ){
        /* Initialisation de chaque personnage */        
        int age,classe;
        for(age=0;age<NB_AGE;age++){
            for(classe=0;classe<NB_CHARACTER;classe++){
                tab[age*NB_CHARACTER+classe].age              =age;
                tab[age*NB_CHARACTER+classe].classe           =classe;
                tab[age*NB_CHARACTER+classe].cost             =calcule_prix(age*NB_CHARACTER+classe+1);
                tab[age*NB_CHARACTER+classe].dammage          =(((age+1)*8)*((age+2)*7)*20+(classe+1)*(classe+2)*48)/5;
                tab[age*NB_CHARACTER+classe].max_pv           =((age+1)*8)*((age+2)*7)*20+(classe+1)*(classe+2)*48;
                tab[age*NB_CHARACTER+classe].owner            =OWNER_INIT;
                tab[age*NB_CHARACTER+classe].pv               =((age+1)*8)*((age+2)*7)*20+(classe+1)*(classe+2)*48;
                tab[age*NB_CHARACTER+classe].ratio_ressources =RATIO_RESSOURCES;
                tab[age*NB_CHARACTER+classe].time             =temp_former(age*NB_CHARACTER+classe+1);
                tab[age*NB_CHARACTER+classe].vector           =(age*NB_CHARACTER+classe+1)/4 + 4;
                tab[age*NB_CHARACTER+classe].x                =0;
                tab[age*NB_CHARACTER+classe].y                =0;

                switch (age)
                {
                case Prehistoire:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Préhistoire/");
                    break;
                
                case Antiquite:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Antiquité/");
                    break;
                
                case Moyen_Age:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Moyen age/");
                    break;

                case Ere_Moderne:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Ere moderne/");
                    break;
                
                case Ere_Futuriste:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Ere futuriste/");
                    break;
                }
                switch (classe)
                {
                case melee:
                    strcat(tab[age*NB_CHARACTER+classe].sprite,"melee.png");
                    break;
                
                case marksman:
                    strcat(tab[age*NB_CHARACTER+classe].sprite,"marksman.png");
                    break;
                
                case tank:
                    strcat(tab[age*NB_CHARACTER+classe].sprite,"tank.png");
                    break;
                
                default:
                    strcat(tab[age*NB_CHARACTER+classe].sprite,"specialist.png");
                    break;
                }
            }
        }
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
    if((*destination) == NULL || src == NULL){
        printf("Erreur : copie character un des pointeurs NULL \n");
        return FALSE;
    }
    
    (*destination)->age              = src->age;
    (*destination)->classe           = src->classe;
    (*destination)->cost             = src->cost;
    (*destination)->dammage          = src->dammage;
    strcpy((*destination)->description,"");
    (*destination)->max_pv           = src->max_pv;
    strcpy((*destination)->name,"");
    (*destination)->owner            = src->owner;
    (*destination)->pv               = src->pv;
    (*destination)->ratio_ressources = src->ratio_ressources;
    strcpy((*destination)->sprite, src->sprite);
    (*destination)->time             = src->time;
    (*destination)->vector           = src->vector;
    (*destination)->x                = src->x;
    (*destination)->y                = src->y;

    return TRUE;
}



