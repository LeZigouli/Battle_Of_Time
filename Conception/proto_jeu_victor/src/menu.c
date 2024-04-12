#include "lib/menu.h"


/***************/
/*--Fonctions--*/
/***************/
/*Gestion du clic de la souris sur les éléments du menu*/
void clic_menu(etatMenu_t* etatMenu, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, 
               int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, 
               int* continuer, int* selecElement, char* effet, int* isValid, const char* textInput, const char* ipPattern, 
               int* textInputActive, int* keyCounts, int x, int y, int* ancienSon, int* ancienReso)
{
    /*Gestion des clics sur les menus*/
    switch((*etatMenu)){

        /***** ****/
        /*--MENU--*/
        /**********/
        /*Vérifier si le clic est dans la zone de la page d'acceuil*/
        case PAGE_ACCUEIL:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;
            menuY = (h - MENU_HEIGHT * heightFactor + MENU_DECALAGE) / 2;

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)) {
                /*Clic sur le bouton "Menu Principale"*/
                (*etatMenu) = MENU_PRINCIPAL;
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                }
            }
            break;
        
        /*Vérifier si le clic est dans la zone du Menu Principale*/
        case MENU_PRINCIPAL:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;  /*Position horizontale centrée pour le sous-menu*/
            menuY = (h - (MENU_HEIGHT * heightFactor) + ((2 * SPACING) * heightFactor)) / 2;  /*Position verticale centrée pour le sous-menu*/
            
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) && 
                mouseY >= menuY - (MENU_HEIGHT * heightFactor) - (SPACING * heightFactor) && mouseY <= menuY + 5 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                /*Clic sur le bouton "Jouer"*/
                if (mouseY >= menuY - 0.8 * (MENU_HEIGHT * heightFactor) - SPACING * heightFactor && mouseY <= menuY - 1.4 * SPACING * heightFactor) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_JOUER;
                }
                /*Clic sur le bouton "Options"*/
                else if (mouseY >= menuY + ((SPACING/2) * heightFactor) && mouseY <= menuY + 0.9 * (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_OPTIONS;
                }
                /*Clic sur le bouton "Crédits"*/
                else if (mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_CREDITS;
                }
                /*Clic sur le bouton "Quitter"*/
                else if (mouseY >= menuY + 2.7 * (MENU_HEIGHT  * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 3.4 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Fin du programme et fermeture de la fenêtre*/
                    (*continuer) = SDL_FALSE;
                }
            }
            break;
        
        /*Vérifier si le clic est dans la zone du menu Options*/
        case MENU_SOUS_OPTIONS:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2;
            menuY = (h - (2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2;  /*Position verticale centrée pour le sous-menu*/
            
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                mouseY >= menuY && mouseY <= menuY + 3 * ((MENU_HEIGHT * heightFactor) + SPACING)) {
                /*Clic sur le bouton "Son"*/
                if (mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT  * heightFactor)) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*ancienSon) = MENU_SOUS_OPTIONS;
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_SON;
                }
                /*Clic sur le bouton "Résolution"*/
                else if (mouseY >= menuY + ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*ancienReso) = MENU_SOUS_OPTIONS;
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_RESOLUTION;
                }
                /*Clic sur le bouton "Retour"*/
                else if (mouseY >= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_PRINCIPAL;
                }
            }
            break;
        
        /*Vérifier si le clic est dans la zone du menu Résolution*/
        case MENU_SOUS_RESOLUTION:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale
            
            if (mouseX >= menuX - (MENU_WIDTH / 3) && mouseX <= menuX + (MENU_WIDTH * widthFactor) + (MENU_WIDTH / 3) &&
                mouseY >= menuY && mouseY <= menuY + ((MENU_HEIGHT * heightFactor) + SPACING)) {
                /*Clic sur la flèche de droite*/
                if (mouseY <= menuY + (MENU_HEIGHT * heightFactor) && mouseX >= menuX + (MENU_WIDTH * widthFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*On incrémente l'indice de sélection*/
                    (*selecElement)++;
                }
                /*Clic sur la flèche de gauche*/
                else if(mouseY <= menuY + (MENU_HEIGHT * heightFactor) && mouseX <= menuX){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*On décrémente l'indice de sélection*/
                    (*selecElement)--;
                }
                /*Création d'un système de boucle sans fin (quand on est sur le dernier élément on repasse au premier)*/
                if((*selecElement) >= 4){
                    (*selecElement) = 0;
                }
                else if((*selecElement) < 0){
                    (*selecElement) = 3;
                }
                /*Redimentionnement de la fenêtre en fonction de la résolution sélectionnée*/
                SDL_SetWindowSize(fenetre, elm_reso[(*selecElement)].w, elm_reso[(*selecElement)].h);
            }
            //Gestion des 2 boutons "Plein ecran" et "Retour"
            else if(mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                    mouseY >= menuY + 1.5 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3.5 * ((MENU_HEIGHT + SPACING) * heightFactor)){
                
                /*Clic sur le bouton "Plein Écran"*/
                if(mouseY >= menuY + 1.5 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2.5 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Mode fenêtré*/
                    if (SDL_GetWindowFlags(fenetre) & SDL_WINDOW_FULLSCREEN) {
                        SDL_SetWindowFullscreen(fenetre, 0);
                    /*Mode plein écran*/
                    } else {
                        SDL_SetWindowFullscreen(fenetre, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                }
                /*Clic que le bouton "Retour"*/
                else if(mouseY >= menuY + 2.5 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3.5 * ((MENU_HEIGHT + SPACING) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu en fonction de la page précédente*/
                    if((*ancienReso) == MENU_SOUS_OPTIONS){
                        (*etatMenu) = MENU_SOUS_OPTIONS;
                    }
                    else if((*ancienReso) == OPTION_JEU){
                        (*etatMenu) = OPTION_JEU;
                    } 
                }
            }
            break;

        /*Vérifier si le clic est dans la zone du menu Crédit*/   
        case MENU_SOUS_CREDITS:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - (MENU_HEIGHT * heightFactor)) / 2; //Position verticale

            /*Clic sur le bouton "Retour"*/
            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                mouseY >= menuY + 335 * heightFactor && mouseY <= menuY + (((MENU_HEIGHT - 20 + 335) * heightFactor))){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_PRINCIPAL;
                }
            break;
        
        /*Vérifier si le clic est dans la zone du menu Son*/   
        case MENU_SOUS_SON:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale
            

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY - MENU_HEIGHT && mouseY <= menuY + 4 * ((MENU_HEIGHT * heightFactor)) + SPACING) {
                /*Clic sur le curseur de volume*/
                if (mouseY >= menuY && mouseY <= menuY + (30  * heightFactor)) {
                    /*Détecter si l'utilisateur clique sur le curseur*/
                    if (evenement.button.button == SDL_BUTTON_LEFT &&
                        SDL_PointInRect(&(SDL_Point){evenement.button.x, evenement.button.y}, volumeCursor)){
                        estLache = SDL_TRUE;
                    }
                }
                /*Clic sur le bouton "Activer/Désactiver"*/
                else if(mouseY >= menuY + 2.1 * (MENU_HEIGHT * heightFactor) && mouseY <= menuY + 2.9 * (MENU_HEIGHT * heightFactor)){
                    /*Gestion de l'activation/désactivation du son*/
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
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + 3.1 * (MENU_HEIGHT * heightFactor) + SPACING && mouseY <= menuY + 4.4 * (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu en fonction de la page précédente*/
                    if((*ancienSon) == MENU_SOUS_OPTIONS){
                        (*etatMenu) = MENU_SOUS_OPTIONS;
                    }
                    else if((*ancienSon) == OPTION_JEU){
                        (*etatMenu) = OPTION_JEU;
                    }
                }
            }
            break;
        
        /*Vérifier si le clic est dans la zone du menu Jouer*/   
        case MENU_SOUS_JOUER:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY && mouseY <= menuY + 3 * (((MENU_HEIGHT + SPACING) * heightFactor)) + MENU_HEIGHT){
                /*Clic sur le bouton "Solo"*/
                if(mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'éat du menu*/
                    (*etatMenu) = MENU_SOUS_SOLO;
                }
                /*Clic sur le bouton "En ligne"*/
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_ENLIGNE;
                } 
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_PRINCIPAL;
                }
                }
            break;
        
        /*Vérifier si le clic est dans la zone du menu Solo*/   
        case MENU_SOUS_SOLO:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY && mouseY <= menuY + 3 * (((MENU_HEIGHT + SPACING) * heightFactor)) + MENU_HEIGHT){
                /*Clic sur le bouton "Nouvelle Partie"*/
                if(mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = JOUER;
                }
                /*Clic sur le bouton "Reprendre Partie"*/
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    
                } 
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_JOUER;
                }
            }
            break;

        /*Vérifier si le clic est dans la zone du menu En Ligne*/           
        case MENU_SOUS_ENLIGNE:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
                mouseY >= menuY && mouseY <= menuY + 3 * (((MENU_HEIGHT + SPACING) * heightFactor)) + MENU_HEIGHT){
                /*Clic sur le bouton "Créer Partie"*/
                if(mouseY >= menuY && mouseY <= menuY + (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                }
                /*Clic sur le bouton "Rejoindre Partie"*/
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état de menu*/
                    (*etatMenu) = MENU_SOUS_REJOINDRE;
                } 
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_JOUER;
                }
            }
            break;

        /*Vérifier si le clic est dans la zone du menu Rejoindre Partie*/           
        case MENU_SOUS_REJOINDRE:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX + (50 * widthFactor) && mouseX <= menuX + (180 * widthFactor) &&
                mouseY >= menuY + (135 * heightFactor) && mouseY <= menuY + (280 * heightFactor) ){
                
                /*Clic sur le bouton "Valider"*/
                if(mouseX >= menuX + (60 * widthFactor) && mouseX <= menuX + (160 * widthFactor) &&
                   mouseY >= menuY + (137 * heightFactor) && mouseY <= menuY + (178 * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Vérification de la l'adresse IP avec une regex*/
                    (*isValid) = validateRegex(textInput, ipPattern);
                    /*Désactivation de la saisie de texte*/
                    (*textInputActive) = SDL_FALSE;
                    /*Incrémentation du compteur */
                    (*keyCounts)++;
                }
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + (240 * heightFactor) && mouseY <= menuY + (290 * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Remet le compteur à 0*/
                    (*keyCounts) = 0;
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_ENLIGNE;
                }
            }
            break;


        /*********/
        /*--JEU--*/
        /*********/
        /*Vérifier si le clic est dans la zone du Jeu*/   
        case JOUER:
            /*Clic sur la roue crantée*/
            if(mouseX >= (WINDOW_WIDTH - 60) * widthFactor && mouseX <= (WINDOW_WIDTH - 10) * widthFactor &&
               mouseY >= 10 * heightFactor && mouseY <= 60 * heightFactor){
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                    Mix_PlayChannel(1, click, 0);
                }
                /*Changement d'état du menu*/
                (*etatMenu) = OPTION_JEU;
            }
            break;

        /*Vérifier si le clic est dans la zone du menu Option dans le jeu*/   
        case OPTION_JEU:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale
            
            if(mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * widthFactor) + 15 &&
               mouseY >= menuY - ((MENU_HEIGHT - 15) * heightFactor) && mouseY <= menuY + 4 * ((MENU_HEIGHT + SPACING) * heightFactor) - 5 * heightFactor){
                /*Clic sur le bouton 'Reprendre'*/
                if(mouseY >= menuY - ((MENU_HEIGHT - 15) * heightFactor) && mouseY <= menuY - 5 * heightFactor){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = JOUER;
                }
                /*Clic sur le bouton 'Sauvegarde'*/
                else if(mouseY >= menuY + (SPACING + 10 * heightFactor) && mouseY <= menuY + (((MENU_HEIGHT + SPACING) - 10) * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    //(*etatMenu) = ;
                }
                /*Clic sur le bouton 'Musique/Son'*/
                else if(mouseY >= menuY + ((MENU_HEIGHT + 2 * SPACING) + 10) * heightFactor && mouseY <= menuY + (( 2 * (MENU_HEIGHT + SPACING) - 10) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*ancienSon) = OPTION_JEU;
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_SON;
                    
                }
                /*Clic sur le bouton 'Résolution*/
                else if(mouseY >= menuY + ((2 * MENU_HEIGHT + 3 * SPACING) + 10) * heightFactor && mouseY <= menuY + (( 3 * (MENU_HEIGHT + SPACING) - 10) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*ancienReso) = OPTION_JEU;
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_SOUS_RESOLUTION;
                }
                else if(mouseY >= menuY + ((3 * MENU_HEIGHT + 4 * SPACING) + 10) * heightFactor && mouseY <= menuY + (( 4 * (MENU_HEIGHT + SPACING) - 10) * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etatMenu) = MENU_PRINCIPAL;
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
    /*Gestion du relachement du clique de la souris*/
    if((*etatMenu) == MENU_SOUS_SON){
        /*Calcul de la position de x et y*/
        menuX = (w - (MENU_WIDTH * (*widthFactor))) / 2; //Position horizontale
        menuY = (h - ((MENU_HEIGHT * (*heightFactor)) + (SPACING * (*heightFactor)))) / 2; //Position verticale

        if (mouseX >= menuX && mouseX <= menuX + (MENU_WIDTH * (*widthFactor)) + 15 && 
            mouseY >= menuY && mouseY <= menuY + (30  * (*heightFactor))) {
            /*Arrêter de déplacer le curseur lorsque le bouton de la souris est relâché*/
            estLache = SDL_FALSE;
        }
    }
}

/*Gestion du déplacement de la souris sur les éléments du menu*/
void deplacement_menu(Mix_Chunk* music, int mouseX, SDL_Event evenement, float* widthFactor)
{
    /*Déplacer le curseur si l'utilisateur déplace la souris tout en maintenant le bouton de la souris enfoncé*/
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
void destruction_menu(int* selecElement, int* index_effet, int* continuer, etatMenu_t* etatMenu, float* widthFactor, float* heightFactor, int* textInputActive, int* isValid, int* keyCounts, int* ancienSon, age_t* etatAge, int* ancienReso)
{
    /*Destruction des variables allouée dynamiquement*/
    free(textInputActive);
    free(isValid);
    free(keyCounts);
    free(selecElement);
    free(volumeBar);
    free(volumeCursor);
    free(ancienSon);
    free(ancienReso);
    free(etatAge);
    free(index_effet);
    free(continuer);
    free(etatMenu);
    free(widthFactor);
    free(heightFactor);
}

/*Fonction pour vérifier si une chaîne de caractères respecte une expression régulière*/
int validateRegex(const char *input, const char *pattern) 
{
    /*Déclaration d'une regex*/
    regex_t regex;
    int valid;

    /*Compilation de l'expression régulière*/
    valid = regcomp(&regex, pattern, REG_EXTENDED);
    if (valid) {
        printf("Erreur lors de la compilation de l'expression régulière\n");
        return -1;
    }

    /*Vérification si la chaîne de caractères correspond à l'expression régulière*/
    valid = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    return valid == 0 ? 1 : 0;
}

void touches_menu(SDL_Event evenement, int* textInputActive, int* keyCounts, int* isValid, char* textInput,const char* ipPattern)
{
    /*Si la saisie du texte est activée*/
    if ((*textInputActive)) {
        /*Si la saisie de texte est active, gérer les événements de saisie*/
        if (evenement.key.keysym.sym == SDLK_RETURN) {
            /*Incrémenter le compteur pour la touche appuyée*/
            (*keyCounts)++;
            (*textInputActive) = SDL_FALSE; /*Désactiver la saisie de texte*/
            /*Validation de l'adresse IP*/
            (*isValid) = validateRegex(textInput, ipPattern);
        }
        else if (evenement.key.keysym.sym == SDLK_BACKSPACE && strlen(textInput) > 0) {
            /*Effacer le dernier caractère si la touche BACKSPACE est enfoncée*/
            textInput[strlen(textInput) - 1] = '\0';
        }               
    }
    else{
        /*Saisie du texte activée en permanence*/
        (*textInputActive) = SDL_TRUE;
    }
}