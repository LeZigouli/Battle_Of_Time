/*
 * Projet Battle Of Time
 * Le 28 janvier 2024, 17:00
*/

/**************/
/*--Includes--*/
/**************/
#include "../lib/menu.h"


/*************************/
/*--Programme Principal--*/
/*************************/
int main(int argc, char* argv[]) {
    
    /*Initialisation des modules SDL*/
    if(initialisation() == 1){
        return 1;
    }

    /*Créer une fenêtre*/
    SDL_Window* fenetre = SDL_CreateWindow("BATTLE OF TIME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!fenetre) {
        SDL_Log("Erreur lors de la création de la fenêtre : %s", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    /*Créer un rendu pour la fenêtre*/
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!rendu) {
        SDL_Log("Erreur lors de la création du rendu : %s", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    /*L'image en fonds*/
    SDL_Texture* textureFond = IMG_LoadTexture(rendu, "img/Fond_menu.png");
    if (!textureFond) {
        SDL_Log("Erreur lors du chargement de l'image : %s", IMG_GetError());
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    /**********/
    /*-Police-*/
    /**********/
    /*Police pour le texte du menu*/
    TTF_Font* police = TTF_OpenFont("font/Handjet/Handjet-SemiBold.ttf", 60);  // Remplacez par le chemin de votre police
    if (!police) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        SDL_DestroyTexture(textureFond);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }
    TTF_SetFontHinting(police, TTF_HINTING_NORMAL);

    /*Police pour les FPS*/
    TTF_Font* police_fps = TTF_OpenFont("font/Handjet/Handjet-Regular.ttf", 200);
    if (!police_fps) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        SDL_DestroyTexture(textureFond);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }
    TTF_SetFontHinting(police_fps, TTF_HINTING_LIGHT_SUBPIXEL);
    


    /***********/
    /*-Musique-*/
    /***********/
    Mix_AllocateChannels(2); // Allouer 2 cannaux 
    Mix_Volume(0, volume); // Met le son a 50% en volume pour le premier cannaux
    Mix_Volume(1, MIX_MAX_VOLUME); // Met le son a 100% en volume pour le deuxièmme cannaux 

    /*Chargement son du clique de la souris*/
    Mix_Chunk* click = Mix_LoadWAV("sound/click.mp3");
    if (!click) {
        SDL_Log("Erreur lors du chargement de l'effet sonore : %s", Mix_GetError());
        SDL_DestroyTexture(textureFond);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    /*Chargement musique */
    Mix_Chunk* music = Mix_LoadWAV("sound/music.mp3");
    if (!music) {
        SDL_Log("Erreur lors du chargement de la musique : %s", Mix_GetError());
        SDL_DestroyTexture(textureFond);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    /*Etat initial du menu*/
    enum MenuState etatMenu = MENU_PRINCIPAL;

    /*Variables pour le compteur de FPS*/
    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    Uint32 frameCount = 0;
    float fps = 0.0f;

    /*Variables pour la gestion de la souris*/
    int menuX;
    int menuY;
    int mouseX;
    int mouseY;

    /*Variables pour le redimensionnement dynamique de la fenêtre*/
    int w;
    int h;

    /*Bloc d'instructions pour le menu de résolution*/
    Element elm_reso[4];
    int* selecElement = malloc(sizeof(int)) ; //Indice de l'élément sélectionné
    (*selecElement) = 2;
    initElements(rendu, fenetre, elm_reso);

    /*Variables pour l'option "effet sonore"*/
    int index_effet = 0;
    char effet[15] = "Désactiver";

    /*Lecture de la musique en boucle*/
    Mix_PlayChannel(0,music,-1);

    /*Boucle principale*/
    int continuer = SDL_TRUE;
    while (continuer) {
        /*Récupération dimension fenêtre*/
        SDL_GetWindowSize(fenetre, &w, &h);
        /*Calcul ratio avec les dimensions récupérées*/
        float widthFactor = (float)w / WINDOW_WIDTH;
        float heightFactor = (float)h / WINDOW_HEIGHT;
        /*Gestion des événements*/
        SDL_Event evenement;
        while (SDL_PollEvent(&evenement) != 0) {
            switch(evenement.type){
                /*Fin de programme*/
                case SDL_QUIT:
                    continuer = SDL_FALSE;
                    break;
                
                /*Gestion du clic de la souris*/
                case SDL_MOUSEBUTTONDOWN:
                    mouseX = evenement.button.x;
                    mouseY = evenement.button.y;

                    /*Gestion des clics sur les menus*/
                    switch(etatMenu){

                        /*Vérifier si le clic est dans la zone du menu principal*/
                        case MENU_PRINCIPAL:
                            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;
                            menuY = (h - MENU_HEIGHT * heightFactor + MENU_DECALAGE) / 2;
                            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                                mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
                                /*Clic sur le menu principal, passer à l'état MENU_SOUS_JOUER*/
                                etatMenu = MENU_SOUS_JOUER;
                                //Bruit quand on clique sur l'élément
                                if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                }
                            }
                            break;
                        
                        /*Vérifier si le clic est dans la zone du sous-menu*/
                        case MENU_SOUS_JOUER:
                            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;  /*Position horizontale centrée pour le sous-menu*/
                            menuY = (h - (4 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2;  /*Position verticale centrée pour le sous-menu*/
                            
                            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) && 
                                mouseY >= menuY && mouseY <= menuY + 5 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                                /*Clic sur une option du sous-menu*/
                                if (mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
                                    //Clic sur l'option "Jouer"
                                    SDL_Log("Clic sur Jouer !");
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                }
                                
                                else if (mouseY >= menuY + ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                                    //Clic sur l'option "Reprendre une partie"
                                    SDL_Log("Clic sur Reprendre une partie !");
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                }
                                else if (mouseY >= menuY + 2 * ((MENU_HEIGHT  + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                                    //Clic sur l'option "Paramètres"
                                    SDL_Log("Clic sur Options !");
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    //Changer l'état du menu
                                    etatMenu = MENU_SOUS_OPTIONS;
                                }
                                else if (mouseY >= menuY + 3 * ((MENU_HEIGHT  + SPACING) * heightFactor) && mouseY <= menuY + 4 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                                    //Clique sur les crédits
                                    SDL_Log("Clic sur Crédits !");
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    //Change l'état du menu
                                    etatMenu = MENU_SOUS_CREDITS;
                                }
                                else if (mouseY >= menuY + 4 * ((MENU_HEIGHT  + SPACING) * heightFactor) && mouseY <= menuY + 5 * ((MENU_HEIGHT  + SPACING) * heightFactor) - SPACING) {
                                    //Clic sur l'option "Quitter"
                                    SDL_Log("Clic sur Quitter !");
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    continuer = SDL_FALSE;
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
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    etatMenu = MENU_SOUS_SON;
                                }
                                else if (mouseY >= menuY + ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                                    //Clic sur l'option "Résolution"
                                    SDL_Log("Clic sur Résolution !");
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    etatMenu = MENU_SOUS_RESOLUTION;
                                }
                                else if (mouseY >= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                                    // Clic sur l'option "Retour", revenir au menu précédent
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    etatMenu = MENU_SOUS_JOUER;
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
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    (*selecElement)++;
                                }
                                //Clique sur flèche de gauche
                                else if(mouseY <= menuY + (MENU_HEIGHT * heightFactor) && mouseX <= menuX){
                                    printf("--\n");
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
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
                                    if(!index_effet){
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
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    etatMenu = MENU_SOUS_OPTIONS;
                                }
                            }
                            break;

                        case MENU_SOUS_CREDITS:
                            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
                            menuY = (h - (MENU_HEIGHT * heightFactor)) / 2; //Position verticale

                            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                                mouseY >= menuY + 335 * heightFactor && mouseY <= menuY + (((MENU_HEIGHT - 20 + 335) * heightFactor))){
                                    //Bruit quand on clique sur l'élément
                                    if(!index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    etatMenu = MENU_SOUS_JOUER;
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
                                    if(index_effet == 0){
                                        strcpy(effet,"Activer");
                                        index_effet = 1;
                                    }
                                    else{
                                        strcpy(effet,"Désactiver");
                                        index_effet = 0;
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                }
                                else if(mouseY >= menuY + 3.1 * (MENU_HEIGHT * heightFactor) + SPACING && mouseY <= menuY + 4.4 * (MENU_HEIGHT * heightFactor)){
                                    if(!index_effet && !index_effet){
                                        Mix_PlayChannel(1, click, 0);
                                    }
                                    etatMenu = MENU_SOUS_OPTIONS;
                                }
                            }

                            break;

                        default : 
                            break;
                    }

                    break;

                case SDL_MOUSEBUTTONUP:
                    //Gestion du relachement du clique de la souris
                    if(etatMenu == MENU_SOUS_SON){
                        menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
                        menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

                        if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 && 
                            mouseY >= menuY && mouseY <= menuY + (30  * heightFactor)) {
                            // Arrêter de déplacer le curseur lorsque le bouton de la souris est relâché
                            estLache = SDL_FALSE;
                        }
                    }
                    break;


                case SDL_MOUSEMOTION:
                    // Déplacer le curseur si l'utilisateur déplace la souris tout en maintenant le bouton de la souris enfoncé
                    if (estLache) {
                        mouseX = evenement.motion.x;
                        if (mouseX < volumeBar->x) {
                            mouseX = volumeBar->x;
                        } else if (mouseX > volumeBar->x + (volumeBar->w - 14)) {
                            mouseX = volumeBar->x + (volumeBar->w - 14);
                        }
                        volume = ((mouseX - volumeBar->x) / 2) / widthFactor;
                        Mix_VolumeChunk(music, volume);
                        volumeCursor->x = mouseX;
                    }
                    break;

                default:
                    break;
                    
            }
        }

        
        /*Afficher l'image en fond*/
        SDL_RenderCopy(rendu, textureFond, NULL, NULL);

        /*Affiche le titre du jeu*/
        afficherTitre(rendu, police, fenetre, ((WINDOW_WIDTH - 800) / 2), ((WINDOW_HEIGHT - 1000) / 2), 800, 600);

        /*Afficher le menu en fonction de l'état*/
        if (etatMenu == MENU_PRINCIPAL) {
            menuX = (WINDOW_WIDTH - MENU_WIDTH ) / 2;
            menuY = (WINDOW_HEIGHT - (MENU_HEIGHT - MENU_DECALAGE) ) / 2;
            afficherMenu(rendu, police, fenetre, "Menu Principal", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
        }
        else if (etatMenu == MENU_SOUS_JOUER) {
            afficherSousMenu(rendu, police, fenetre, "Jouer", "Reprendre une partie", "Options", "Crédit","Quitter");
        }
        /*Ajouter l'affichage du sous-menu Paramètres*/
        else if (etatMenu == MENU_SOUS_OPTIONS) {
            afficherSousMenuOption(rendu, police, fenetre, "Musique / Son", "Résolution","Retour");
        }
        else if (etatMenu == MENU_SOUS_RESOLUTION) {
            afficherSousMenuResolution(rendu, police, fenetre);
            resolution(rendu, fenetre, police, elm_reso, selecElement);
        }
        else if (etatMenu == MENU_SOUS_CREDITS){
            afficherSousMenuCredits(rendu, fenetre, police);
        }
        else if(etatMenu == MENU_SOUS_SON){
            afficherSousMenuSon(rendu, police, fenetre, effet);
        }
       

        /*Amélioration antialiasing*/
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");

        /*Calculer le nombre de trames par seconde (FPS)*/
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 1000) {
            fps = frameCount * 1000.0f / (currentTime - lastTime);
            lastTime = currentTime;
            frameCount = 0;
        }

        /*Afficher le compteur de FPS*/
        char fpsText[20];
        sprintf(fpsText, "FPS: %0.f", fps);
        SDL_Color textColor = {0, 0, 0}; // Couleur blanche
        SDL_Surface* surface = TTF_RenderText_Solid(police_fps, fpsText, textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
        SDL_FreeSurface(surface);
        SDL_Rect fpsRect = {10, 10, 80, 25}; /*Position du texte*/
        SDL_RenderCopy(rendu, texture, NULL, &fpsRect);
        SDL_DestroyTexture(texture);

        /*Actualiser l'affichage*/
        SDL_RenderPresent(rendu);

        /*Incrémenter le compteur pour les fps*/
        frameCount++;

        /*Attendre un court instant (pour éviter une utilisation excessive du processeur)*/
        SDL_Delay(10);
    }

    /*Libérer les ressources*/
    free(selecElement);
    free(volumeBar);
    free(volumeCursor);
    SDL_DestroyTexture(textureFond);
    TTF_CloseFont(police);
    TTF_CloseFont(police_fps);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_FreeChunk(click);
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}