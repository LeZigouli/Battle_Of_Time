#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../lib/ordinateur.h"
#include "../lib/help.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

#define NB_RESOLUTIONS 6
#define TAILLE_SPRITE 64
#define TAILLE_ATTAQUE TAILLE_SPRITE*3


int largeur[NB_RESOLUTIONS] = {1800,640,1280,1366,1600,1920};
int hauteur[NB_RESOLUTIONS] = {600,480,720,768,900,1080};
char tab_resolution[NB_RESOLUTIONS][10] = {"1800x600","640x480","1280x720","1366x768","1600x900","1920x1080"};
int position = 0;

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    gWindow = SDL_CreateWindow("FENETRE SDL BASIQUE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largeur[0], hauteur[0], SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC );
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    gFont = TTF_OpenFont("ttf/Pixel Sans Serif.ttf", 28);
    if (gFont == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

void refresh_W_H() {
    int SCREEN_WIDTH,SCREEN_HEIGHT;
    SDL_GetWindowSize(gWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    printf("Résolution actualisée en : %dx%d \n", SCREEN_WIDTH, SCREEN_HEIGHT);
}

void pleinEcran() {
    SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    printf("\nPlein écran → ");
    refresh_W_H();
}

void fenetre() {
    SDL_SetWindowFullscreen(gWindow, 0);
    printf("\nFenêtré → ");
    refresh_W_H();
}

void closeSDL() {
    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;


    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    printf("\nJe quitte SDL\n");

}

void renderSquare(SDL_Rect squareRect) {
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(gRenderer, &squareRect);
}

void deplacement(){

}
void attaque(){

}


int main(){
    if(!initSDL()){
        printf("Erreur initialisation SDL\n");
        exit(1);
    }
    Uint32 startTime = SDL_GetTicks(); // temps debut
    Uint32 lastAction = 0; //derniere action

    const Uint8* state = SDL_GetKeyboardState(NULL);

    int quit = 0;
    SDL_Event event;


    int resize = 1;

    char * img_path = "../../sprite/Antiquité/legionnaire epee.png";

    SDL_Rect playerImg = {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1};   //position sur le png avec tous les sprite
    SDL_Rect playerPosition = {0, hauteur[position]-TAILLE_SPRITE*2-16, 128, 128}; // position et taille du sprite sur l'écran
    Uint32 lastMovement = 0; //dernier mouvement du sprite


    SDL_Rect img_carre = {TAILLE_SPRITE * 0 , TAILLE_SPRITE * 10 , TAILLE_SPRITE * 1 , TAILLE_SPRITE * 1};

    SDL_Texture* image;

    image = IMG_LoadTexture(gRenderer,img_path);

    SDL_Texture * Prehistoire_texture = IMG_LoadTexture(gRenderer,"../../Fond/Préhistoire.jpg");
    SDL_Texture * Antiquite_texture = IMG_LoadTexture(gRenderer,"../../Fond/Antiquité.jpg");
    SDL_Texture * Moyen_age_texture = IMG_LoadTexture(gRenderer,"../..Fond/Moyen-Âge_base.jpg");
    SDL_Texture * Ere_moderne_texture = IMG_LoadTexture(gRenderer,"../../Fond/Moderne_base.jpg");
    SDL_Texture * Ere_futuriste_texture = IMG_LoadTexture(gRenderer,"../..Fond/Futuriste_base.jpg");


    int attaque = 0;
    int nb_attaque = 1;

    character_t * tab_de_charactere = initcharacter();
    player_t * j1 = initplayer(EASY,OWNER_1);
    afficher_player(j1);
    buy_character(&j1,tab_de_charactere,legionnaire_epee);
    sleep(4);
    envoie_char(&j1);
    ordi_t * o = init_ordi(EASY);

    SDL_Rect Perso1 = {TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE};
    SDL_Rect Perso2 = {TAILLE_SPRITE*2+8,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE};
    SDL_Rect Perso3 = {TAILLE_SPRITE*3+16,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE};
    SDL_Rect Perso4 = {TAILLE_SPRITE*4+24,TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE};


    while (!quit) {
        Uint32 currentTime = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
                printf("\nFermeture de la fenêtre\n");
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_p:
                        if (SDL_GetWindowFlags(gWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                            fenetre();
                        } else {
                            pleinEcran();
                        }
                        break;
                    case SDLK_a:
                        attaque = !attaque;
                        break;
                }


                if(state[SDL_SCANCODE_W]){ //sdl reconnais le clavier en anglais donc c'est Z qu'il faut appuyer
                    nb_attaque=1;
                    printf("atk : %d\n",nb_attaque);
                }
                if(state[SDL_SCANCODE_E]){
                    nb_attaque=2;
                    printf("atk : %d\n",nb_attaque);
                }
                if(state[SDL_SCANCODE_R]){
                    nb_attaque=3;
                    printf("atk : %d\n",nb_attaque);

                }
            }

                
            
        }

        if(attaque == 0 && resize == 0){

                playerImg.h = TAILLE_SPRITE;
                playerImg.w = TAILLE_SPRITE;
                playerImg.x = 128;
                playerImg.y = TAILLE_SPRITE*11;

                playerPosition.h=128;
                playerPosition.w=128;
                playerPosition.x+=128;
                playerPosition.y+=128;

                resize=1;

        }

        if(currentTime - lastMovement>=100 && attaque == 0){ //le sprite va avancer tout les 100 ms
                    if(playerImg.x==TAILLE_SPRITE*8) playerImg.x=TAILLE_SPRITE; //si on arrive a la fin de l'animation on retourne a la premiere pour faire l'animation en continu
                    else {
                        playerImg.x+=TAILLE_SPRITE;//on passe a l'image suivante pour l'animation
                    }
                    //playerPosition.x+= 10;//on avance de 10 pixel 
                    deplacement_droit(&j1->characters->tab[0]);

                    lastMovement= SDL_GetTicks();
        }
        if(attaque){

            if(currentTime - lastMovement>=150){//le sprite va effectuer les différentes animations toutes les 150 ms

                if(resize){ //il faut resize car les png d'animations sont différents
                    playerPosition.h*=3;
                    playerPosition.w*=3;
                    playerPosition.x-=128;
                    playerPosition.y-=128;
                    playerImg.x=0;
                    resize=0;
                }

                if(playerImg.x == TAILLE_SPRITE*3*5) playerImg.x=0;
                else{
                    playerImg.x+=TAILLE_SPRITE*3;
                }
                
                //éventuellement faire un random pour que les animations d'attaques soient diversifiées
                
                if(nb_attaque == 1) playerImg.y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                else if (nb_attaque == 2) playerImg.y = (21*TAILLE_SPRITE)+7*(TAILLE_ATTAQUE);
                else if(nb_attaque == 3) playerImg.y = (21*TAILLE_SPRITE)+11*(TAILLE_ATTAQUE);
                playerImg.h = TAILLE_SPRITE*3;
                playerImg.w = TAILLE_SPRITE*3;
                lastMovement= SDL_GetTicks();

            }
        }

        SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);//couleur du fond
        SDL_RenderClear(gRenderer);//effacer l'ancien rendu
        SDL_RenderCopy(gRenderer,Prehistoire,NULL,NULL);//le fond 
        SDL_RenderCopy(gRenderer,image,&playerImg,&playerPosition);

        renderSquare(Perso1);
        SDL_RenderCopy(gRenderer,image,&img_carre,&Perso1);
        renderSquare(Perso2);
        renderSquare(Perso3);
        renderSquare(Perso4);

        SDL_RenderPresent(gRenderer);//dessiner le rendu actuel
    }
    SDL_DestroyTexture(image);
    closeSDL();
    return 0;
}
