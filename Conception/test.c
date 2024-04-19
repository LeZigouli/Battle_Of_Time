#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


//Prehistoire Antiquité MoyenAge Moderne Futuriste

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

#define NB_RESOLUTIONS 6
#define TAILLE_SPRITE 64
#define TAILLE_ATTAQUE TAILLE_SPRITE*3


int largeur[NB_RESOLUTIONS] = {1920,640,1280,1366,1600,1920};
int hauteur[NB_RESOLUTIONS] = {1000,480,720,768,900,1080};
char tab_resolution[NB_RESOLUTIONS][10] = {"1920x1000","640x480","1280x720","1366x768","1600x900","1920x1080"};
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

    gFont = TTF_OpenFont("Pixel Sans Serif.ttf", 28);
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



int main(){
    if(!initSDL()){
        printf("Erreur initialisation SDL\n");
        exit(1);
    }
    Uint32 lastAction = 0; //derniere action

    const Uint8* state = SDL_GetKeyboardState(NULL);

    int quit = 0;
    SDL_Event event;



    int resize = 1; //entier qui sert a définir si le sprite a été redimensionné (car les animations sont de taille différentes)
    SDL_Rect playerImg[20] ={
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},

        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {0 , 0, 48, 48},

        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},

        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},

        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1},
        {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1}
    };    //position sur le png avec tous les sprite

    SDL_Rect playerPosition[20] = {
        {0, 0, 128, 128},
        {0, 100, 128, 128},
        {0, 200, 128, 128},
        {0, 300, 128, 128},

        {0, 400, 128, 128},
        {0, 500, 128, 128},
        {0, 600, 128, 128},
        {0, 700, 128, 128},

        {400, 0, 128, 128},
        {400, 100, 128, 128},
        {400, 200, 128, 128},
        {400, 300, 128, 128},

        {400, 400, 128, 128},
        {400, 500, 128, 128},
        {400, 600, 128, 128},
        {400, 700, 128, 128},

        {800, 0, 128, 128},
        {800, 100, 128, 128},
        {800, 200, 128, 128},
        {800, 300, 128, 128}


    }; // position et taille du sprite sur l'écran

    Uint32 lastMovement = 0; //dernier mouvement du sprite

    SDL_Texture* image[20] = {
        IMG_LoadTexture(gRenderer,"sprite/Préhistoire/marksman.png"),
        IMG_LoadTexture(gRenderer,"sprite/Préhistoire/melee.png"),
        IMG_LoadTexture(gRenderer,"sprite/Préhistoire/specialist.png"),
        IMG_LoadTexture(gRenderer,"sprite/Préhistoire/tank.png"),

        IMG_LoadTexture(gRenderer,"sprite/Antiquité/marksman.png"),
        IMG_LoadTexture(gRenderer,"sprite/Antiquité/melee.png"),
        IMG_LoadTexture(gRenderer,"sprite/Antiquité/specialist.png"),
        IMG_LoadTexture(gRenderer,"sprite/Antiquité/tank.png"),

        IMG_LoadTexture(gRenderer,"sprite/Moyen age/marksman.png"),
        IMG_LoadTexture(gRenderer,"sprite/Moyen age/melee.png"),
        IMG_LoadTexture(gRenderer,"sprite/Moyen age/specialist.png"),
        IMG_LoadTexture(gRenderer,"sprite/Moyen age/tank.png"),

        IMG_LoadTexture(gRenderer,"sprite/Ere moderne/marksman.png"),
        IMG_LoadTexture(gRenderer,"sprite/Ere moderne/melee.png"),
        IMG_LoadTexture(gRenderer,"sprite/Ere moderne/specialist.png"),
        IMG_LoadTexture(gRenderer,"sprite/Ere moderne/tank.png"),

        IMG_LoadTexture(gRenderer,"sprite/Ere futuriste/marksman.png"),
        IMG_LoadTexture(gRenderer,"sprite/Ere futuriste/melee.png"),
        IMG_LoadTexture(gRenderer,"sprite/Ere futuriste/specialist.png"),
        IMG_LoadTexture(gRenderer,"sprite/Ere futuriste/tank.png")
    }; 

    //texture du sprite qui sera copier dans le rendu pour l'affichage
    //on charge l'image dans une texture SDL

    int attaque = 0; //est-ce que le sprite attaque ?
    int nb_attaque = 1; //quelle animation d'attaque ? 


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
                    case SDLK_a: //on appuie sur A pour attaquer/ne plus attaquer 
                        attaque = !attaque;
                        break;
                }
                /*if (currentTime - lastAction >= 10) { // Temps pour une nouvelle action de 10 ms
                    if(state[SDL_SCANCODE_W]){ //sdl reconnais le clavier en anglais donc c'est Z qu'il faut appuyer
                        nb_attaque=1;//attaque 1
                        printf("atk : %d\n",nb_attaque);
                    }
                    if(state[SDL_SCANCODE_E]){
                        nb_attaque=2;//attaque 2
                        printf("atk : %d\n",nb_attaque);
                    }
                    if(state[SDL_SCANCODE_R]){
                        nb_attaque=3;//attaque 3
                        printf("atk : %d\n",nb_attaque);
                    }
                }
                */  
            }
        }


        if(attaque == 0){
            if(resize == 0){
                //si le perso n'attaque plus on le remet a sa taille d'origine (car taille des sprite lors des animations différentes)
                //playerPosition pour régler la taille, playerImg pour régler l'animation
            
                
                playerImg[0].y = TAILLE_SPRITE*11;

                playerImg[1].h = TAILLE_SPRITE;
                playerImg[1].w = TAILLE_SPRITE;
                playerImg[1].x = 128;
                playerImg[1].y = TAILLE_SPRITE*11;
                playerPosition[1].h=128;
                playerPosition[1].w=128;
                playerPosition[1].x+=128;
                playerPosition[1].y+=128;

                playerImg[2].x = 0;
                playerImg[2].y = TAILLE_SPRITE*11;

                playerImg[3].x = 0;
                playerImg[3].y = TAILLE_SPRITE*11;
                
                playerImg[4].x = 0;
                playerImg[4].y = TAILLE_SPRITE*11;

                playerImg[5].h = TAILLE_SPRITE;
                playerImg[5].w = TAILLE_SPRITE;
                playerImg[5].x = 128;
                playerImg[5].y = TAILLE_SPRITE*11;
                playerPosition[5].h=128;
                playerPosition[5].w=128;
                playerPosition[5].x+=128;
                playerPosition[5].y+=128;
                
                playerImg[6].h = TAILLE_SPRITE;
                playerImg[6].w = TAILLE_SPRITE;
                playerImg[6].x = 128;
                playerImg[6].y = TAILLE_SPRITE*11;
                playerPosition[6].h=128;
                playerPosition[6].w=128;
                playerPosition[6].x+=128;
                playerPosition[6].y+=128;

                playerImg[7].x = 0;

                playerImg[8].x = 0;
                playerImg[8].y = TAILLE_SPRITE*11;

                playerImg[9].h = TAILLE_SPRITE;
                playerImg[9].w = TAILLE_SPRITE;
                playerImg[9].x = 128;
                playerImg[9].y = TAILLE_SPRITE*11;
                playerPosition[9].h=128;
                playerPosition[9].w=128;
                playerPosition[9].x+=128;
                playerPosition[9].y+=128;

                playerImg[10].h = TAILLE_SPRITE;
                playerImg[10].w = TAILLE_SPRITE;
                playerImg[10].x = 128;
                playerImg[10].y = TAILLE_SPRITE*11;
                playerPosition[10].h=128;
                playerPosition[10].w=128;
                playerPosition[10].x+=128;
                playerPosition[10].y+=128;

                playerImg[11].h = TAILLE_SPRITE;
                playerImg[11].w = TAILLE_SPRITE;
                playerImg[11].x = 128;
                playerImg[11].y = TAILLE_SPRITE*11;
                playerPosition[11].h=128;
                playerPosition[11].w=128;
                playerPosition[11].x+=TAILLE_SPRITE;
                playerPosition[11].y+=TAILLE_SPRITE;

                playerImg[12].x = 0;
                playerImg[12].y = TAILLE_SPRITE*11;

                playerImg[13].h = TAILLE_SPRITE;
                playerImg[13].w = TAILLE_SPRITE;
                playerImg[13].x = 128;
                playerImg[13].y = TAILLE_SPRITE*11;
                playerPosition[13].h=128;
                playerPosition[13].w=128;
                playerPosition[13].x+=TAILLE_SPRITE;
                playerPosition[13].y+=TAILLE_SPRITE;

                playerImg[14].h = TAILLE_SPRITE;
                playerImg[14].w = TAILLE_SPRITE;
                playerImg[14].x = 128;
                playerImg[14].y = TAILLE_SPRITE*11;
                playerPosition[14].h=128;
                playerPosition[14].w=128;
                playerPosition[14].x+=TAILLE_SPRITE*2;
                playerPosition[14].y+=TAILLE_SPRITE*2;

                playerImg[15].x = 0;
                playerImg[15].y = TAILLE_SPRITE*11;

                playerImg[16].h = TAILLE_SPRITE;
                playerImg[16].w = TAILLE_SPRITE;
                playerImg[16].x = 128;
                playerImg[16].y = TAILLE_SPRITE*11;
                playerPosition[16].h=128;
                playerPosition[16].w=128;
                playerPosition[16].x+=TAILLE_SPRITE*2;
                playerPosition[16].y+=TAILLE_SPRITE*2;

                playerImg[17].h = TAILLE_SPRITE;
                playerImg[17].w = TAILLE_SPRITE;
                playerImg[17].x = 128;
                playerImg[17].y = TAILLE_SPRITE*11;
                playerPosition[17].h=128;
                playerPosition[17].w=128;
                playerPosition[17].x+=TAILLE_SPRITE*2;
                playerPosition[17].y+=TAILLE_SPRITE*2;

                playerImg[18].x = 0;
                playerImg[18].y = TAILLE_SPRITE*11;

                playerImg[19].h = TAILLE_SPRITE;
                playerImg[19].w = TAILLE_SPRITE;
                playerImg[19].x = 128;
                playerImg[19].y = TAILLE_SPRITE*11;
                playerPosition[19].h=128;
                playerPosition[19].w=128;
                playerPosition[19].x+=TAILLE_SPRITE*2;
                playerPosition[19].y+=TAILLE_SPRITE*2;


                resize=1;
            }
        }

        if(currentTime - lastMovement>=100 && attaque == 0){ //le sprite va avancer tout les 100 ms
            int i = 0;
            for(i;i<20;i++){
                if(i!=7){
                    if(playerImg[i].x==TAILLE_SPRITE*8) playerImg[i].x=TAILLE_SPRITE; 
                    else {
                        playerImg[i].x+=TAILLE_SPRITE;
                    }
                }
                playerPosition[i].x+= 10;//avance de 10pixel
            }
            if(playerImg[7].x == 48*7) playerImg[7].x = 0;
            else{
                playerImg[7].x+=48;
            }
            
            lastMovement= SDL_GetTicks();
        }
        if(attaque){
            if(currentTime - lastMovement>=150){//le sprite va effectuer les différentes animations toutes les 150 ms
                if(resize){ //il faut resize car les png d'animations sont différents
                //les dimensions d'un sprite d'animation d'attaque est 3x plus grand d'ou le 128*3 pour height et width
                    playerImg[0].x = 0;
                    playerImg[0].y = TAILLE_SPRITE*19;

                    playerPosition[1].h=128*3;
                    playerPosition[1].w=128*3;
                    playerPosition[1].x-=128;
                    playerPosition[1].y-=128;
                    playerImg[1].x=0;  

                    playerImg[2].x = 0;
                    playerImg[2].y = TAILLE_SPRITE*19;

                    playerImg[3].x = 0;
                    playerImg[3].y = TAILLE_SPRITE*7;
                    
                    playerImg[4].x = 0;
                    playerImg[4].y = TAILLE_SPRITE*7;

                    playerPosition[5].h=128*3;
                    playerPosition[5].w=128*3;
                    playerPosition[5].x-=128;
                    playerPosition[5].y-=128;
                    playerImg[5].x=0;

                    playerPosition[6].h=128*3;
                    playerPosition[6].w=128*3;
                    playerPosition[6].x-=128;
                    playerPosition[6].y-=128;
                    playerImg[6].x=0;

                    
                    playerImg[7].x = 48 * 19;

                    playerImg[8].x = 0;
                    playerImg[8].y = TAILLE_SPRITE*19;

                    playerPosition[9].h=128*3;
                    playerPosition[9].w=128*3;
                    playerPosition[9].x-=128;
                    playerPosition[9].y-=128;
                    playerImg[9].x=0;

                    playerPosition[10].h=128*3;
                    playerPosition[10].w=128*3;
                    playerPosition[10].x-=128;
                    playerPosition[10].y-=128;
                    playerImg[10].x=0;

                    playerPosition[11].h=128*2;
                    playerPosition[11].w=128*2;
                    playerPosition[11].x-=TAILLE_SPRITE;
                    playerPosition[11].y-=TAILLE_SPRITE;
                    playerImg[11].x=TAILLE_SPRITE*2;

                    playerImg[12].x = 0;
                    playerImg[12].y = TAILLE_SPRITE*15;

                    playerPosition[13].h=128*2;
                    playerPosition[13].w=128*2;
                    playerPosition[13].x-=TAILLE_SPRITE;
                    playerPosition[13].y-=TAILLE_SPRITE;
                    playerImg[13].x=TAILLE_SPRITE*2;

                    playerPosition[14].h=128*3;
                    playerPosition[14].w=128*3;
                    playerPosition[14].x-=128;
                    playerPosition[14].y-=128;
                    playerImg[14].x=0;

                    playerImg[15].x = 0;
                    playerImg[15].y = TAILLE_SPRITE*15;

                    playerPosition[16].h=128*3;
                    playerPosition[16].w=128*3;
                    playerPosition[16].x-=128;
                    playerPosition[16].y-=128;
                    playerImg[16].x=0;

                    playerPosition[17].h=128*3;
                    playerPosition[17].w=128*3;
                    playerPosition[17].x-=128;
                    playerPosition[17].y-=128;
                    playerImg[17].x=0;

                    playerImg[18].x = 0;
                    playerImg[18].y = TAILLE_SPRITE*15;

                    playerPosition[19].h=128*3;
                    playerPosition[19].w=128*3;
                    playerPosition[19].x-=128;
                    playerPosition[19].y-=128;
                    playerImg[19].x=0;

                    resize=0;
                }

                if(playerImg[0].x == TAILLE_SPRITE*7) playerImg[0].x=0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[0].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[1].x == TAILLE_SPRITE*3*5) playerImg[1].x=0; //si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[1].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[2].x == TAILLE_SPRITE*12) playerImg[2].x=0; //si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[2].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[3].x == TAILLE_SPRITE*7) playerImg[3].x=0; //si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[3].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[4].x == TAILLE_SPRITE*7) playerImg[4].x=0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[4].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[5].x == TAILLE_SPRITE*3*5) playerImg[5].x=0; //si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[5].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[6].x == TAILLE_SPRITE*3*5) playerImg[6].x=0; //si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[6].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[7].x == 48 * 28) playerImg[7].x= 48 * 20;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[7].x+=48;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[8].x == TAILLE_SPRITE*12) playerImg[8].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[8].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[9].x == TAILLE_SPRITE*3*5) playerImg[9].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[9].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[10].x == TAILLE_SPRITE*3*7) playerImg[10].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[10].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[11].x == TAILLE_SPRITE*2*5) playerImg[11].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[11].x+=TAILLE_SPRITE*2;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[12].x == TAILLE_SPRITE*5) playerImg[12].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[12].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[13].x == TAILLE_SPRITE*2*5) playerImg[13].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[13].x+=TAILLE_SPRITE*2;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[14].x == TAILLE_SPRITE*3*7) playerImg[14].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[14].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[15].x == TAILLE_SPRITE*5) playerImg[15].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[15].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[16].x == TAILLE_SPRITE*3*5) playerImg[16].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[16].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[17].x == TAILLE_SPRITE*3*5) playerImg[17].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[17].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[18].x == TAILLE_SPRITE*5) playerImg[18].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[18].x+=TAILLE_SPRITE;//sinon on passe a l'image d'animation suivante
                }
                if(playerImg[19].x == TAILLE_SPRITE*3*5) playerImg[19].x= 0;//si on arrive au bout de l'animation alors on retourne a la premiere image de l'animation pour faire une animation continue
                else{
                    playerImg[19].x+=TAILLE_SPRITE*3;//sinon on passe a l'image d'animation suivante
                }

                //éventuellement faire un random pour que les animations d'attaques soient diversifiées
                /* il y a plusieurs animations d'attaque pour certains perso, pas implémentés encore.
                if(nb_attaque == 1)playerImg[1].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);//attaque 1
                else if (nb_attaque == 2) playerImg[1].y = (21*TAILLE_SPRITE)+7*(TAILLE_ATTAQUE);//attaque 2
                else if(nb_attaque == 3) playerImg[1].y = (21*TAILLE_SPRITE)+11*(TAILLE_ATTAQUE);//attaque 3
                */

                playerImg[1].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[1].h = TAILLE_SPRITE*3;
                playerImg[1].w = TAILLE_SPRITE*3;

                playerImg[5].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[5].h = TAILLE_SPRITE*3;
                playerImg[5].w = TAILLE_SPRITE*3;

                playerImg[6].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[6].h = TAILLE_SPRITE*3;
                playerImg[6].w = TAILLE_SPRITE*3;

                playerImg[9].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[9].h = TAILLE_SPRITE*3;
                playerImg[9].w = TAILLE_SPRITE*3;

                playerImg[10].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[10].h = TAILLE_SPRITE*3;
                playerImg[10].w = TAILLE_SPRITE*3;

                playerImg[11].y = (21*TAILLE_SPRITE)+2*(TAILLE_ATTAQUE);
                playerImg[11].h = TAILLE_SPRITE*2;
                playerImg[11].w = TAILLE_SPRITE*2;

                playerImg[13].y = (20*TAILLE_SPRITE)+5*(TAILLE_ATTAQUE);
                playerImg[13].h = TAILLE_SPRITE*2;
                playerImg[13].w = TAILLE_SPRITE*2;

                playerImg[14].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[14].h = TAILLE_SPRITE*3;
                playerImg[14].w = TAILLE_SPRITE*3;

                playerImg[16].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[16].h = TAILLE_SPRITE*3;
                playerImg[16].w = TAILLE_SPRITE*3;

                playerImg[17].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[17].h = TAILLE_SPRITE*3;
                playerImg[17].w = TAILLE_SPRITE*3;

                playerImg[19].y = (21*TAILLE_SPRITE)+3*(TAILLE_ATTAQUE);
                playerImg[19].h = TAILLE_SPRITE*3;
                playerImg[19].w = TAILLE_SPRITE*3;

                lastMovement= SDL_GetTicks();
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);//couleur du fond
        SDL_RenderClear(gRenderer);//effacer l'ancien rendu

        for (int i = 0; i < 20; i++) {
            SDL_RenderCopy(gRenderer, image[i], &playerImg[i], &playerPosition[i]);
        }
        SDL_RenderPresent(gRenderer);//dessiner le rendu actuel
    }

    for (int i = 0; i < 20; i++) {
        SDL_DestroyTexture(image[i]);
    }
    closeSDL();
    return 0;
}
