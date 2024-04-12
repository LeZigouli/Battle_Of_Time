#include "lib/affichage_menu.h"

/************************/
/*--Affichage du menu--*/
/***********************/

/*Gestion de l'affichage des menus et sous-menus*/
void affichage(etatMenu_t etatMenu, SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police , int menuX, int menuY, element_t* elm_reso, int* selecElement, const char* effet, int* textInputActive, char* textInput, int* isValid, int* keyCounts)
{
    /*Affiche le titre du jeu*/
    afficherTitre(rendu, police, fenetre, ((WINDOW_WIDTH - 800) / 2), ((WINDOW_HEIGHT - 1000) / 2), 800, 600);

    /*Afficher le menu en fonction de l'état*/
    switch(etatMenu){
        case MENU_PRINCIPAL:
            menuX = (WINDOW_WIDTH - MENU_WIDTH ) / 2;
            menuY = (WINDOW_HEIGHT - (MENU_HEIGHT - MENU_DECALAGE) ) / 2;
            afficherMenu(rendu, police, fenetre, "Menu Principal", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
            break;
        
        case MENU_SOUS:
            afficherSousMenu(rendu, police, fenetre, "Jouer", "Options", "Crédit","Quitter");
            break;

        /*Affichage du sous-menu Paramètres*/
        case MENU_SOUS_OPTIONS:
            afficherSousMenuOption(rendu, police, fenetre, "Musique / Son", "Résolution","Retour");
            break;
        
        case MENU_SOUS_RESOLUTION:
            afficherSousMenuResolution(rendu, police, fenetre);
            resolution(rendu, fenetre, police, elm_reso, selecElement);
            break;

        case MENU_SOUS_CREDITS:
            afficherSousMenuCredits(rendu, fenetre, police);
            break;

        case MENU_SOUS_SON:
            afficherSousMenuSon(rendu, police, fenetre, effet);
            break;
        
        case MENU_SOUS_JOUER:
            afficherSousMenuJouer(rendu, fenetre, police);
            break;

        case MENU_SOUS_SOLO:
            afficherSousMenuSolo(rendu, fenetre, police);
            break;

        case MENU_SOUS_ENLIGNE:
            afficherSousMenuEnLigne(rendu, fenetre, police);
            break;
        
        case MENU_SOUS_REJOINDRE:
            afficherSousMenuRejoindre(rendu, fenetre, police, textInputActive, textInput, isValid, keyCounts);
            break;
    }
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

    SDL_Surface* surfaceTexte = TTF_RenderUTF8_Solid(police, texte, couleurTexte);
    SDL_Texture* textureTexte = SDL_CreateTextureFromSurface(rendu, surfaceTexte);

    SDL_Rect rectangleMenu = creationRectangle(fenetre, x, y,largeur,hauteur);
    SDL_RenderCopy(rendu, textureTexte, NULL, &rectangleMenu);

    SDL_FreeSurface(surfaceTexte);
    SDL_DestroyTexture(textureTexte);
}

/*Fonction d'affichage des sous-menus*/
void afficherSousMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3, const char* texte4)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT - MENU_HEIGHT + 2 * SPACING) / 2;  // Position verticale centrée pour le sous-menu

    // Afficher les onglets du sous-menu avec espacement
    afficherMenu(rendu, police, fenetre, texte1, menuX, menuY - (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte2, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte3, menuX, menuY + (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte4, menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Fonction d'affichage des sous-menus*/
void afficherSousMenuOption(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT -  (2 * MENU_HEIGHT + SPACING)) / 2;  // Position verticale centrée pour le sous-menu

    // Afficher les onglets du sous-menu avec espacement
    afficherMenu(rendu, police, fenetre, texte1, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte2, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte3, menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage du sous-menu résolution*/
void afficherSousMenuResolution(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Afficher les flèches de sélections*/
    //Flèche droite
    SDL_Texture* texture_fleche_d = IMG_LoadTexture(rendu, "img/fleche_menu_droite.png");
    SDL_Rect rect_flechD = creationRectangle(fenetre, menuX + MENU_WIDTH, menuY, MENU_WIDTH / 3, MENU_HEIGHT * 1.5);
    SDL_RenderCopy(rendu, texture_fleche_d, NULL, &rect_flechD);
    SDL_DestroyTexture(texture_fleche_d);

    //Flèche gauche
    SDL_Texture* texture_fleche_g = IMG_LoadTexture(rendu, "img/fleche_menu_gauche.png");
    SDL_Rect rect_flechG = creationRectangle(fenetre, menuX - 90, menuY, MENU_WIDTH / 3, MENU_HEIGHT * 1.5);
    SDL_RenderCopy(rendu, texture_fleche_g, NULL, &rect_flechG);
    SDL_DestroyTexture(texture_fleche_g);

    //Afficher les onglets
    afficherMenu(rendu, police, fenetre, "Plein écran", menuX, menuY + 1.5 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 2.5 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage du menu jouer*/
void afficherSousMenuJouer(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    afficherMenu(rendu, police, fenetre, "Solo", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "En ligne", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);

}

/*Affichage du menu Solo*/
void afficherSousMenuSolo(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    afficherMenu(rendu, police, fenetre, "Nouvelle Partie", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Reprendre Partie", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage de menu Enligne*/
void afficherSousMenuEnLigne(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    afficherMenu(rendu, police, fenetre, "Créer partie", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Rejoindre partie", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Initialiser du bloc avec les résolutions*/
void initElements(SDL_Renderer* rendu, SDL_Window* fenetre, element_t* elm_reso) 
{

    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; // Coordonnée x pour centrer les éléments horizontalement
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; // Coordonnée y pour centrer les éléments verticalement

    // Informations à afficher pour chaque élément
    char* infos[4] = {"800x600", "1024x768", "1280x720", "1920x1080"};
    int largeur[4] = {800, 1024, 1080, 1920};
    int hauteur[4] = {600, 768, 720, 1080};

    for (int i = 0; i < 4; ++i) {
        elm_reso[i].rect = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, MENU_HEIGHT * 1.5);
        elm_reso[i].info = infos[i];
        elm_reso[i].w = largeur[i];
        elm_reso[i].h = hauteur[i];
    }
}

/*Affichage du bloc résolution dans le sous-menu résolution*/
void resolution(SDL_Renderer* rendu, SDL_Window* fenetre , TTF_Font* police, element_t* elm_reso, int* selecElement)
{
    //Dessiner l'élément sélectionné
    SDL_Rect shiftedRect = {elm_reso[(*selecElement)].rect.x, elm_reso[(*selecElement)].rect.y, elm_reso[(*selecElement)].rect.w, elm_reso[(*selecElement)].rect.h};
    // Dessiner le texte pour l'élément sélectionné
    SDL_Surface* textSurface = TTF_RenderText_Solid(police, elm_reso[(*selecElement)].info, COLOR);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rendu, textSurface);
    SDL_Rect textRect = creationRectangle(fenetre, shiftedRect.x, shiftedRect.y, shiftedRect.w, shiftedRect.h);
    SDL_RenderCopy(rendu, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

/*Affichage du sous menu crédits*/
void afficherSousMenuCredits(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    int img_w = 700 / 1.2;
    int img_h = 549 / 1.25;
    int menuX_img = (WINDOW_WIDTH - img_w) / 2; //Position horizontale
    int menuY_img = (WINDOW_HEIGHT - img_h) / 2; //Position verticale

    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;
    int menuY = (WINDOW_HEIGHT - MENU_HEIGHT) / 2;

    //Chargement de l'image
    SDL_Texture* texture_credit = NULL;
    texture_credit = IMG_LoadTexture(rendu, "img/credits.png");
    if(texture_credit == NULL){
        SDL_Log("Erreur lors du chargement image des crédits : %s\n", SDL_GetError());
    }

    SDL_Rect rect_credit = creationRectangle(fenetre, menuX_img, menuY_img + 100, img_w, img_h);
    SDL_RenderCopy(rendu, texture_credit, NULL, &rect_credit);
    SDL_DestroyTexture(texture_credit);

    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 335, MENU_WIDTH, MENU_HEIGHT - 20);
}

/*Affichage du sous menu son*/
void afficherSousMenuSon(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    // Variables pour gérer le curseur de volume
    (*volumeBar)  = creationRectangle(fenetre, menuX, menuY + 2.5, MENU_WIDTH, 25);
    (*volumeCursor) = creationRectangle(fenetre, menuX + volume * 2, menuY - 2.5, 15, 35);

    // Dessiner la barre de volume
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderFillRect(rendu, volumeBar);

    // Dessiner le curseur de volume
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderFillRect(rendu, volumeCursor);


    afficherMenu(rendu, police, fenetre, "Musique :", menuX, menuY - MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Effets sonores :", menuX, menuY + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte, menuX, menuY + 2 * MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu ,police, fenetre, "Retour", menuX, menuY + 3 * MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage du sous-menu 'Rejoindre partie' en ligne*/
void afficherSousMenuRejoindre(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police, int* textInputActive, char* textInput, int* isValid, int* keyCounts)
{
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_Rect zone_texte = creationRectangle(fenetre, menuX - 70, menuY + 60, 350, 70);
    SDL_RenderFillRect(rendu, &zone_texte); 

    SDL_Surface* message = NULL;

    SDL_Surface* textSurface = TTF_RenderText_Solid(police, textInput, (SDL_Color){0, 0, 0, 255});
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rendu, textSurface);
        if (textTexture) {
            SDL_Rect textRect = creationRectangle(fenetre, menuX - 70, menuY + 60, textSurface->w, textSurface->h);
            SDL_RenderCopy(rendu, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }

    if((*isValid)){
        message = TTF_RenderText_Solid(police, "Adresse IP valide", (SDL_Color){0, 255, 0, 255});
    }
    else{
        message = TTF_RenderText_Solid(police, "Adresse IP invalide", (SDL_Color){255, 0, 0, 255});
    }

    if((*keyCounts) > 0){
        // Afficher un message si l'IP est valide ou non
        if (message) {
            SDL_Texture* messagetexture = SDL_CreateTextureFromSurface(rendu, message);
            if (message) {
                SDL_Rect messRect = creationRectangle(fenetre, menuX - 410, menuY + 70, message->w-40, message->h-20);
                SDL_RenderCopy(rendu, messagetexture, NULL, &messRect);
                SDL_DestroyTexture(messagetexture);
            }
            SDL_FreeSurface(message);
        }
    }

    afficherMenu(rendu, police, fenetre, "Saisir l'IP du serveur :", menuX - 70, menuY, 300, 50);
    afficherMenu(rendu, police, fenetre, "Valider", menuX + 60, menuY + 130, 100, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX + 50, menuY + 230, 130, MENU_HEIGHT);
}