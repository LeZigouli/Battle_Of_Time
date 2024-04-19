/**
 * \file commun_SDL.c
 * \brief Contient les fonction communes pour l'utilisation de la SDL
 * \author Poirier Victor
 * \date 10 avril 2024
 * \version 1.0
 * 
*/

#include "lib/commun_SDL.h"


/**
 * @brief Initialise SDL, SDL_image, SDL_ttf, et SDL_Mixer.
 * 
 * @return 0 en cas de succès, 1 en cas d'erreur.
 */
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

/**
 * @brief Charge une police à partir d'un fichier.
 * 
 * @param rendu Le renderer associé à la fenêtre.
 * @param fenetre La fenêtre où afficher le texte.
 * @param textureFond La texture de fond de l'interface.
 * @param path Le chemin vers le fichier de la police.
 * @param taille La taille de la police à charger.
 * @return Un pointeur vers la police chargée.
 */
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

/**
 * @brief Charge un fichier audio dans un chunk.
 * 
 * @param rendu Le renderer associé à la fenêtre.
 * @param fenetre La fenêtre où afficher le texte.
 * @param textureFond La texture de fond de l'interface.
 * @param path Le chemin vers le fichier audio.
 * @return Un pointeur vers le chunk audio chargé.
 */
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

/**
 * @brief Charge une image à partir d'un fichier.
 * 
 * @param rendu Le renderer associé à la fenêtre.
 * @param fenetre La fenêtre où afficher le texte.
 * @param path Le chemin vers le fichier image.
 * @return Une texture contenant l'image chargée.
 */
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


/**
 * @brief Crée un rectangle dynamique en fonction des dimensions de la fenêtre.
 * 
 * @param fenetre La fenêtre où afficher le rectangle.
 * @param x La position horizontale du rectangle.
 * @param y La position verticale du rectangle.
 * @param largeur La largeur du rectangle.
 * @param hauteur La hauteur du rectangle.
 * @return Le rectangle créé.
 */
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

/**
 * @brief Libère la mémoire allouée pour les variables SDL et ferme SDL.
 * 
 * @param parametre La texture du paramètre.
 * @param gold La texture de l'or.
 * @param xp La texture de l'expérience.
 * @param textureFond La texture de fond de l'interface.
 * @param prehistoire La texture pour la période préhistorique.
 * @param antiquite La texture pour la période de l'Antiquité.
 * @param moyen_age La texture pour la période du Moyen Âge.
 * @param moderne La texture pour la période moderne.
 * @param futuriste La texture pour la période futuriste.
 * @param police La police de caractères utilisée.
 * @param police_texte La police de caractères pour le texte.
 * @param rendu Le renderer associé à la fenêtre.
 * @param fenetre La fenêtre principale.
 * @param click Le son du clic.
 * @param music La musique du jeu.
 * @param sprite_hud Le tableau de textures pour l'interface HUD.
 * @param building Le tableau de textures pour les bâtiments.
 * @param win La texture pour l'écran de victoire.
 * @param lose La texture pour l'écran de défaite.
 */
void destruction_SDL(SDL_Texture* parametre, SDL_Texture* gold, SDL_Texture* xp, SDL_Texture* textureFond, 
                     SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age, SDL_Texture* moderne,
                     SDL_Texture* futuriste, TTF_Font* police, TTF_Font* police_texte, SDL_Renderer* rendu,
                     SDL_Window* fenetre, Mix_Chunk* click, Mix_Chunk* music, SDL_Texture* sprite_hud[], SDL_Texture* building[], SDL_Texture* win, SDL_Texture* lose)
{

    int i;
    for(i = 0; i < 20; i++){
        SDL_DestroyTexture(sprite_hud[i]);
    }

    for(i = 0; i < 10; i++){
        SDL_DestroyTexture(building[i]);
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
    SDL_DestroyTexture(win);
    SDL_DestroyTexture(lose);
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