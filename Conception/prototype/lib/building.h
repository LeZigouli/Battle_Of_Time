#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "common.h"

typedef struct building_s{

	int pv;
	int owner;
	int dammage;
	int max_pv;
	int XP_cost;
	int level;

}building_t;

booleen_t init_building(building_t ** building, int owner);
booleen_t upgrade_building(building_t ** building,int * xp);
booleen_t afficher_building(building_t * building);

#endif