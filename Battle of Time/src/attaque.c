/**
 * \file attaque.c
 * \brief Contient les fonctions pour les animations des sprites
 * \author Victor Poirier Vincent Proudy Louison Roquain Thomas Wolter
 * \date 16 avril 2024
 * \version 1.0
 * 
*/

#include "../lib/attaque.h"

/**
 * \fn void resize_dep(SDL_Rect * atimg,SDL_Rect * position, character_t * c)
 * \brief Redimensionne la position et l'image du personnage pour la taille par défaut.
 *
 * Si le personnage n'est pas en train d'attaquer, cette fonction ajuste sa position et son image
 * à leur taille d'origine pour correspondre à la taille des sprites lors des animations différentes.
 *
 * \param atimg Pointeur vers la structure SDL_Rect représentant la position de l'image du personnage.
 * \param position Pointeur vers la structure SDL_Rect représentant la position du personnage.
 * \param c Pointeur vers la structure character_t représentant le personnage.
 */
void resize_dep(SDL_Rect * atimg,SDL_Rect * position, character_t * c)
{
//si le perso n'attaque plus on le remet a sa taille d'origine (car taille des sprite lors des animations différentes)
//playerPosition pour régler la taille, playerImg pour régler l'animation
    int ind = c->classe+c->age*NB_CHARACTER;
    
    switch(ind){
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 9:
        case 13:
        case 14:
        case 19:        
        case 0:
        case 4:
        case 7:
        case 8:
        case 10:
        case 12:
        case 11:
        case 15:
        case 16:
        case 17:
        case 18:
            position->h=TAILLE_SPRITE * 2;
            position->w=TAILLE_SPRITE * 2;
            break;
    }
}

/**
 * \fn void resize_att(SDL_Rect * atimg,SDL_Rect * position, character_t * c)
 * \brief Redimensionne la position et l'image du personnage pour l'animation d'attaque.
 *
 * Cette fonction ajuste la position et l'image du personnage pour l'animation d'attaque, en raison
 * de la différence de dimensions des sprites d'animation.
 *
 * \param atimg Pointeur vers la structure SDL_Rect représentant la position de l'image du personnage en attaque.
 * \param position Pointeur vers la structure SDL_Rect représentant la position du personnage.
 * \param c Pointeur vers la structure character_t représentant le personnage.
 */
void resize_att(SDL_Rect * atimg,SDL_Rect * position, character_t * c)
{
    //il faut resize car les png d'animations sont différents
    //les dimensions d'un sprite d'animation d'attaque est 3x plus grand d'ou le 128*3 pour height et width
    int ind = c->classe+c->age*NB_CHARACTER;
    
    switch(ind){
        case 1:
        case 3:
        case 9:
            atimg->x = 0;
            atimg->y = TAILLE_SPRITE*19;
            break;

        case 0:
        case 4:
        case 6:
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 17:
        case 18:
            atimg->x=0;
            atimg->y=TAILLE_SPRITE*10;
            break;

        case 2:
        case 5:
            atimg->x = 0;
            atimg->y = TAILLE_SPRITE*7;
            break;
        
        case 13:
        case 14:
        case 19:
            atimg->x = 0;
            atimg->y = TAILLE_SPRITE*15;
            break;

    }
}

/**
 * \fn void ataquage(SDL_Rect * atimg, character_t * c, int * attaque, int owner)
 * \brief Gère l'animation de l'attaque du personnage.
 *
 * Cette fonction gère l'animation de l'attaque du personnage en ajustant l'image affichée
 * pour simuler le mouvement d'attaque.
 *
 * \param atimg Pointeur vers la structure SDL_Rect représentant la position de l'image d'attaque du personnage.
 * \param c Pointeur vers la structure character_t représentant le personnage.
 * \param attaque Pointeur vers un entier indiquant si une attaque est en cours.
 * \param owner Indicateur du propriétaire de l'attaque (OWNER_1 ou OWNER_2).
 */
void ataquage(SDL_Rect * atimg, character_t * c, int * attaque, int owner)
{
    int ind = c->classe+c->age*NB_CHARACTER;

    int position_anim;
    int longueur_anim;

    switch(ind){    

        case 0:
        case 1:
        case 3:
        case 9:
        case 4:
        case 6:
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 17:
            longueur_anim = TAILLE_SPRITE*11; // 11 image 
            if ( owner == OWNER_1 ) position_anim = TAILLE_SPRITE*19; // position dans l'image
            else position_anim = TAILLE_SPRITE*17; // position dans l'image

            if(atimg->x == longueur_anim){
                atimg->x=0;
                *attaque=TRUE;
            }else 
            {
                atimg->y = position_anim;
                atimg->x+=TAILLE_SPRITE;
            }
            break;

        // personnage avec dague
        case 13:
        case 14:
        case 19:

                longueur_anim = TAILLE_SPRITE*7;
                if ( owner == OWNER_1 ) position_anim = TAILLE_SPRITE * 7;
                else position_anim = TAILLE_SPRITE * 5;

                if(atimg->x == longueur_anim){
                    atimg->x=0;
                    *attaque=TRUE;
                }else 
                {
                    atimg->y = position_anim;
                    atimg->x+=TAILLE_SPRITE;
                }
                break;

        case 5: //chevalier lance
        case 18: //l'ogre
            longueur_anim = TAILLE_SPRITE * 7;
            if ( owner == OWNER_1 ) position_anim = TAILLE_SPRITE * 7;
            else position_anim = TAILLE_SPRITE * 5;

            if(atimg->x == longueur_anim){
                    atimg->x=0;
                    *attaque=TRUE;
            }else 
            {
                    atimg->y = position_anim;
                    atimg->x+=TAILLE_SPRITE;
            }
            break;

        case 2: //gorille
            longueur_anim = TAILLE_SPRITE * 7;
            if ( owner == OWNER_1 ) position_anim = TAILLE_SPRITE * 7;
            else position_anim = TAILLE_SPRITE * 5;

            if(atimg->x == longueur_anim){
                    atimg->x=0;
                    *attaque=TRUE;
            }else 
            {
                    atimg->y = position_anim;
                    atimg->x+=TAILLE_SPRITE;
            }
            break;
    }
}

/**
 * \fn booleen_t animation_mort(SDL_Rect * atimg, character_t * c)
 * \brief Gère l'animation de la mort du personnage.
 *
 * Cette fonction gère l'animation de la mort du personnage en ajustant l'image affichée
 * pour simuler le processus de la mort.
 *
 * \param atimg Pointeur vers la structure SDL_Rect représentant la position de l'image du personnage en train de mourir.
 * \param c Pointeur vers la structure character_t représentant le personnage.
 * \return Valeur booléenne indiquant si l'animation de la mort est terminée (TRUE) ou non (FALSE).
 */
booleen_t animation_mort(SDL_Rect * atimg, character_t * c)
{

    if(atimg->x == TAILLE_SPRITE * 5){
        atimg->x=0;
        return TRUE;
    }else 
    {
        atimg->y = TAILLE_SPRITE * 20;
        atimg->x += TAILLE_SPRITE;
        return FALSE;
    }
}