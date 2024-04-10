#ifndef _SAUVER_H_
#define _SAUVER_H_

#include "ordinateur.h"
#define MAX_SAVE 5

typedef struct sauver_s
{
    player_t * p;
    ordi_t * o;
}sauver_t;

typedef struct sauvegardes_s
{
    int nb;
    sauver_t * tab[MAX_SAVE];
}sauvegardes_t;



booleen_t save_possible();
booleent_t sauver_online(void * owner, booleen_t (*sauver)(void *));


#endif