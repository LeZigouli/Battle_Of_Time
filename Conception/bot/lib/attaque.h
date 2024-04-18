#ifndef _ATTAQUE_H_
#define _ATTAQUE_H_

#include "ordinateur.h"

void resize_dep(SDL_Rect * atimg,SDL_Rect * position, character_t * c);
void resize_att(SDL_Rect * atimg,SDL_Rect * position, character_t * c);
void ataquage(SDL_Rect * atimg,SDL_Rect * position, character_t * c, int * attaque, unsigned long * fin, unsigned long * debut);

#endif