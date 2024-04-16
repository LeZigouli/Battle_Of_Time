/*
 * Projet Battle Of Time
 * Le 28 janvier 2024, 17:00
*/

/**************/
/*--Includes--*/
/**************/
#include "../lib/affichage_menu.h"
#include "../lib/gestion.h"
#include "../lib/ordinateur.h"
#include "../lib/help.h"
#include "../lib/commun_SDL.h"
#include "../socket/serveur.h"
#include "../socket/client.h"


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
    /*Police texte*/
    TTF_Font* police_texte = chargementPolice(rendu, fenetre, textureFond, "font/Handjet/Handjet-Medium.ttf", 60);
    TTF_SetFontHinting(police_texte, TTF_HINTING_NORMAL); 

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
    etat_t* etat = malloc(sizeof(etat_t));
    /*Initialisation de l'état du menu*/
    (*etat) = PAGE_ACCUEIL;

    /*État actuel de l'age*/
    int* etatAge = malloc(sizeof(int));
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

    int* cameraX = malloc(sizeof(int));
    (*cameraX) = 0;
    int* cameraY = malloc(sizeof(int));;
    (*cameraY) = 0;


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



    
    /**********/
    /*-Images-*/
    /**********/
    /*Chargement des images pour l'HUD*/
    SDL_Texture* parametre = chargementImg(rendu, fenetre, "img/HUD/parametre.png");
    SDL_Texture* upgrade = chargementImg(rendu, fenetre, "img/HUD/upgrade.png");
    SDL_Texture* gold = chargementImg(rendu, fenetre, "img/HUD/gold.png");
    SDL_Texture* xp = chargementImg(rendu, fenetre, "img/HUD/xp.png");
    SDL_Texture* ultim = chargementImg(rendu, fenetre, "img/HUD/ultimate.png");

    /*Chargement des imges d'arrière plan*/
    SDL_Texture* prehistoire = chargementImg(rendu, fenetre, "img/Fond/Préhistoire_v2.jpg");
    SDL_Texture* antiquite = chargementImg(rendu, fenetre, "img/Fond/Antiquité_v2.jpg");
    SDL_Texture* moyen_age = chargementImg(rendu, fenetre, "img/Fond/Moyen-Âge_v2.jpg");
    SDL_Texture* moderne = chargementImg(rendu, fenetre, "img/Fond/Moderne_v2.jpg");
    SDL_Texture* futuriste = chargementImg(rendu, fenetre, "img/Fond/Futuriste_v2.jpg");

    /*Chargement des images des sprites pour l'HUD*/
    SDL_Texture* sprite_hud[20] = {chargementImg(rendu, fenetre, "img/sprite/Préhistoire/melee_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Préhistoire/marksman_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Préhistoire/tank_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Préhistoire/specialist_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Antiquité/melee_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Antiquité/marksman_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Antiquité/tank_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Antiquité/specialist_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Moyen age/melee_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Moyen age/marksman_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Moyen age/tank_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Moyen age/specialist_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere moderne/melee_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere moderne/marksman_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere moderne/tank_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere moderne/specialist_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere futuriste/melee_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere futuriste/marksman_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere futuriste/tank_img.png"),
                                   chargementImg(rendu, fenetre, "img/sprite/Ere futuriste/specialist_img.png")
                                   };
                                
    SDL_Texture* building[10] = {chargementImg(rendu, fenetre, "img/Base/grotte.png"),
                               chargementImg(rendu, fenetre, "img/Base/grotte_ad.png"),
                               chargementImg(rendu, fenetre, "img/Base/base.png"),
                               chargementImg(rendu, fenetre, "img/Base/base_ad.png"),
                               chargementImg(rendu, fenetre, "img/Base/chateau.png"),
                               chargementImg(rendu, fenetre, "img/Base/chateau_ad.png"),
                               chargementImg(rendu, fenetre, "img/Base/base_militaire.png"),
                               chargementImg(rendu, fenetre, "img/Base/base_militaire_ad.png"),
                               chargementImg(rendu, fenetre, "img/Base/base_futuriste.png"),
                               chargementImg(rendu, fenetre, "img/Base/base_futuriste_ad.png")};

    /*****************/
    /*-Variables jeu-*/
    /*****************/
    int attaque = 0;
    int nb_attaque = 1;
    int* upgarde_j = malloc(sizeof(int));
    (*upgarde_j) = 0;
    int i;

    int resize = 1; //entier qui sert a définir si le sprite a été redimensionné (car les animations sont de taille différentes)
    //SDL_Rect playerPosition = {100, 100, 128, 128}; // position et taille du sprite sur l'écran
    Uint32 lastMovement = 0; //dernier mouvement du sprite

    SDL_Rect playerImg = {TAILLE_SPRITE*0 , TAILLE_SPRITE*11, TAILLE_SPRITE*1, TAILLE_SPRITE*1};   //position sur le png avec tous les sprite
    SDL_Rect ordiImg = {TAILLE_SPRITE*0 , TAILLE_SPRITE*9, TAILLE_SPRITE*1, TAILLE_SPRITE*1};
    SDL_Rect playerPosition[MAX_POSSESSED]; // position et taille du sprite sur l'écran
    SDL_Rect ordiPosition[MAX_POSSESSED];

    character_t * tab_de_charactere = initcharacter();
    player_t * j1 = initplayer(OWNER_1);; 
    ordi_t * o = init_ordi(); 

    SDL_Texture* image[8]={IMG_LoadTexture(rendu,tab_de_charactere[Prehistoire+melee].sprite),
                           IMG_LoadTexture(rendu,tab_de_charactere[Prehistoire+marksman].sprite),
                           IMG_LoadTexture(rendu,tab_de_charactere[Prehistoire+tank].sprite),
                           IMG_LoadTexture(rendu,tab_de_charactere[Prehistoire+specialist].sprite),
                           NULL,NULL,NULL,NULL};



    SDL_Texture* img_char[MAX_POSSESSED];
    SDL_Texture * img_c_ordi[MAX_POSSESSED];

    /*Récupération dimension fenêtre*/
    SDL_GetWindowSize(fenetre, &w, &h);

    for( i= 0; i < MAX_POSSESSED; i++){
        playerPosition[i].x = POS_DEP;
        playerPosition[i].w = 128;
        playerPosition[i].h = 128;
        ordiPosition[i].x = POS_DEP_AD;
        ordiPosition[i].w = 128;
        ordiPosition[i].h = 128;
        
    }

    /* reseau */
    int connection_reussi = FALSE;

    /*********************/
    /*-Boucle Principale-*/
    /*********************/
    int* continuer = malloc(sizeof(int));
    (*continuer) = SDL_TRUE;
    while ((*continuer)) {
        Uint32 currentTime = SDL_GetTicks();

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
                    clic(etat, fenetre, evenement, elm_reso, click, mouseX, mouseY, w, h, 
                              (*widthFactor), (*heightFactor), menuX, menuY, index_effet, continuer, 
                              selecElement, effet, isValide, textInput, ipPattern, textInputActive, keyCounts,
                              x, y, ancienSon, ancienReso, j1, upgarde_j, tab_de_charactere, o);
                    break;

                /*Gestion du relachement du clic de la souris*/
                case SDL_MOUSEBUTTONUP:

					/*Gestion du relachement du clique de la souris sur les éléments du menu*/
                	relachement(etat, menuX, menuY, w, h, widthFactor, heightFactor, mouseX, mouseY);
                    break;
                
                /*Gestion du déplacement de la souris*/
                case SDL_MOUSEMOTION:
                
					/*Gestion du déplacement de la souris sur les éléments du menu*/
				   	deplacement_souris(music, mouseX, evenement, widthFactor);
                	break;

                /*Gestion des touches du clavier*/
                case SDL_KEYDOWN:
                    
                    /*Gestion des touches pour l'adresse IP*/
                    touches(evenement, textInputActive, keyCounts, isValide, textInput, ipPattern, &connection_reussi);
                    if ( connection_reussi )
                    {
                        (*etat) = JOUER_RESEAU_REJOINDRE;
                    }
                    break;

                /*Gestion du texte saisie*/
                case SDL_TEXTINPUT:

                    /*Gérer les événements de texte saisi*/
                    if ((*textInputActive) && strlen(textInput) + strlen(evenement.text.text) < sizeof(textInput)) {
                        /*Ajouter le texte saisi au buffer*/
                        strcat(textInput, evenement.text.text);
                    }
                    break;



                case SDLK_a: //on appuie sur A pour attaquer/ne plus attaquer 
                    attaque = !attaque;
                    break;


                default:
                    break;

                    
            }
        }
        
        /*Afficher l'image du menu*/
        SDL_RenderCopy(rendu, textureFond, NULL, NULL);

        /*Gestion de l'affichage en fonction de l'état*/
        affichage((*etat), etatAge,rendu, fenetre, police, police_texte, menuX, menuY, elm_reso, selecElement, 
                  effet, textInput, isValide, keyCounts, parametre, gold, xp, prehistoire, antiquite,
                  moyen_age, moderne, futuriste, j1, sprite_hud, upgrade, o, cameraX, cameraY, ultim, building, j1->building->pv, o->building->pv);
        
    
        /*On appelle les fonctions du jeu si on est dans une partie*/
        if((*etat) == JOUER){
            
            envoie_char(&j1);
            jeu_ordi(o,j1,tab_de_charactere);
            //afficher_player(j1);
            affichageSprite(rendu, j1, o, &playerImg, &ordiImg, attaque, playerPosition, ordiPosition, upgarde_j, 
                            tab_de_charactere, image, img_char, img_c_ordi, currentTime, &lastMovement, w, h, cameraX, cameraY);
        }

        if ( (*etat) == JOUER_RESEAU_REJOINDRE )
        {
            printf("Je joue en reseau !\n");
        }
            
        /*================ RESEAU INITIALISATION ================*/
        /* si le choix était de creer une partie */
        /* et que on a pas deja reussi une connection */
        
        /*=======================================================*/
        /* jeu */
        /*=============== RESEAU ENVOIE/RECEPTION ===============*/
        // envoyer_structure()
        // recevoir_structure()
        /*=======================================================*/
        /* traitement */

    

        /*Amélioration antialiasing*/
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");

        /*Actualiser l'affichage*/
        SDL_RenderPresent(rendu);

        /*Limite le processeur*/
        SDL_Delay(16);
    }

    /*Libérer les ressources*/

	/*Destruction des éléments du menu*/
	destruction(selecElement, index_effet, continuer, etat, widthFactor, heightFactor, textInputActive, isValide, keyCounts, ancienSon, etatAge, ancienReso);
    free(upgarde_j);

    /*================ RESEAU ================*/

    /*========================================*/

    destroy_tab_character(&tab_de_charactere);
    destroy_player(&j1);
    detr_ordi(&o);
    /*****************************/
    /*-Libération des ressources-*/
    /*****************************/

    free(cameraX);
    free(cameraY);
    

    destruction_SDL(parametre, gold, xp, textureFond, prehistoire, antiquite, moyen_age,
                    moderne, futuriste, police, police_texte, rendu, fenetre, click, music, sprite_hud,
                    building);

    return EXIT_SUCCESS;
}