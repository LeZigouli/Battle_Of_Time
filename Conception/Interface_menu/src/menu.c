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

/*Gestion du clic de la souris sur les éléments du menu*/
void clic_menu(etatMenu_t* etatMenu, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, int* continuer, int* selecElement, char* effet, int* isValid, const char* textInput, const char* ipPattern, int* textInputActive, int* keyCounts)
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
            menuY = (h - (MENU_HEIGHT * heightFactor) + ((2 * SPACING) * heightFactor)) / 2;  /*Position verticale centrée pour le sous-menu*/
            
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) && 
                mouseY >= menuY - (MENU_HEIGHT * heightFactor) - (SPACING * heightFactor) && mouseY <= menuY + 5 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                /*Clic sur une option du sous-menu*/
                //printf("DEDANS\n");
                if (mouseY >= menuY - 0.8 * (MENU_HEIGHT * heightFactor) - SPACING * heightFactor && mouseY <= menuY - 1.4 * SPACING * heightFactor) {
                    (*etatMenu) = MENU_SOUS_JOUER;
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                }
                else if (mouseY >= menuY + ((SPACING/2) * heightFactor) && mouseY <= menuY + 0.9 * (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    //Changer l'état du menu
                    (*etatMenu) = MENU_SOUS_OPTIONS;
                }
                else if (mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    //Change l'état du menu
                    (*etatMenu) = MENU_SOUS_CREDITS;
                }
                else if (mouseY >= menuY + 2.7 * (MENU_HEIGHT  * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 3.4 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)) {
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

                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_SON;
                }
                else if (mouseY >= menuY + ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {

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
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*selecElement)++;
                }
                //Clique sur flèche de gauche
                else if(mouseY <= menuY + (MENU_HEIGHT * heightFactor) && mouseX <= menuX){
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
        
        case MENU_SOUS_JOUER:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY && mouseY <= menuY + 3 * (((MENU_HEIGHT + SPACING) * heightFactor)) + MENU_HEIGHT){
            
                if(mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_SOLO;
                }
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_ENLIGNE;
                } 
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS;
                }
            }

            break;
        
        case MENU_SOUS_SOLO:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY && mouseY <= menuY + 3 * (((MENU_HEIGHT + SPACING) * heightFactor)) + MENU_HEIGHT){
            
                if(mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                }
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                } 
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_JOUER;
                }
            }
            break;

        case MENU_SOUS_ENLIGNE:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY && mouseY <= menuY + 3 * (((MENU_HEIGHT + SPACING) * heightFactor)) + MENU_HEIGHT){
            
                if(mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                }
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_REJOINDRE;
                } 
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*etatMenu) = MENU_SOUS_JOUER;
                }
            }
            break;

        case MENU_SOUS_REJOINDRE:
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX + (50 * widthFactor) && mouseX <= menuX + (180 * widthFactor) &&
                mouseY >= menuY + (135 * heightFactor) && mouseY <= menuY + (280 * heightFactor) ){
                
                if(mouseX >= menuX + (60 * widthFactor) && mouseX <= menuX + (160 * widthFactor) &&
                   mouseY >= menuY + (137 * heightFactor) && mouseY <= menuY + (178 * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*isValid) = validateRegex(textInput, ipPattern);
                    (*textInputActive) = SDL_FALSE;
                    (*keyCounts)++;
                    printf("%i\n", (*isValid));
                }

                else if(mouseY >= menuY + (240 * heightFactor) && mouseY <= menuY + (290 * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*keyCounts) = 0;
                    (*etatMenu) = MENU_SOUS_ENLIGNE;
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
void destruction_menu(int* selecElement, int* index_effet, int* continuer, etatMenu_t* etatMenu, float* widthFactor, float* heightFactor, int* textInputActive, int* isValid, int* keyCounts)
{
    free(textInputActive);
    free(isValid);
    free(keyCounts);
    free(selecElement);
    free(volumeBar);
    free(volumeCursor);
    free(index_effet);
    free(continuer);
    free(etatMenu);
    free(widthFactor);
    free(heightFactor);
}

/*Fonction pour vérifier si une chaîne de caractères respecte une expression régulière*/
int validateRegex(const char *input, const char *pattern) 
{
    regex_t regex;
    int reti;

    // Compiler l'expression régulière
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        printf("Erreur lors de la compilation de l'expression régulière\n");
        return -1;
    }

    // Vérifier si la chaîne de caractères correspond à l'expression régulière
    reti = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    return reti == 0 ? 1 : 0;
}