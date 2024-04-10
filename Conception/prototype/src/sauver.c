#include "../lib/sauver.h"

sauvegardes_t * init_save(){
    sauvegardes_t * new = malloc(sizeof(sauvegardes_t));
    if(new == NULL)
        return NULL;
    FILE * f;
    f=fopen("../sauvegarde/save.txt","r");
    if(f!=NULL){
        new->nb=0;
        for(int i=0;i<MAX_SAVE;i++){
            new->tab[i]=NULL;
        }
    }
    

}

booleen_t save_possible(){
    FILE * f;
    int i;
    char nom_save[MAX_STR]="save_";
    for(i=0;i<MAX_SAVE;i++){
        strcat(nom_save,)
        f=fopen(nom_save,)
    }
}

booleent_t sauver_online(ordi_t * o, player_t * p, sauvegardes_t ** save){
    (*save)->nb
}