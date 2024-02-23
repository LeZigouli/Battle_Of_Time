#include "../lib/menu.h"


/***************/
/*--Fonctions--*/
/***************/

/*Création de rectangle dynamique*/
SDL_Rect creationRectangle(SDL_Window* fenetre, int x, int y, int largeur, int hauteur)
{
    int w, h;

    SDL_GetWindowSize(fenetre, &w, &h);
    /*Calcul des proportions relatives*/
    float widthFactor = (float)w / WINDOW_WIDTH;
    float heightFactor = (float)h / WINDOW_HEIGHT;
    
    /*Définition du rectangle en fonction des proportions relatives*/
    SDL_Rect rect = {x * widthFactor, y * heightFactor, largeur * widthFactor, hauteur * heightFactor};

    return rect;
}

/*Fonction pour afficher le titre du jeu*/
void afficherTitre(SDL_Renderer * rendu, TTF_Font* police, SDL_Window* fenetre, int x, int y, int largeur, int hauteur)
{
    SDL_Texture* texture_titre = IMG_LoadTexture(rendu, "img/Battle_of_Time.png");

    SDL_Rect rect_titre = creationRectangle(fenetre, x, y,largeur,hauteur);
    SDL_RenderCopy(rendu, texture_titre, NULL, &rect_titre);

    SDL_DestroyTexture(texture_titre);
}

/*Fonction d'affichage du menu*/
void afficherMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte, int x, int y, int largeur, int hauteur)
{
    SDL_Color couleurTexte = COLOR;  // Couleur du texte 

    SDL_Surface* surfaceTexte = TTF_RenderText_Solid(police, texte, couleurTexte);
    SDL_Texture* textureTexte = SDL_CreateTextureFromSurface(rendu, surfaceTexte);

    SDL_Rect rectangleMenu = creationRectangle(fenetre, x, y,largeur,hauteur);
    SDL_RenderCopy(rendu, textureTexte, NULL, &rectangleMenu);

    SDL_FreeSurface(surfaceTexte);
    SDL_DestroyTexture(textureTexte);
}

/*Fonction d'affichage des sous-menus*/
void afficherSousMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3, const char* texte4,const char* texte5)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT -  ( 4 * MENU_HEIGHT + SPACING)) / 2;  // Position verticale centrée pour le sous-menu

    // Afficher les options du sous-menu avec espacement
    afficherMenu(rendu, police, fenetre, texte1, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte2, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte3, menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte4, menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte5, menuX, menuY + 4 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Création d'un menu*/
MenuItem* creerMenu(SDL_Window* fenetre, const char* item1, const char* item2, const char* item3, const char* item4, const char* item5)
{
    MenuItem* items = malloc(sizeof(MenuItem) * 5);
    if(items == NULL){
        printf("Erreur allocation mémoire menu\n");
    }
    int i;

    int w, h;

    SDL_GetWindowSize(fenetre, &w, &h);
    /*Calcul des proportions relatives*/
    float widthFactor = (float)w / WINDOW_WIDTH;
    float heightFactor = (float)h / WINDOW_HEIGHT;

    for(i = 0; i < 5; i++){
        MenuItem item;
        item.rect.x = MENU_ITEM_PADDING * widthFactor;
        item.rect.y = (i * (MENU_ITEM_HEIGHT + MENU_ITEM_PADDING) + MENU_ITEM_PADDING) * heightFactor;
        item.rect.w = 150 * widthFactor;
        item.rect.h = MENU_ITEM_HEIGHT * heightFactor;
        item.isHovered = false;
        items[i] = item;
    }

    sprintf(items[0].text, "%s", item1);
    sprintf(items[1].text, "%s", item2);
    sprintf(items[2].text, "%s", item3);
    sprintf(items[3].text, "%s", item4);
    sprintf(items[4].text, "%s", item5);


    return items;
}

/**/
void ligneHorizontale(int x, int y, int w, Uint32 coul)
{
    SDL_Surface* affichage;

    SDL_Rect r;
    
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = 1;
    
    SDL_FillRect(affichage, &r, coul);
}

/*Fonction pour afficher le menu*/
/*
void afficherMenuDeroulant(SDL_Renderer* renderer, SDL_Window* fenetre, Resolu_Item* item, TTF_Font* police, int item_courant)
{
    SDL_Rect rect = {}
    SDL_RenderDrawRect(renderer, &rect); 
    
    SDL_Surface* surface = TTF_RenderText_Solid(police, item->label, COLOR);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect textRect = creationRectangle(fenetre, item[item_courant].rect.x, item[item_courant].rect.y, item[]);
    //{ item[currentItemIndex].rect.x + (MENU_ITEM_WIDTH - surface->w) / 2, item[currentItemIndex].rect.y + (MENU_ITEM_HEIGHT - surface->h) / 2, surface->w, surface->h };
    
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
*/


/*Fonction pour afficher le sous-menu Résolution*/
/*
void afficherSousMenuResolution(SDL_Renderer* rendu, Resolu_Item* item, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, int currentItemIndex) 
{
   

    // Afficher les options du sous-menu avec espacement
    afficherMenuDeroulant(rendu,item, police, currentItemIndex);
    afficherMenu(rendu, police, fenetre, texte2, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
}
*/