/**
 * \file attaque.h
 * \brief Contient les élements utilisés par attaque.c
 * \author Proudy Vincent
 * \date 02 avril 2024
 * \version 1.0
 * 
*/
#ifndef _ATTAQUE_H_
#define _ATTAQUE_H_

#include "ordinateur.h"

void resize_dep(SDL_Rect * atimg,SDL_Rect * position, character_t * c);
void resize_att(SDL_Rect * atimg,SDL_Rect * position, character_t * c);
void ataquage(SDL_Rect * atimg, character_t * c, int * attaque, int owner);
booleen_t animation_mort(SDL_Rect * atimg, character_t * c);
#endif