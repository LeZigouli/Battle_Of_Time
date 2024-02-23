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
    /*Initialiser SDL*/
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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

    /*Créer une fenêtre*/
    SDL_Window* fenetre = SDL_CreateWindow("BATTLE OF TIME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!fenetre) {
        SDL_Log("Erreur lors de la création de la fenêtre : %s", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
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
        SDL_Quit();
        return 1;
    }

    /*Police pour le texte du menu*/
    TTF_Font* police = TTF_OpenFont("font/Handjet/Handjet-Bold.ttf", 60);  // Remplacez par le chemin de votre police
    if (!police) {
        SDL_Log("Erreur lors du chargement de la police : %s", TTF_GetError());
        SDL_DestroyTexture(textureFond);
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fenetre);
        TTF_Quit();
        IMG_Quit();
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
            SDL_Quit();
            return 1;
    }

    TTF_SetFontHinting(police_fps, TTF_HINTING_LIGHT_SUBPIXEL);
    

    /*Tableau de résolutions disponibles*/
    //const char* resolutions[] = {"800x600", "1024x768", "1280x720"};


    /*Etat initial du menu*/
    enum MenuState etatMenu = MENU_PRINCIPAL;


    /*Variables pour le compteur de FPS*/
    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    Uint32 frameCount = 0;
    float fps = 0.0f;

    /*Pour le soulignage */
    SDL_Point ligne = {100, 100};

    /*Création du menu principale*/
    MenuItem* menu = creerMenu(fenetre, "Jouer", "Reprendre Partie", "Options", "Credits", "Quitter");

    /*Variables pour la gestion de la souris*/
    int menuX;
    int menuY;
    int mouseX;
    int mouseY;

    /*Pointeur pour récupérer la largeur et la hauteur de la fenêtre
    int * w = malloc(sizeof(int));
    int * h = malloc(sizeof(int));
    */
   int w;
   int h;

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
                            }
                            break;
                        
                        /*Vérifier si le clic est dans la zone du sous-menu*/
                        case MENU_SOUS_JOUER:
                            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;  /*Position horizontale centrée pour le sous-menu*/
                            menuY = (h - (4 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2;  /*Position verticale centrée pour le sous-menu*/
                            
                            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) && 
                                mouseY >= menuY && mouseY <= menuY + 5 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                                /*Clic sur une option du sous-menu*/
                                if (mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
                                    /*Clic sur l'option "Jouer"*/
                                    SDL_Log("Clic sur Jouer !");
                                }
                                else if (mouseY <= menuY + 2 * ((MENU_HEIGHT  + SPACING) * heightFactor)) {
                                    /*Clic sur l'option "Reprendre une partie"*/
                                    SDL_Log("Clic sur Reprendre une partie !");
                                }
                                else if (mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor)) {
                                    /*Clic sur l'option "Paramètres"*/
                                    SDL_Log("Clic sur Options !");
                                    /*Changer l'état du menu*/
                                    etatMenu = MENU_SOUS_PARAMETRES;
                                }
                                else if (mouseY <= menuY + 4 * ((MENU_HEIGHT + SPACING) * heightFactor)) {
                                    /*Clique sur les crédits*/
                                    SDL_Log("Clic sur Quitter !");
                                }
                                else if (mouseY <= menuY + 5 * ((MENU_HEIGHT + SPACING) * heightFactor)) {
                                    /*Clic sur l'option "Quitter"*/
                                    SDL_Log("Clic sur Quitter !");
                                    continuer = SDL_FALSE;
                                    
                                    
                
                                    
                                    /*Mise en plein écran
                                    SDL_Log("Clic sur FULLSCREEN !");
                                    if (SDL_GetWindowFlags(fenetre) & SDL_WINDOW_FULLSCREEN) {
                                        SDL_SetWindowFullscreen(fenetre, 0); //Mode fenêtré
                                    } else {
                                        SDL_SetWindowFullscreen(fenetre, SDL_WINDOW_FULLSCREEN_DESKTOP); //Plein écran
                                    }*/
                                }
                            }
                            break;
                        
                        /*Vérifier si le clic est dans la zone du sous-menu Paramètres*/
                        case MENU_SOUS_PARAMETRES:
                            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;
                            menuY = (h - (4 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2;  /*Position verticale centrée pour le sous-menu*/
                            
                            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                                mouseY >= menuY && mouseY <= menuY + 5 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                                /*Clic sur une option du sous-menu Paramètres*/
                                if (mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
                                    /*Clic sur l'option "Musique"*/
                                    SDL_Log("Clic sur Musique !");
                                }
                                else if (mouseY <= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor)) {
                                    /*Clic sur l'option "Option 2", vous pouvez ajouter le code pour gérer cela ici*/
                                    SDL_Log("Clic sur Effets Sonores!");
                                }
                                else if (mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor)) {
                                    // Clic sur l'option "Option 3", vous pouvez ajouter le code pour gérer cela ici
                                    SDL_Log("Clic sur Tout Désactiver !");
                                }
                                else if (mouseY <= menuY + 4 * ((MENU_HEIGHT + SPACING) * heightFactor)) {
                                    /*Clic sur l'option "Résolution"*/
                                    SDL_Log("Clic sur Résolution !");
                                    etatMenu = MENU_SOUS_RESOLUTION;
                                }
                                else if (mouseY <= menuY + 5 * ((MENU_HEIGHT + SPACING) * heightFactor)) {
                                    // Clic sur l'option "Retour", revenir au menu précédent
                                    etatMenu = MENU_SOUS_JOUER;
                                }
                            }
                            break;
                        
                        case MENU_SOUS_RESOLUTION:
                            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;
                            menuY = (h - MENU_HEIGHT * heightFactor + MENU_DECALAGE) / 2;

                            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                                mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
  
                                if(mouseY <= menuY + (MENU_HEIGHT  * heightFactor)) {
                                    /*Clic sur l'option "Retour" */
                                    etatMenu = MENU_SOUS_PARAMETRES;
                                }                                 

                            }
                            break;

                        default : 
                            break;
                    }
                    //là

                    break;
                
                case SDL_MOUSEMOTION:
                    mouseX = evenement.motion.x;
                    mouseY = evenement.motion.y;
                    // Vérifier si la souris survole un élément du menu
                    for (int i = 0; i < 3; ++i) {
                        if (mouseX >= menuX && mouseX <= menu[i].rect.x + menu[i].rect.w &&
                            mouseY >= menu[i].rect.y && mouseY <= menu[i].rect.y + menu[i].rect.h) {
                            ligneHorizontale()
                        } else {
                            SDL_SetRenderDrawColor(rendu, 255, 255, 255, SDL_ALPHA_OPAQUE);
                        }
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
            afficherSousMenu(rendu, police, fenetre, "Jouer", "Reprendre une partie", "Options", "Credit","Quitter");
        }
        /*Ajouter l'affichage du sous-menu Paramètres*/
        else if (etatMenu == MENU_SOUS_PARAMETRES) {
            afficherSousMenu(rendu, police, fenetre, "Musique", "Effet sonore", "Tout desactiver", "Resolution","Retour");
        }
        else if (etatMenu == MENU_SOUS_RESOLUTION) {
            menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  
            menuY = (WINDOW_HEIGHT - (MENU_HEIGHT - MENU_DECALAGE)) / 2;
            afficherMenu(rendu, police, fenetre, "Retour", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
            //afficherSousMenuResolution(rendu, menuItems, police, fenetre, "", "RETOUR", currentItemIndex);
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
    free(menu);
    SDL_DestroyTexture(textureFond);
    TTF_CloseFont(police);
    TTF_CloseFont(police_fps);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}