/**
 * \file character.c
 * \brief Contient les fonction pour les personnages du jeu
 * \author Roquain Lousion Proudy Vincent
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/
#include "../lib/character.h"

/**
 * @brief Fonction permettant à un personnage d'attaquer un autre personnage.
 * 
 * @param destination Le personnage cible de l'attaque.
 * @param src Le personnage effectuant l'attaque.
 * @return TRUE si l'opération s'est déroulée avec succès, FALSE sinon.
 */
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


/**
 * @brief Fonction permettant à un personnage d'attaquer un bâtiment.
 * 
 * @param destination Le bâtiment cible de l'attaque.
 * @param src Le personnage effectuant l'attaque.
 * @return TRUE si l'opération s'est déroulée avec succès, FALSE sinon.
 */
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


/**
 * @brief Déplace un personnage vers la gauche.
 * 
 * @param character Le personnage à déplacer.
 */
void deplacement_gauche(character_t ** character)
{
    (*character)->x -= (*character)->vector;
}

/**
 * @brief Déplace un personnage vers la droite.
 * 
 * @param character Le personnage à déplacer.
 */
void deplacement_droit(character_t ** character)
{
    (*character)->x += (*character)->vector;
}


/**
 * @brief Calcule le prix d'un personnage en fonction de son niveau.
 * 
 * @param n Le niveau du personnage.
 * @return Le prix calculé.
 */
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

/**
 * @brief Calcule le temps nécessaire à la formation d'un personnage en fonction de son niveau.
 * 
 * @param n Le niveau du personnage.
 * @return Le temps de formation calculé.
 */
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

/**
 * @brief Initialise tous les personnages du jeu.
 * 
 * @return Un pointeur vers un tableau de personnages initialisés.
 */
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
                tab[age*NB_CHARACTER+classe].first_Attaque    = TRUE;
                tab[age*NB_CHARACTER+classe].max_pv           =((age+1)*8)*((age+2)*7)*20+(classe+1)*(classe+2)*48;
                tab[age*NB_CHARACTER+classe].owner            =OWNER_INIT;
                tab[age*NB_CHARACTER+classe].pv               =((age+1)*8)*((age+2)*7)*20+(classe+1)*(classe+2)*48;
                tab[age*NB_CHARACTER+classe].ratio_ressources =RATIO_RESSOURCES;
                tab[age*NB_CHARACTER+classe].time             =temp_former(age*NB_CHARACTER+classe+1);
                tab[age*NB_CHARACTER+classe].vector           =(age*NB_CHARACTER+classe+1)/4 + 25;
                tab[age*NB_CHARACTER+classe].x                =0;
                tab[age*NB_CHARACTER+classe].x_pred           =0;
                tab[age*NB_CHARACTER+classe].y                =0;

                switch (age)
                {
                case Prehistoire:

                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Préhistoire/");
                    
                    switch(classe)
                    {
                        case 0 : 
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Combattant massue");
                            break;

                        case 1 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Combattant caillou");
                            break;

                        case 2 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Gorille");
                            break;
                            
                         case 3 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Combattant dinosaure");
                            break;
                    }
                    break;
                
                case Antiquite:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Antiquité/");
                    
                    switch(classe)
                    {
                        case 0 : 
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Légionnaire épee");
                            break;

                        case 1 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Légionnaire lance");
                            break;

                        case 2 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Chevalier");
                            break;
                            
                         case 3 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Sorciere");
                            break;
                    }
                    
                    break;
                
                case Moyen_Age:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Moyen age/");
                    
                    switch(classe)
                    {
                        case 0 : 
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Chevalier épée bouclier");
                            break;

                        case 1 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Archer");
                            break;

                        case 2 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Princesse");
                            break;
                            
                         case 3 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Zombie");
                            break;
                    }
                    
                    break;

                case Ere_Moderne:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Ere moderne/");
                    
                    switch(classe)
                    {
                        case 0 : 
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Samurai");
                            break;

                        case 1 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Soldat");
                            break;

                        case 2 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Avatar");
                            break;
                            
                         case 3 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Pere noel");
                            break;
                    }

                    break;
                
                case Ere_Futuriste:
                    strcpy(tab[age*NB_CHARACTER+classe].sprite,"img/sprite/Ere futuriste/");
                    
                    switch(classe)
                    {
                        case 0 : 
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Jedhi");
                            break;

                        case 1 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Squellette");
                            break;

                        case 2 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Ogre");
                            break;
                            
                         case 3 :
                            strcpy(tab[age*NB_CHARACTER+classe].description,"Alien");
                            break;
                    }
                    
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


/**
 * @brief Libère la mémoire allouée pour le tableau de personnages.
 * 
 * @param tab Un pointeur vers le tableau de personnages à détruire.
 * @return TRUE si l'opération s'est déroulée avec succès, FALSE sinon.
 */
booleen_t destroy_tab_character(character_t ** tab )
{
    free((*tab));
    (*tab) = NULL;
    return TRUE;
}

/**
 * @brief Copie les données d'un personnage source vers un personnage destination.
 * 
 * @param destination Le personnage de destination.
 * @param src Le personnage source.
 * @return TRUE si l'opération s'est déroulée avec succès, FALSE sinon.
 */
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
    (*destination)->x_pred           = src->x_pred;
    (*destination)->y                = src->y;

    return TRUE;
}



