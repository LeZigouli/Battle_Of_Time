#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_AGE 5
#define NB_CHARACTER 4

enum t_age { Préhistoire=0, Antiquité, Moyen_Age, Ere_Moderne, Ere_Futuriste };
enum t_monstre_Préhistoire { Monstre1_Prehistoire=0, Monstre2_Prehistoire, Monstre3_Prehistoire, Monstre4_Prehistoire };
enum t_monstre_Antiquité { Monstre1_Antiquite=0, Monstre2_Antiquite, Monstre3_Antiquite, Monstre4_Antiquite };
enum t_monstre_Moyen_Age { Monstre1_Moyen_Age=0, Monstre2_Moyen_Age, Monstre3_Moyen_Age, Monstre4_Moyen_Age };
enum t_monstre_Ere_Moderne { Monstre1_Ere_Moderne=0, Monstre2_Ere_Moderne, Monstre3_Ere_Moderne, Monstre4_Ere_Moderne };
enum t_monstre_Ere_futuriste { Monstre1_Ere_Futuriste=0, Monstre2_Ere_Futuriste, Monstre3_Ere_Futuriste, Monstre4_Ere_Futuriste };

#define MAX_STR 20
#define MAX_POSSESSED 10
#define EASY 1
#define MEDIUM 2
#define HARD 3
#define MAX_DESCRIPTION 100