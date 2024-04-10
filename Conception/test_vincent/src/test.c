#include "../lib/help.h"
#include "../lib/ordinateur.h"
#include "../lib/save.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>

int main(){
    int test_jeux=1,test_fct_player=0,test_fct_ordi=0; 
    /* initialise tous les characters */
    character_t * tab_character = initcharacter();
    if(test_fct_player){
        /* initialisation d'un joueur */
        player_t * main_player = initplayer(EASY,OWNER_1);
        player_t * main_player2 = initplayer(EASY,OWNER_2);


        afficher_player(main_player);
        afficher_player(main_player2);


        
        /* achat d'un character par le joueur */
        if ( buy_character(&main_player,tab_character,combattant_caillou) )
        {
            
            printf("Achat reussi !\n");
        }
        envoie_char(&main_player);
        printf("delai :%d \n",main_player->delai);
        sleep(main_player->delai);
        envoie_char(&main_player);
        if ( buy_character(&main_player,tab_character,combattant_massue) )
        {
            printf("Achat reussi !\n");
        }
        
        buy_character(&main_player2,tab_character,gorille);
        buy_character(&main_player2,tab_character,combattant_massue);

        

        if ( delete_character(&main_player->characters) && delete_character(&main_player2->characters) )
        {
            printf("Suppression reussi !\n\n");
        }

        afficher_player(main_player);
        afficher_player(main_player2);

        upgrade_building(&main_player->building,&main_player->xp);
        
        afficher_player(main_player);
        










        if ( buy_character(&main_player2,tab_character,gorille) )
        {
            printf("Achat reussi !\n");
        }

        if ( buy_character(&main_player2,tab_character,combattant_massue) )
        {
            printf("Achat reussi !\n");
        }
        
        afficher_characters(main_player2->characters);

        if ( delete_character(&main_player->characters) && delete_character(&main_player2->characters) )
        {
            printf("Suppression reussi !\n\n");
        }

        afficher_player(main_player2);

        upgrade_building(&main_player2->building,&main_player2->xp);
        
        afficher_player(main_player2);


        /* on detruit la mémoire */
        destroy_player(&main_player);
        destroy_player(&main_player2);


    }
    if(test_fct_ordi){
        printf("<------------------------- TEST FONCTION ORDINATEUR ------------------------->\n");
        
        ordi_t * ordin = init_ordi(EASY);
        player_t * play = initplayer(EASY,OWNER_1);
        
        
        afficher_ordi(ordin);
        buy_character(&play,tab_character,gorille);
        sleep(play->delai);
        envoie_char(&play);
        afficher_player(play);
        delete_character(&ordin->characters);

        
        for(int i=0;i<12;i++){
            //character_attack_character(&ordin->characters->tab[0],&play->characters->tab[0]);
            envoie_char_ordi(ordin,tab_character);
            
        }
        afficher_ordi(ordin);
        ulti(&ordin->characters);
        afficher_ordi(ordin);
        give_ressources(play,ordin);
        delete_character(&ordin->characters);
        afficher_ordi(ordin);
        give_ressources(play,ordin);
        delete_character(&ordin->characters);
        destroy_player(&play);
        detr_ordi(&ordin);
    }
    if(test_jeux){
    printf("<------------------------- TEST JEU SANS GRAPHISME ------------------------->\n");
        ordi_t * or = init_ordi(HARD);
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
                        printf("QUITTER\n");
                        break;

                    case SDLK_a:
                        afficher_ordi(or);
                        afficher_player(player);
                        break;
                    
                    case SDLK_KP_1:
                        buy_character(&player,tab_character,combattant_dinosaure);
                        break;
                    
                    case SDLK_u:
                        ulti(&or->characters);
                    
                    default:
                        break;
                    }
                    if(player!=NULL)
                        if(player->characters !=NULL)
                            if(player->characters->nb!=0){
                                character_attack_character(&or->characters->tab[0],&player->characters->tab[0]);
                            }
                }
            }
            
            envoie_char(&player);
            jeu_ordi(or,player,tab_character);
            delete_character(&or->characters);
            delete_character(&player->characters);
            // Nettoyage et mise à jour du renderer
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    
        // Libération des ressources
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        save(or,player);

        detr_ordi(&or);
        destroy_player(&player);

        load(&or,&player);
        afficher_ordi(or);
        afficher_player(player);
        detr_ordi(&or);
        destroy_player(&player);
    }
    
    destroy_tab_character(&tab_character);

    return TRUE;
}