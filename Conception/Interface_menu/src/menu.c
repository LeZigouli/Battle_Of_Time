#include "../lib/menu.h"


/***************/
/*--Fonctions--*/
/***************/

/*Fonction d'affichage du menu*/
void afficherMenu(SDL_Renderer* rendu, TTF_Font* police, const char* texte, int x, int y, int largeur, int hauteur)
{
    SDL_Color couleurTexte = COLOR;  // Couleur du texte 

    SDL_Surface* surfaceTexte = TTF_RenderText_Solid(police, texte, couleurTexte);
    SDL_Texture* textureTexte = SDL_CreateTextureFromSurface(rendu, surfaceTexte);

    SDL_Rect rectangleMenu = {x, y, largeur, hauteur};
    SDL_RenderCopy(rendu, textureTexte, NULL, &rectangleMenu);

    SDL_FreeSurface(surfaceTexte);
    SDL_DestroyTexture(textureTexte);
}

/*Fonction d'affichage des sous-menus*/
void afficherSousMenu(SDL_Renderer* rendu, TTF_Font* police, const char* texte1, const char* texte2, const char* texte3, const char* texte4,const char* texte5)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT - (4 * MENU_HEIGHT + 3 * SPACING)) / 2;  // Position verticale centrée pour le sous-menu

    // Afficher les options du sous-menu avec espacement
    afficherMenu(rendu, police, texte1, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, texte2, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, texte3, menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, texte4, menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, texte5, menuX, menuY + 4 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Fonction pour initialiser un élément de menu déroulant*/
void initMenuItem(MenuItem* item, const char* label, int x, int y)
{
    item->label = label;
    item->rect.x = x;
    item->rect.y = y;
    item->rect.w = MENU_ITEM_WIDTH;
    item->rect.h = MENU_ITEM_HEIGHT;
}

/*Fonction pour afficher le menu*/
void afficherMenuDeroulant(SDL_Renderer* renderer, MenuItem* item, TTF_Font* police, int currentItemIndex)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &item->rect);
    SDL_Surface* surface = TTF_RenderText_Solid(police, item->label, COLOR);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = { item[currentItemIndex].rect.x + (MENU_ITEM_WIDTH - surface->w) / 2, item[currentItemIndex].rect.y + (MENU_ITEM_HEIGHT - surface->h) / 2, surface->w, surface->h };
    
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}




/*Fonction pour afficher le sous-menu Résolution*/
/*
void afficherSousMenuResolution(SDL_Renderer* rendu, TTF_Font* police, const char* texte, const char* texte1, int x, int y, int largeur, int hauteur, SDL_Color couleurTexte)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT - (2 * MENU_HEIGHT + SPACING)) / 2;  // Position verticale centrée pour le sous-menu

    afficherMenu(rendu, police, texte, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, texte1, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
}*/

/*Fonction pour afficher le sous-menu Résolution*/

void afficherSousMenuResolution(SDL_Renderer* rendu, MenuItem* item, TTF_Font* police, const char* texte1, const char* texte2, int currentItemIndex) 
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT - (3 * MENU_HEIGHT + 2 * SPACING)) / 2;  // Position verticale centrée pour le sous-menu

    // Afficher les options du sous-menu avec espacement
    afficherMenuDeroulant(rendu,item, police, currentItemIndex);
    afficherMenu(rendu, police, texte2, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
}


/*Fonction pour mettre à jour la position du menu lors du changement de dimensions de la fenêtre*/
void mettreAJourPositionMenu(int* menuX, int* menuY)
{
    *menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;
    *menuY = (WINDOW_HEIGHT - MENU_HEIGHT) / 2;
}

/*Fonction pour mettre à jour la position du sous-menu lors du changement de dimensions de la fenêtre*/
void mettreAJourPositionSousMenu(int* menuX, int* menuY)
{
    *menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;
    *menuY = (WINDOW_HEIGHT - (4 * MENU_HEIGHT + 3 * SPACING)) / 2;
}