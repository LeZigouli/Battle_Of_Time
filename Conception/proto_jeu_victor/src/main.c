/*
 * Projet Battle Of Time
 * Le 28 janvier 2024, 17:00
*/

/**************/
/*--Includes--*/
/**************/
#include "lib/affichage_menu.h"
#include "lib/menu.h"


/*************************/
/*--Programme Principal--*/
/*************************/
int main(int argc, char* argv[]) {
    
    /*Initialisation des modules SDL*/
    if(initialisation() == 1){
        return 1;
    }

    /*Créer une fenêtre*/
    SDL_Window* fenetre = SDL_CreateWindow("BATTLE OF TIME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                           WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    /*Chargement de l'image de fond du menu*/
    SDL_Texture* textureFond = chargementImg(rendu, fenetre, "img/Fond/Fond_menu.png");
    

    /**********/
    /*-Police-*/
    /**********/
    /*Police principale*/
    TTF_Font* police = chargementPolice(rendu, fenetre, textureFond, "font/Handjet/Handjet-SemiBold.ttf", 60);
    TTF_SetFontHinting(police, TTF_HINTING_NORMAL); 


    /***********/
    /*-Musique-*/
    /***********/
    Mix_AllocateChannels(2); // Allouer 2 cannaux 
    Mix_Volume(0, volume); // Met le son a 50% en volume pour le premier cannaux
    Mix_Volume(1, MIX_MAX_VOLUME); // Met le son a 100% en volume pour le deuxièmme cannaux 

    /*Chargement son du clique de la souris*/
    Mix_Chunk* click = chargementAudio(rendu, fenetre, textureFond, "sound/click.mp3");

    /*Chargement musique */
    Mix_Chunk* music = chargementAudio(rendu, fenetre, textureFond, "sound/music.mp3");

    /*****************/
    /*-Variables SDL-*/
    /*****************/
    /*État actuel du menu*/
    etatMenu_t* etatMenu = malloc(sizeof(etatMenu_t));
    /*Initialisation de l'état du menu*/
    (*etatMenu) = PAGE_ACCUEIL;

    /*État actuel de l'age*/
    age_t* etatAge = malloc(sizeof(age_t));
    (*etatAge) = Prehistoire;

    /*Variables pour la gestion de la souris*/
    int menuX = 0;
    int menuY = 0;
    int mouseX;
    int mouseY;
    /*Calcul du milieu de l'écran*/
    int x = WINDOW_WIDTH / 2;
    int y = WINDOW_HEIGHT / 2;

    /*Variables pour le redimensionnement dynamique de la fenêtre*/
    int w;
    int h;

    /*Bloc d'instructions pour le menu de résolution*/
    element_t elm_reso[4];
    int* selecElement = malloc(sizeof(int)) ; //Indice de l'élément sélectionné
    (*selecElement) = 2;
    initElements(rendu, fenetre, elm_reso); //Initialisation des éléments pour le sous-menu de résolution
    int* ancienReso = malloc(sizeof(int));
    (*ancienReso) = MENU_SOUS_OPTIONS;

    /*Variables pour l'option "effet sonore"*/
    int* index_effet = malloc(sizeof(int)); 
    (*index_effet) = 0;
    char effet[15] = "Désactiver";
    int* ancienSon = malloc(sizeof(int));
    (*ancienSon) = MENU_SOUS_OPTIONS;

    /*Lecture de la musique en boucle*/
    //Mix_PlayChannel(0,music,-1);

	/*Variables pour le calcul du ration de la dimension de la fenêtre*/
    float* widthFactor = malloc(sizeof(float));
    float* heightFactor = malloc(sizeof(float)); 


    /*Variables pour la saisie de texte*/
    char textInput[16] = ""; //Buffer pour stocker le texte saisi
    int* textInputActive = malloc(sizeof(int));
    (*textInputActive) = SDL_TRUE; // Booléen pour indiquer si la saisie de texte est active
    /*Expression régulière pour vérifier une adresse IP*/
    const char *ipPattern = "^([0-9]{1,3}\\.){3}[0-9]{1,3}$";
    int* isValide = malloc(sizeof(int));
    (*isValide) = SDL_FALSE; // Booléen pour indiquer si l'adresse IP est valide
    /*Variable pour stocker le nombre de fois que la touche 'Enter' a été appuyée*/
    int* keyCounts = malloc(sizeof(int));
    (*keyCounts) = 0;


    /*********************/
    /*-Boucle Principale-*/
    /*********************/
    int* continuer = malloc(sizeof(int));
    (*continuer) = SDL_TRUE;
    while ((*continuer)) {
        /*Récupération dimension fenêtre*/
        SDL_GetWindowSize(fenetre, &w, &h);

        /*Calcul ratio avec les dimensions récupérées*/
		(*widthFactor) = (float)w / WINDOW_WIDTH;
		(*heightFactor) = (float)h / WINDOW_HEIGHT;

        /*Gestion des événements*/
        SDL_Event evenement;
        while (SDL_PollEvent(&evenement) != 0) {
            switch(evenement.type){
                /*Fin de programme*/
                case SDL_QUIT:
                    (*continuer) = SDL_FALSE;
                    break;
                
                /*Gestion du clic de la souris*/
                case SDL_MOUSEBUTTONDOWN:
                    /*Récupération des coordonnées de la souris*/
                    mouseX = evenement.button.x;
                    mouseY = evenement.button.y;

					/*Gestion des cliquable sur les éléments du menu*/
                    clic_menu(etatMenu, fenetre, evenement, elm_reso, click, mouseX, mouseY, w, h, 
                              (*widthFactor), (*heightFactor), menuX, menuY, index_effet, continuer, 
                              selecElement, effet, isValide, textInput, ipPattern, textInputActive, keyCounts,
                              x, y, ancienSon, ancienReso);
                    break;

                /*Gestion du relachement du clic de la souris*/
                case SDL_MOUSEBUTTONUP:

					/*Gestion du relachement du clique de la souris sur les éléments du menu*/
                	relachement_menu(etatMenu, menuX, menuY, w, h, widthFactor, heightFactor, mouseX, mouseY);
                    break;
                
                /*Gestion du déplacement de la souris*/
                case SDL_MOUSEMOTION:
                
					/*Gestion du déplacement de la souris sur les éléments du menu*/
				   	deplacement_menu(music, mouseX, evenement, widthFactor);
                	break;

                /*Gestion des touches du clavier*/
                case SDL_KEYDOWN:
                    
                    /*Gestion des touches pour l'adresse IP*/
                    touches_menu(evenement, textInputActive, keyCounts, isValide, textInput, ipPattern);
                    break;

                /*Gestion du texte saisie*/
                case SDL_TEXTINPUT:

                    /*Gérer les événements de texte saisi*/
                    if ((*textInputActive) && strlen(textInput) + strlen(evenement.text.text) < sizeof(textInput)) {
                        /*Ajouter le texte saisi au buffer*/
                        strcat(textInput, evenement.text.text);
                    }
                    break;

                default:
                    break;

                    
            }
        }

        
        /*Afficher l'image du menu*/
        SDL_RenderCopy(rendu, textureFond, NULL, NULL);


        /*Gestion de l'affichage en fonction de l'état*/
        affichage((*etatMenu), (*etatAge),rendu, fenetre, police, menuX, menuY, elm_reso, selecElement, effet, textInput, isValide, keyCounts);



        /*Amélioration antialiasing*/
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");

        /*Actualiser l'affichage*/
        SDL_RenderPresent(rendu);

    }

    /*Libérer les ressources*/

	/*Destruction des éléments du menu*/
	destruction_menu(selecElement, index_effet, continuer, etatMenu, widthFactor, heightFactor, textInputActive, isValide, keyCounts, ancienSon, etatAge, ancienReso);

    /*****************************/
    /*-Libération des ressources-*/
    /*****************************/
    SDL_DestroyTexture(textureFond);
    TTF_CloseFont(police);
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