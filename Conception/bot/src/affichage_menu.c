#include "../lib/affichage_menu.h"

/************************/
/*--Affichage du menu--*/
/***********************/

/*Gestion de l'affichage des menus et sous-menus*/
void affichage(etat_t etat, int* etatAge, SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police , TTF_Font* police_texte, 
               int menuX, int menuY, element_t* elm_reso, int* selecElement, const char* effet, char* textInput, 
               int* isValid, int* keyCounts, SDL_Texture* parametre, SDL_Texture* gold, SDL_Texture* xp,
               SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age,
               SDL_Texture* moderne, SDL_Texture* futuriste, player_t* joueur, SDL_Texture** sprite_hud, SDL_Texture* upgrade,
               ordi_t* ordi, int* cameraX, int* cameraY, SDL_Texture* ultim, SDL_Texture* building[], int fin_partie, SDL_Texture * win,
               SDL_Texture * lose, character_t* tab_charactere, int survol)
{
    /*Affiche le titre du jeu*/
    afficherTitre(rendu, fenetre, ((WINDOW_WIDTH - 800) / 2), ((WINDOW_HEIGHT - 1000) / 2), 800, 600);

    /*Afficher le menu en fonction de l'état*/
    switch(etat){

        case PAGE_ACCUEIL:
            menuX = (WINDOW_WIDTH - MENU_WIDTH ) / 2;
            menuY = (WINDOW_HEIGHT - (MENU_HEIGHT - MENU_DECALAGE) ) / 2;

            /*Affichage du rectangle translucide derrière le menu*/
            SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
            SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(rendu, &rect_menu);
            /*Affichage du bouton*/
            afficherMenu(rendu, police, fenetre, "Menu Principal", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
            break;
        
        case MENU_PRINCIPAL:
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

        case MENU_SOUS_CREER:
            afficherSousMenuCreer(rendu, fenetre, police);
            break;
        
        case MENU_SOUS_REJOINDRE:
            afficherSousMenuRejoindre(rendu, fenetre, police, textInput, isValid, keyCounts);
            break;

        case MENU_DIFFICULTE:
            afficherSousMenuDifficulte(rendu, fenetre, police);
            break;
        
        case JOUER:
            /*Effacement de l'ancien rendu*/
            SDL_RenderClear(rendu);   
            gestionAffichageFondJeu(rendu, fenetre, etatAge, prehistoire, antiquite, moyen_age, moderne, futuriste, joueur, ordi, 
                                    cameraX, cameraY);
            afficherHUD(rendu, fenetre, police_texte, parametre, upgrade, gold, xp, joueur, sprite_hud, ultim, joueur->building->level);
            affichageBulding(rendu, fenetre, building, *cameraX, *cameraY, joueur->building->level, ordi->building->level);
            affichagePointDeVie(rendu, police, joueur->building->pv, ordi->building->pv, fenetre, (*cameraX), (*cameraY));
            affichageSurvolSouris(rendu, fenetre, police, survol, tab_charactere, joueur->building->level);
            break;
        case FIN_PARTIE :
            /*Effacement de l'ancien rendu*/
            SDL_RenderClear(rendu);   
            affichage_gagnant(rendu, police, fin_partie, fenetre, *cameraX, *cameraY, win, lose);
            break;

        case MENU_SAUVEGARDER :
            break;
        case JOUER_RESEAU_CREER :
            break;
        case JOUER_RESEAU_REJOINDRE :
            break;
        case JOUER_CHARGER :
            break;
        case MENU_SOUS_CREER_VALIDE :
            break;

        case OPTION_JEU:
            afficherOptionJeu(rendu, police, fenetre);
            break;
 
    }
}

/*Fonction pour afficher le titre du jeu*/
void afficherTitre(SDL_Renderer * rendu, SDL_Window* fenetre, int x, int y, int largeur, int hauteur)
{
    SDL_Texture* texture_titre = IMG_LoadTexture(rendu, "img/Battle_of_Time.png");

    SDL_Rect rect_titre = creationRectangle(fenetre, x, y,largeur,hauteur);
    SDL_RenderCopy(rendu, texture_titre, NULL, &rect_titre);

    SDL_DestroyTexture(texture_titre);
}

/*Fonction d'affichage d'un élément du menu*/
void afficherMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte, int x, int y, int largeur, int hauteur)
{
    /*Création de la surface et de la texture avec le texte, la police et la couleur*/
    SDL_Surface* surfaceTexte = TTF_RenderUTF8_Solid(police, texte, BLACK);
    SDL_Texture* textureTexte = SDL_CreateTextureFromSurface(rendu, surfaceTexte);

    /*Création du rectangle et affichage de l'élément*/
    SDL_Rect rectangleMenu = creationRectangle(fenetre, x, y,largeur,hauteur);
    SDL_RenderCopy(rendu, textureTexte, NULL, &rectangleMenu);

    /*Suppression des variables de travail*/
    SDL_FreeSurface(surfaceTexte);
    SDL_DestroyTexture(textureTexte);
}

/*Fonction d'affichage des sous-menus*/
void afficherSousMenu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3, const char* texte4)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT - MENU_HEIGHT + 2 * SPACING) / 2;  // Position verticale centrée pour le sous-menu

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY - (MENU_HEIGHT + SPACING), MENU_WIDTH, (4 * MENU_HEIGHT) + (3 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Afficher les onglets du menu avec espacement*/
    afficherMenu(rendu, police, fenetre, texte1, menuX, menuY - (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte2, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte3, menuX, menuY + (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte4, menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Fonction d'affichage du sous-menu des options*/
void afficherSousMenuOption(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte1, const char* texte2, const char* texte3)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT -  (2 * MENU_HEIGHT + SPACING)) / 2;  // Position verticale centrée pour le sous-menu

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, (3 * MENU_HEIGHT) + (2 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Afficher les onglets du menu avec espacement*/
    afficherMenu(rendu, police, fenetre, texte1, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte2, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte3, menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage du sous-menu résolution*/
void afficherSousMenuResolution(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX - 90, menuY - 5, MENU_WIDTH + 175, (4 * MENU_HEIGHT) + (2 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

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

    /*Affichage des onglets du sous-menu*/
    afficherMenu(rendu, police, fenetre, "Plein écran", menuX, menuY + 1.5 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 2.5 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage du menu jouer*/
void afficherSousMenuJouer(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, (4 * MENU_HEIGHT) + (3 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Affichage des onglets du sous-menu*/
    afficherMenu(rendu, police, fenetre, "Solo", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "En ligne", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);

}

/*Affichage du menu Solo*/
void afficherSousMenuSolo(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, (4 * MENU_HEIGHT) + (3 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Affichage des onglets du sous-menu*/
    afficherMenu(rendu, police, fenetre, "Nouvelle Partie", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Reprendre Partie", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage de menu Enligne*/
void afficherSousMenuEnLigne(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, (4 * MENU_HEIGHT) + (3 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Affichage des onglets du sous-menu*/
    afficherMenu(rendu, police, fenetre, "Créer partie", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Rejoindre partie", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

/*Initialisation du bloc avec les résolutions*/
void initElements(SDL_Renderer* rendu, SDL_Window* fenetre, element_t* elm_reso) 
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; // Coordonnée x pour centrer les éléments horizontalement
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; // Coordonnée y pour centrer les éléments verticalement

    /*Tableaux contenants les informations de dimensions de la fenêtre*/
    char* infos[4] = {"800x600", "1024x768", "1280x720", "1920x1080"};
    int largeur[4] = {800, 1024, 1080, 1920};
    int hauteur[4] = {600, 768, 720, 1080};

    /*Affectation des information dans les structures d'éléments*/
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
    /*Affichage l'élément selectionné */
    SDL_Rect shiftedRect = {elm_reso[(*selecElement)].rect.x, elm_reso[(*selecElement)].rect.y, elm_reso[(*selecElement)].rect.w, elm_reso[(*selecElement)].rect.h};
    
    /*Affichage le texte pour l'élément sélectionné*/
    SDL_Surface* textSurface = TTF_RenderText_Solid(police, elm_reso[(*selecElement)].info, BLACK);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rendu, textSurface);
    SDL_Rect textRect = creationRectangle(fenetre, shiftedRect.x, shiftedRect.y, shiftedRect.w, shiftedRect.h);
    SDL_RenderCopy(rendu, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

/*Affichage du sous menu crédits*/
void afficherSousMenuCredits(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    /*Calcul des dimensions de l'image */
    int img_w = 700 / 1.2;
    int img_h = 549 / 1.25;
    /*Calcul des positions x et y pour l'image*/
    int menuX_img = (WINDOW_WIDTH - img_w) / 2; //Position horizontale
    int menuY_img = (WINDOW_HEIGHT - img_h) / 2; //Position verticale
    /*Calcul des positions x et y pour le bouton 'Retour'*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;
    int menuY = (WINDOW_HEIGHT - MENU_HEIGHT) / 2;

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY + 335, MENU_WIDTH, MENU_HEIGHT - 20);
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Chargement de l'image des crédits*/
    SDL_Texture* texture_credit = chargementImg(rendu, fenetre, "../img/credits.png");

    /*Affichage de l'image chargée*/
    SDL_Rect rect_credit = creationRectangle(fenetre, menuX_img, menuY_img + 100, img_w, img_h);
    SDL_RenderCopy(rendu, texture_credit, NULL, &rect_credit);
    SDL_DestroyTexture(texture_credit);

    /*Affichage du bouton 'Retour'*/
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 335, MENU_WIDTH, MENU_HEIGHT - 20);
}

/*Affichage du sous menu son*/
void afficherSousMenuSon(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre, const char* texte)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX - 5, menuY - MENU_HEIGHT, MENU_WIDTH + 10, (4 * MENU_HEIGHT) + (3 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Variables pour gérer le curseur de volume*/
    (*volumeBar)  = creationRectangle(fenetre, menuX, menuY + 2.5, MENU_WIDTH, 25);
    (*volumeCursor) = creationRectangle(fenetre, menuX + volume * 2, menuY - 2.5, 15, 35);

    /*Dessiner la barre de volume*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderFillRect(rendu, volumeBar);

    /*Dessiner le curseur de volume*/
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderFillRect(rendu, volumeCursor);

    /*Affichage des différents boutons du sous-menu*/
    afficherMenu(rendu, police, fenetre, "Musique :", menuX, menuY - MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Effets sonores :", menuX, menuY + MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte, menuX, menuY + 2 * MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu ,police, fenetre, "Retour", menuX, menuY + 3 * MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
}

/*Affichage du sous-menu 'Rejoindre partie' en ligne*/
void afficherSousMenuRejoindre(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police, char* textInput, int* isValid, int* keyCounts)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX - 75 , menuY, 360, (4 * MENU_HEIGHT) + (2 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Affichage de la zone de texte blanche*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_Rect zone_texte = creationRectangle(fenetre, menuX - 70, menuY + 60, 350, 70);
    SDL_RenderFillRect(rendu, &zone_texte); 

    /*Affichage du texte saisie par l'utilisateur*/
    SDL_Surface* textSurface = TTF_RenderText_Solid(police, textInput, BLACK);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rendu, textSurface);
        if (textTexture) {
            SDL_Rect textRect = creationRectangle(fenetre, menuX - 70, menuY + 60, textSurface->w, textSurface->h);
            SDL_RenderCopy(rendu, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }

    /*Affecte le message de conformité de l'adresse IP*/
    SDL_Surface* message = NULL;
    if((*isValid)){
        message = TTF_RenderText_Solid(police, "Adresse IP valide", GREEN);
    }
    else{
        message = TTF_RenderText_Solid(police, "Adresse IP invalide", RED);
    }

    /*Affichage du message de conformité de l'adresse IP
     *il faut que l'utilisateur ait déjà saisi quelque choe dans la zone de texte
     */
    if((*keyCounts) > 0){
        if (message) {
            SDL_Texture* messagetexture = SDL_CreateTextureFromSurface(rendu, message);
            
            /*Affichage de la zone de texte noir*/
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
            SDL_Rect zone_texte = creationRectangle(fenetre, menuX - 410, menuY + 70, message->w-40, message->h-20);
            SDL_RenderFillRect(rendu, &zone_texte); 
            /*Affichage du message*/
            SDL_Rect messRect = creationRectangle(fenetre, menuX - 410, menuY + 70, message->w-40, message->h-20);
            SDL_RenderCopy(rendu, messagetexture, NULL, &messRect);
            SDL_DestroyTexture(messagetexture);

            SDL_FreeSurface(message);
        }
    }

    /*Affichage des différents boutons du sous-menu*/
    afficherMenu(rendu, police, fenetre, "Saisir l'IP du serveur :", menuX - 70, menuY, 300, 50);
    afficherMenu(rendu, police, fenetre, "Valider", menuX + 60, menuY + 130, 100, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX + 50, menuY + 230, 130, MENU_HEIGHT);
}

/*Affichage du sous-menu 'Difficulté'*/
void afficherSousMenuDifficulte(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, (4 * MENU_HEIGHT) + (3 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Affichage des différents boutons du sous-menu*/
    afficherMenu(rendu, police, fenetre, "Facile", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Moyen", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Difficile", menuX, menuY + 2 * MENU_HEIGHT + 2 * SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY + 3 * MENU_HEIGHT + 3 * SPACING, MENU_WIDTH, MENU_HEIGHT);
}

void afficherSousMenuCreer(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2; //Position horizontale
    int menuY = (WINDOW_HEIGHT - (MENU_HEIGHT + SPACING)) / 2; //Position verticale

    /*Affichage de la zone de texte blanche*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_Rect zone_texte = creationRectangle(fenetre, menuX - 70, menuY + 60, 350, 70);
    SDL_RenderFillRect(rendu, &zone_texte);

    char* IP = get_ip_serveur();

    SDL_Surface* IPSurface = TTF_RenderText_Solid(police, IP, BLACK);
    SDL_Texture* IPTexture = SDL_CreateTextureFromSurface(rendu, IPSurface);

    SDL_Rect textRect = creationRectangle(fenetre, menuX - 70, menuY + 60, IPSurface->w, IPSurface->h);
    SDL_RenderCopy(rendu, IPTexture, NULL, &textRect);
    SDL_DestroyTexture(IPTexture);

    init_reseau_serveur();
}
