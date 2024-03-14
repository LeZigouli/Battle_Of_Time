#include "../lib/player.h"
#include "../lib/common.h"
#include "../lib/character.h"
#include "../lib/help.h"
#include "../lib/building.h"
#include "../lib/ordinateur.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

int main(){

    /* initialisation d'un joueur */
    player_t * main_player = initplayer(EASY,OWNER_1);
    player_t * main_player2 = initplayer(EASY,OWNER_2);


    afficher_player(main_player);
    afficher_player(main_player2);

    //afficher_building(main_player);
    //afficher_building(main_player2);


    /* initialise tous les characters */
    character_t * tab_character = initcharacter();

    /* achat d'un character par le joueur */
    if ( buy_character(&main_player,tab_character,Prehistoire,Prehistoire,gorille) )
    {
        //printf("Achat reussi !\n");
    }

    if ( buy_character(&main_player,tab_character,Prehistoire,Prehistoire,combattant_massue) )
    {
        //printf("Achat reussi !\n");
    }
    
    buy_character(&main_player2,tab_character,Prehistoire,Prehistoire,gorille);
    buy_character(&main_player2,tab_character,Prehistoire,Prehistoire,combattant_massue);

    //afficher_characters_player(main_player->characters);

    if ( delete_character(&main_player,&main_player2) )
    {
        //printf("Suppression reussi !\n\n");
    }

    //afficher_characters_player(main_player->characters);

    afficher_player(main_player);
    afficher_player(main_player2);

    //upgrade_building(&main_player);
    
    //afficher_building(main_player);

    










    if ( buy_character(&main_player2,tab_character,Prehistoire,Prehistoire,gorille) )
    {
        //printf("Achat reussi !\n");
    }

    if ( buy_character(&main_player2,tab_character,Prehistoire,Prehistoire,combattant_massue) )
    {
        //printf("Achat reussi !\n");
    }
    
    afficher_characters_player(main_player2->characters);

    if ( delete_character(&main_player,&main_player2) )
    {
        //printf("Suppression reussi !\n\n");
    }

    afficher_characters_player(main_player2->characters);

    afficher_player(main_player2);

    //upgrade_building(&main_player2);
    
    //afficher_building(main_player2);







    /* on detruit la mémoire */
    destroy_player(&main_player);
    destroy_player(&main_player2);
     

    printf("<------------------------- TEST FONCTION ORDINATEUR ------------------------->\n");
    
   //ordi_t * ordin =init_ordi(EASY);
    player_t *player = initplayer(EASY,OWNER_1);
    printf("okay\n");
    


    //detr_ordi(&ordin);
    destroy_player(&player);
    return TRUE;
}