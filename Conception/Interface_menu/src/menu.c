#include "lib/menu.h"


/***************/
/*--Fonctions--*/
/***************/

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

/*Gestion de l'affichage des menus et sous-menus*/
void affichage(etatMenu_t etatMenu, SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police , int menuX, int menuY, element_t* elm_reso, int* selecElement, const char* effet)
{
    /*Afficher le menu en fonction de l'état*/
    switch(etatMenu){
        case(MENU_PRINCIPAL):
            menuX = (WINDOW_WIDTH - MENU_WIDTH ) / 2;
            menuY = (WINDOW_HEIGHT - (MENU_HEIGHT - MENU_DECALAGE) ) / 2;
            afficherMenu(rendu, police, fenetre, "Menu Principal", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
            break;
        
        case(MENU_SOUS):
            afficherSousMenu(rendu, police, fenetre, "Jouer", "Reprendre une partie", "Options", "Crédit","Quitter");
            break;

        /*Affichage du sous-menu Paramètres*/
        case(MENU_SOUS_OPTIONS):
            afficherSousMenuOption(rendu, police, fenetre, "Musique / Son", "Résolution","Retour");
            break;
        
        case(MENU_SOUS_RESOLUTION):
            afficherSousMenuResolution(rendu, police, fenetre);
            resolution(rendu, fenetre, police, elm_reso, selecElement);
            break;

        case(MENU_SOUS_CREDITS):
            afficherSousMenuCredits(rendu, fenetre, police);
            break;

        case(MENU_SOUS_SON):
            afficherSousMenuSon(rendu, police, fenetre, effet);
            break;
    }
}

/*Chargement de la police principale*/
TTF_Font* chargementPolice(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* textureFond, char* path, int taille)
{
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

    SDL_Surface* surfaceTexte = TTF_RenderUTF8_Solid(police, texte, couleurTexte);
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

    // Afficher les onglets du sous-menu avec espacement
    afficherMenu(rendu, police, fenetre, texte1, menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte2, menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte3, menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte4, menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, texte5, menuX, menuY + 4 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
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

/*Gestion du clic de la souris sur les éléments du menu*/
void clic_menu(etatMenu_t* etatMenu, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, int* continuer, int* selecElement, char* effet)
{
    /*Gestion des clics sur les menus*/
    switch((*etatMenu)){
        /*Vérifier si le clic est dans la zone du menu principal*/
        case MENU_PRINCIPAL:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;
            menuY = (h - MENU_HEIGHT * heightFactor + MENU_DECALAGE) / 2;
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
                /*Clic sur le menu principal, passer à l'état MENU_SOUS*/
                (*etatMenu) = MENU_SOUS;
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                }
            }
            break;
        
        /*Vérifier si le clic est dans la zone du sous-menu*/
        case MENU_SOUS:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;  /*Position horizontale centrée pour le sous-menu*/
            menuY = (h - (4 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2;  /*Position verticale centrée pour le sous-menu*/
            
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) && 
                mouseY >= menuY && mouseY <= menuY + 5 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                /*Clic sur une option du sous-menu*/
                if (mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
                    //Clic sur l'option "Jouer"
                    SDL_Log("Clic sur Jouer !");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                }
                
                else if (mouseY >= menuY + ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                    //Clic sur l'option "Reprendre une partie"
                    SDL_Log("Clic sur Reprendre une partie !");
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                }
                else if (mouseY >= menuY + 2 * ((MENU_HEIGHT  + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                    //Clic sur l'option "Paramètres"
                    SDL_Log("Clic sur Options !");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    //Changer l'état du menu
                    (*etatMenu) = MENU_SOUS_OPTIONS;
                }
                else if (mouseY >= menuY + 3 * ((MENU_HEIGHT  + SPACING) * heightFactor) && mouseY <= menuY + 4 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                    //Clique sur les crédits
                    SDL_Log("Clic sur Crédits !");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    //Change l'état du menu
                    (*etatMenu) = MENU_SOUS_CREDITS;
                }
                else if (mouseY >= menuY + 4 * ((MENU_HEIGHT  + SPACING) * heightFactor) && mouseY <= menuY + 5 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                    //Clic sur l'option "Quitter"
                    SDL_Log("Clic sur Quitter !");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*continuer) = SDL_FALSE;
                }
            }
            break;
        
        /*Vérifier si le clic est dans la zone du sous-menu Options*/
        case MENU_SOUS_OPTIONS:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;
            menuY = (h - (2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2;  /*Position verticale centrée pour le sous-menu*/
            
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                mouseY >= menuY && mouseY <= menuY + 3 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                /*Clic sur une option du sous-menu Options*/
                if (mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT  * heightFactor)) {
                    SDL_Log("Clic sur Son!");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_SON;
                }
                else if (mouseY >= menuY + ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    //Clic sur l'option "Résolution"
                    SDL_Log("Clic sur Résolution !");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_RESOLUTION;
                }
                else if (mouseY >= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    // Clic sur l'option "Retour", revenir au menu précédent
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS;
                }
            }
            break;
        
        case MENU_SOUS_RESOLUTION:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale
            
            //Gestion de la sélection de la résolution
            if (mouseX >= menuX - (MENU_WIDTH / 3) && mouseX <= menuX + (MENU_WIDTH * widthFactor) + (MENU_WIDTH / 3) &&
                mouseY >= menuY && mouseY <= menuY + ((MENU_HEIGHT * heightFactor) + SPACING)) {
                //Clique sur flèche de droite
                if (mouseY <= menuY + (MENU_HEIGHT * heightFactor) && mouseX >= menuX + (MENU_WIDTH * widthFactor)){
                    printf("++ \n");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*selecElement)++;
                }
                //Clique sur flèche de gauche
                else if(mouseY <= menuY + (MENU_HEIGHT * heightFactor) && mouseX <= menuX){
                    printf("--\n");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*selecElement)--;
                }
                //Pour créer un système de boucle sans fin (quand on est sur le dernier élément on repasse au premier)
                if((*selecElement) >= 4){
                    (*selecElement) = 0;
                }
                else if((*selecElement) < 0){
                    (*selecElement) = 3;
                }
                SDL_SetWindowSize(fenetre, elm_reso[(*selecElement)].w, elm_reso[(*selecElement)].h);
            }
            //Gestion des 2 boutons "Plein ecran" et "Retour"
            else if(mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                    mouseY >= menuY + 1.5 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3.5 * ((MENU_HEIGHT + SPACING) * heightFactor)){
                
                if(mouseY >= menuY + 1.5 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2.5 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    //Gestion du plein écran
                    SDL_Log("Plein  ecran");
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    if (SDL_GetWindowFlags(fenetre) & SDL_WINDOW_FULLSCREEN) {
                        SDL_SetWindowFullscreen(fenetre, 0); //Mode fenêtré
                    } else {
                        SDL_SetWindowFullscreen(fenetre, SDL_WINDOW_FULLSCREEN_DESKTOP); //Plein écran
                    }
                }
                else if(mouseY >= menuY + 2.5 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3.5 * ((MENU_HEIGHT + SPACING) * heightFactor) ){
                    //Clic sur l'option "Retour" 
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_OPTIONS;
                }
            }
            break;
        case MENU_SOUS_CREDITS:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - (MENU_HEIGHT * heightFactor)) / 2; //Position verticale
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                mouseY >= menuY + 335 * heightFactor && mouseY <= menuY + (((MENU_HEIGHT - 20 + 335) * heightFactor))){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS;
                }
            break;
        
        case MENU_SOUS_SON:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY - MENU_HEIGHT && mouseY <= menuY + 4 * ((MENU_HEIGHT * heightFactor)) + SPACING) {
                
                if (mouseY >= menuY && mouseY <= menuY + (30  * heightFactor)) {
                    //Détecter si l'utilisateur clique sur le curseur
                    if (evenement.button.button == SDL_BUTTON_LEFT &&
                        SDL_PointInRect(&(SDL_Point){evenement.button.x, evenement.button.y}, volumeCursor)){
                        estLache = SDL_TRUE;
                    }
                }
                else if(mouseY >= menuY + 2.1 * (MENU_HEIGHT * heightFactor) && mouseY <= menuY + 2.9 * (MENU_HEIGHT * heightFactor)){
                    //Gestion de l'activation/désactivation du son
                    if((*index_effet) == 0){
                        strcpy(effet,"Activer");
                        (*index_effet) = 1;
                    }
                    else{
                        strcpy(effet,"Désactiver");
                        (*index_effet) = 0;
                        Mix_PlayChannel(1, click, 0);
                    }
                }
                else if(mouseY >= menuY + 3.1 * (MENU_HEIGHT * heightFactor) + SPACING && mouseY <= menuY + 4.4 * (MENU_HEIGHT * heightFactor)){
                    if(!(*index_effet) && !(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_OPTIONS;
                }
            }
            break;
        default : 
            break;
    }
}

/*Gestion du relachement du clic de la souris sur les éléments du menu*/
void relachement_menu(etatMenu_t* etatMenu, int menuX, int menuY, int w, int h, float* widthFactor, float* heightFactor, int mouseX, int mouseY)
{
    //Gestion du relachement du clique de la souris
    if((*etatMenu) == MENU_SOUS_SON){
        menuX = (w - (MENU_WIDTH * (*widthFactor))) / 2; //Position horizontale
        menuY = (h - ((MENU_HEIGHT * (*heightFactor)) + (SPACING * (*heightFactor)))) / 2; //Position verticale

        if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * (*widthFactor)) + 15 && 
            mouseY >= menuY && mouseY <= menuY + (30  * (*heightFactor))) {
            // Arrêter de déplacer le curseur lorsque le bouton de la souris est relâché
            estLache = SDL_FALSE;
            printf("\n\test relaché\n");
        }
    }
}

/*Gestion du déplacement de la souris sur les éléments du menu*/
void deplacement_menu(Mix_Chunk* music, int mouseX, SDL_Event evenement, float* widthFactor)
{
    // Déplacer le curseur si l'utilisateur déplace la souris tout en maintenant le bouton de la souris enfoncé
    if (estLache) {
        mouseX = evenement.motion.x;
        if (mouseX < volumeBar->x) {
            mouseX = volumeBar->x;
        } else if (mouseX > volumeBar->x + (volumeBar->w - 14 )) {
            mouseX = volumeBar->x + (volumeBar->w - 14);
        }
        volume = ((mouseX - volumeBar->x) / 2) / (*widthFactor);
        Mix_VolumeChunk(music, volume);
        volumeCursor->x = mouseX;
    }
}

/*Fonction de destruction des variables pour le menu*/
void destruction_menu(int* selecElement, int* index_effet, int* continuer, etatMenu_t* etatMenu, float* widthFactor, float* heightFactor)
{
    free(selecElement);
    free(volumeBar);
    free(volumeCursor);
    free(index_effet);
    free(continuer);
    free(etatMenu);
    free(widthFactor);
    free(heightFactor);
}