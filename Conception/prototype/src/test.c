#include "../lib/player.h"
#include "../lib/common.h"
#include "../lib/character.h"
#include "../lib/help.h"
#include "../lib/building.h"

int main(){

    /* initialisation d'un joueur */
    player_t * main_player = initplayer(EASY);
    afficher_player(main_player);
    afficher_building(main_player);


    /* initialise tous les characters */
    character_t * tab_character = initcharacter();

    /* achat d'un character par le joueur */
    if ( buy_character(&main_player,tab_character,Prehistoire,Prehistoire,gorille) )
    {
        printf("Achat reussi !\n");
    }

    if ( buy_character(&main_player,tab_character,Prehistoire,Prehistoire,combattant_massue) )
    {
        printf("Achat reussi !\n");
    }
    
    afficher_characters_player(main_player->characters);

    if ( delete_character(&main_player) )
    {
        printf("Suppression reussi !\n\n");
    }

    afficher_characters_player(main_player->characters);

    afficher_player(main_player);

    upgrade_building(&main_player);
    
    afficher_building(main_player);







    /* on detruit la mémoire */
    destroy_player(&main_player);
    destroy_tab_character(&tab_character);   

    return TRUE;
}