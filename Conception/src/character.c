#include "common.h"

typedef struct{

	char name[MAX_STR];
	int time; 
	int gold; 
	int pv;
	int ratio_resources;
	int dammage;
	int owner; 
	char description[MAX_DESCRIPTION];
	int x;
	int y;
	int vector;

}t_character;