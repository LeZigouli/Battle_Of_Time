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
    
    ordi_t * ordin = init_ordi(EASY);
    
    
    
    for(int i=0;i<12;i++){
        envoie_char(&ordin,tab_character);
        upgrade_building_or(&ordin);
    }
    afficher_ordi(ordin);
    
    
    detr_ordi(&ordin);

    printf("<------------------------- TEST JEU SANS GRAPHISME ------------------------->\n");

    ordin = init_ordi(HARD);
    player_t * player = initplayer(HARD,OWNER_1);

    // Déclaration des variables globales
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("Detection de touche", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Boucle principale
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if(event.type==SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    quit=1;
                    break;

                case SDLK_a:
                    afficher_ordi(ordin);
                    break;
                
                case SDLK_KP_1:
                    buy_character(&player,tab_character,Antiquite,1,0);
                
                default:
                    break;
                }
                if(player!=NULL)
                    if(player->characters !=NULL)
                        if(player->characters->nb!=0){
                        character_attack_character(&ordin->characters->tab[0],&player->characters->tab[0]);
                        }
            }
        }
        jeu_ordi(ordin,player,tab_character);
        // Nettoyage et mise à jour du renderer
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    detr_ordi(&ordin);
    destroy_player(&player);
    destroy_tab_character(&tab_character);

    return TRUE;
}