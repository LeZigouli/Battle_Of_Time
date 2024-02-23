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
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool quit = false;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("SDL NPC Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    /**/
    int rng_envoi=-1;
    ordi_t * ordinateur = init_ordi(EASY);
    player_t * player = initplayer(EASY,OWNER_1);
    srand(time(NULL));
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event) != 0 && rng_envoi>0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_KP_1:
                        // Achat d'un charcter type 1
                        buy_character(&player,tab_character,Antiquite,0,1);
                        break;
                    case SDLK_KP_2:
                        // Achat d'un charcter type 2
                        buy_character(&player,tab_character,Antiquite,0,2);
                        break;
                    case SDLK_KP_3:
                        // Achat d'un charcter type 3
                        buy_character(&player,tab_character,Antiquite,0,3);
                        break;
                    case SDLK_KP_4:
                        // Achat d'un charcter type 4
                        buy_character(&player,tab_character,Antiquite,0,4);
                        break;
                    default:
                        break;
                }
            }
        }
        if(rng_envoi==-1)
            rng_envoi=rand()%(10000/EASY);
        if(!rng_envoi){
            envoie_char(&ordinateur,Antiquite,tab_character);
        }else{
            rng_envoi--;
        }
        if(player->characters->tab[0] && !ordinateur->characters->tab[0])
            character_attack_building(&ordinateur->building,&player->characters->tab[0]);
        else if(!player->characters->tab[0] && ordinateur->characters->tab[0])
            character_attack_building(&player->building,&ordinateur->characters->tab[0]);
        else{
            character_attack_character(&ordinateur->characters->tab[0],&player->characters->tab[0]);
            character_attack_character(&player->characters->tab[0],&ordinateur->characters->tab[0]);
        }
        give_ressources(&player,&ordinateur);
        delete_character(&player,NULL);

        afficher_player(player);
        afficher_ordi(ordinateur);
    }
    
    detr_ordi(&ordinateur);
    destroy_player(&player);
    destroy_tab_character(&tab_character);  

    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return TRUE;
}