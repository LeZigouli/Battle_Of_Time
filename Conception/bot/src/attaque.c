#include "../lib/attaque.h"

void resize_dep(SDL_Rect * atimg,SDL_Rect * position, character_t * c){
//si le perso n'attaque plus on le remet a sa taille d'origine (car taille des sprite lors des animations différentes)
//playerPosition pour régler la taille, playerImg pour régler l'animation
    int ind = c->classe+c->age*NB_CHARACTER;
    
    switch(ind){
        case 1:
        case 2:
        case 3:
        case 5:
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
        
        //le cheval
        case 6:
            atimg->x=TAILLE_CHEVAL * 19;
            atimg->y=0;
            break;
    }
}
void resize_att(SDL_Rect * atimg,SDL_Rect * position, character_t * c){
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
        
        case 6:
            atimg->x = TAILLE_CHEVAL * 19;
            atimg->y=0;
            break;
        
        case 13:
        case 14:
        case 19:
            atimg->x = 0;
            atimg->y = TAILLE_SPRITE*15;
            break;

    }
}

void ataquage(SDL_Rect * atimg, character_t * c, int * attaque, int owner){
    int ind = c->classe+c->age*NB_CHARACTER;

    int position_anim;
    int longueur_anim;

    switch(ind){    

        case 0:
        case 1:
        case 3:
        case 9:
        case 4:
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 17:
            longueur_anim = TAILLE_SPRITE*11;
            if ( owner == OWNER_1 ) position_anim = TAILLE_SPRITE*19;
            else position_anim = TAILLE_SPRITE*17;

            if(atimg->x == longueur_anim){
                atimg->x=0;
                *attaque=TRUE;
            }else 
            {
                atimg->y = position_anim;
                atimg->x+=TAILLE_SPRITE;
            }
            break;

        case 6: //cheval
            if(atimg->x == 48*20){
                atimg->x=0;
                *attaque=TRUE;
            }else 
            {
                atimg->y = 48;
                atimg->x+=48;
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
            longueur_anim = TAILLE_SPRITE * 6;
            if ( owner == OWNER_1 ) position_anim = TAILLE_SPRITE * 3;
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