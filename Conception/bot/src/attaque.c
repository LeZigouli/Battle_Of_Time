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
            break;
        
        case 0:
        case 4:
        case 7:
        case 8:
        case 11:
            position->h=128;
            position->w=128;
            position->x+=TAILLE_SPRITE;
            position->y+=TAILLE_SPRITE;
            break;
        
        case 6:
            atimg->x=0;
            break;
        

        case 10:
        case 12:/*
            atimg->h = TAILLE_SPRITE;
            atimg->w = TAILLE_SPRITE;
            atimg->x = 128;
            atimg->y = TAILLE_SPRITE*11;*/
            position->h=128;
            position->w=128;
            position->x+=TAILLE_SPRITE;
            position->y+=TAILLE_SPRITE;
            break;

        case 15:
        case 16:
        case 17:
        case 18:/*
            atimg->h = TAILLE_SPRITE;
            atimg->w = TAILLE_SPRITE;
            atimg->x = 128;
            atimg->y = TAILLE_SPRITE*11;*/
            position->h=128;
            position->w=128;
            position->x+=TAILLE_SPRITE*2;
            position->y+=TAILLE_SPRITE*2;
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
        case 11:
        case 15:
        case 16:
        case 17:
        case 18:
            position->h=128*3;
            position->w=128*3;
            position->x-=128;
            position->y-=128;
            atimg->x=0;
            atimg->y=TAILLE_ATTAQUE*10;
            atimg->w=TAILLE_ATTAQUE;
            atimg->h=TAILLE_ATTAQUE;
            break;

        case 2:
        case 5:
            atimg->x = 0;
            atimg->y = TAILLE_SPRITE*7;
            break;
        
        case 6:
            atimg->x = 48 * 19;
            break;
        
        case 10:
        case 12:
            position->h=128*2;
            position->w=128*2;
            position->x-=TAILLE_SPRITE;
            position->y-=TAILLE_SPRITE;
            atimg->x=TAILLE_SPRITE*2;
            break;
        
        case 13:
        case 14:
        case 19:
            atimg->x = 0;
            atimg->y = TAILLE_SPRITE*15;
            break;

    }
}

void ataquage(SDL_Rect * atimg, character_t * c, int * attaque, unsigned long * fin, unsigned long * debut){
    int ind = c->classe+c->age*NB_CHARACTER;
    switch(ind){    

        case 0:
        case 1:
        case 5:
        case 3:
        case 9:
        case 4:
        case 7:
        case 8:
        case 16:
        case 17:
        case 18:
            if(atimg->x == TAILLE_SPRITE*11){
                atimg->x=0;
                *attaque=TRUE;
            }else 
            {
                atimg->y = TAILLE_SPRITE*19;
                atimg->x+=TAILLE_SPRITE;
            }
            break;

        /* le cheval */
        case 6:
            if(atimg->x == 48*20){
                atimg->x=0;
                *attaque=TRUE;
            }else 
            {
                atimg->y = 48;
                atimg->x+=48;
            }
            break;
        
        case 11:
        case 15:
            if(atimg->x == TAILLE_SPRITE*3*7){
                atimg->x=0;
                *attaque=TRUE;
            }else 
                atimg->x+=TAILLE_SPRITE;
            break;
        
        case 10:
        case 12:
            if(atimg->x == TAILLE_SPRITE*12){
                atimg->x=0;
                *attaque=TRUE;
            }else 
            {
                atimg->y = TAILLE_SPRITE * 19;
                atimg->x+=TAILLE_SPRITE;
            }
            break;
        
        case 13:
        case 14:
        case 19:
                if(atimg->x == TAILLE_SPRITE*7){
                    atimg->x=0;
                    *attaque=TRUE;
                }else 
                {
                    atimg->y = TAILLE_SPRITE * 7;
                    atimg->x+=TAILLE_SPRITE;
                }
                break;


        /* le gorille */
        case 2 :
            if(atimg->x == TAILLE_SPRITE*5){
                atimg->x=0;
                *attaque=TRUE;
            }else 
            {
                if ( *debut == DELAI_INITIAL ) *debut = time(NULL);
                *fin = time(NULL);
                if ( *fin - *debut > 0 )
                {
                    atimg->y = TAILLE_SPRITE * 15;
                    atimg->x += TAILLE_SPRITE;
                }
                else
                {
                    atimg->y = TAILLE_SPRITE * 3;
                    atimg->x = TAILLE_SPRITE;
                }
            }
            break;

    }
}