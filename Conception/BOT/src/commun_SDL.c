#include "lib/commun_SDL.h"

/*Fonction d'initialisation*/
int initialisation()
{
    /*Initialiser SDL*/
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL : %s", SDL_GetError());
        return 1;
    }
    /*Initialiser SDL_image*/
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL_image : %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }
    /*Initialiser SDL_ttf*/
    if (TTF_Init() < 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL_ttf : %s", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    /*Initialisation SDL_Mixer*/
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
        SDL_Log("Erreur: %s\n", Mix_GetError());
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    } 
    /*Initialisation variables pour la gestion du volume*/
    volumeBar = malloc(sizeof(SDL_Rect));
    volumeCursor = malloc(sizeof(SDL_Rect));
    volume = MIX_MAX_VOLUME / 2;
    estLache = SDL_FALSE;
    return 0; 

 
}

/*Chargement d'une police*/
TTF_Font* chargementPolice(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* textureFond, char* path, int taille)
{
    /*Chargement d'une police à partir du path*/
    TTF_Font* police = TTF_OpenFont(path, taille);
    /*Vérification du chargement de la police*/
    if (!police) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        SDL_DestroyTexture(textureFond);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        exit(1);
    }
    return police;
}

/*Chargement d'un audio dans un chunk*/
Mix_Chunk* chargementAudio(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* textureFond, char* path)
{
    /*Cargement dans un chunk d'une musique avec le path*/
    Mix_Chunk* sound = Mix_LoadWAV(path);
    /*Vérification du chargement de l'audio*/
    if (!sound) {
        SDL_Log("Erreur lors du chargement de l'effet sonore : %s", Mix_GetError());
        SDL_DestroyTexture(textureFond);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        exit(1);
    }
    return sound;
}

/*Chargement d'une image*/
SDL_Texture* chargementImg(SDL_Renderer* rendu, SDL_Window* fenetre, char* path)
{
    /*Chargement dans une texture d'une image avec le path*/
    SDL_Texture* image = IMG_LoadTexture(rendu, path);
    /*Vérification du chargement de l'image*/
    if (!image) {
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        exit(1);
    }
    return image;
}

/*Création de rectangle dynamique*/
SDL_Rect creationRectangle(SDL_Window* fenetre, int x, int y, int largeur, int hauteur)
{
    /*Récupération des dimensions de la fenêtre*/
    int w, h;
    SDL_GetWindowSize(fenetre, &w, &h);

    /*Calcul des proportions relatives*/
    float widthFactor = (float)w / WINDOW_WIDTH;
    float heightFactor = (float)h / WINDOW_HEIGHT;
    
    /*Définition du rectangle en fonction des proportions relatives*/
    SDL_Rect rect = {x * widthFactor, y * heightFactor, largeur * widthFactor, hauteur * heightFactor};

    return rect;
}

/*Destruction des variables SDL et fermeture de la SDL*/
void destruction_SDL(SDL_Texture* parametre, SDL_Texture* gold, SDL_Texture* xp, SDL_Texture* textureFond, 
                     SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age, SDL_Texture* moderne,
                     SDL_Texture* futuriste, TTF_Font* police, TTF_Font* police_texte, SDL_Renderer* rendu,
                     SDL_Window* fenetre, Mix_Chunk* click, Mix_Chunk* music, SDL_Texture* sprite_hud[])
{

    int i;
    for(i = 0; i < 20; i++){
        SDL_DestroyTexture(sprite_hud[i]);
    }

    SDL_DestroyTexture(parametre);
    SDL_DestroyTexture(gold);
    SDL_DestroyTexture(xp);
    SDL_DestroyTexture(textureFond);
    SDL_DestroyTexture(prehistoire);
    SDL_DestroyTexture(antiquite);
    SDL_DestroyTexture(moyen_age);
    SDL_DestroyTexture(moderne);
    SDL_DestroyTexture(futuriste);
    TTF_CloseFont(police);
    TTF_CloseFont(police_texte);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_FreeChunk(click);
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}