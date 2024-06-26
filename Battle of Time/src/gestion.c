/**
 * \file gestion.c
 * \brief Contient les fonction permettant la gestion des inputs et certaines fonctions pour le deroulement de la partie.
 * \author Poirier Victor
 * \date 09 avril 2024
 * \version 1.0
*/
#include "../lib/gestion.h"

/**
 * \fn void clic(etat_t* etat, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, 
          int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, 
          int* continuer, int* selecElement, char* effet, int* isValid, const char* textInput, const char* ipPattern, 
          int* textInputActive, int* keyCounts, int x, int y, int* ancienSon, int* ancienReso, player_t* j1,
          character_t* tab_de_charactere, ordi_t* ordi, Uint32 currentTime, Uint32* lastUlti, Uint32* diff_time, Uint32* delai_ulti,
          int** troupe_formee, Uint32** lastTroupe, int** nb, int * reseau_action, int * reseau_action2, int age, player_t * j2_distant)
 * \brief Gestion des cliques du menu et du jeu 
 * 
 * \param etat L'etat actuel du menu
 * \param fenetre La fenetre du programme
 * \param evenement Les evenements SDL
 * \param elm_reso Un pointeurs sur un element du menu
 * \param click Son d'un clic
 * \param mouseX La position du pointeur de la souris en X
 * \param mouseY La position du pointeur de la souris en Y
 * \param w La longueur de la fenêtre
 * \param h La largeur de la fenêtre
 * \param widthFactor Un coefficient pour la longueur de la fenetre
 * \param heightFactor Un coefficient pour la largeur de la fenetre
 * \param menuX La position X des elements dans le menu
 * \param menuY La position Y des elements dans le menu
 * \param index_effet Choisir une résoltion
 * \param continuer Arret du programme si il est mis a FAUX
 * \param selecElement L'élement selectionné
 * \param effet Effet sonore
 * \param isValid Pointeur vers la validité de la saisie de texte.
 * \param textInput La chaîne de caractères saisie
 * \param ipPattern Le motif de l'expression régulière pour une adresse IP.
 * \param textInputActive Pointeur vers l'état de la saisie de texte
 * \param keyCounts Pointeur vers le nombre de touches pressées
 * \param x Position en X
 * \param y Position Y
 * \param ancienSon L'anacien son
 * \param ancienReso L'ancienne resolution
 * \param j1 Un pointeur sur joueur
 * \param tab_de_charactere Un tableau de personnage
 * \param ordi Un pointeur sur ordinateur
 * \param currentTime temps actuel
 * \param lastUlti Temps depuis le dernier ulti
 * \param diff_time différence de temps
 * \param delai_ulti Delai de l'ulti
 * \param troupe_formee tableau de troupe formee
 * \param lastTroupe temps derniere troupe donnée
 * \param nb tableau de nombre
 * \param reseau_action pointeur sur un entier pour le mode reseau
 * \param reseau_action2 pointeur sur un entier pour le mode reseau
 * \param age age actuel du jeu
 * \param j2_distant pointeur sur un joueur en mode reseau
 */
void clic(etat_t* etat, SDL_Window* fenetre, SDL_Event evenement, element_t* elm_reso, Mix_Chunk* click, 
          int mouseX, int mouseY, int w, int h, float widthFactor, float heightFactor, int menuX, int menuY, int* index_effet, 
          int* continuer, int* selecElement, char* effet, int* isValid, const char* textInput, const char* ipPattern, 
          int* textInputActive, int* keyCounts, int x, int y, int* ancienSon, int* ancienReso, player_t* j1,
          character_t* tab_de_charactere, ordi_t* ordi, Uint32 currentTime, Uint32* lastUlti, Uint32* diff_time, Uint32* delai_ulti,
          int** troupe_formee, Uint32** lastTroupe, int** nb, int * reseau_action, int * reseau_action2, int age, player_t * j2_distant)
{
    /*Gestion des clics sur les menus*/
    switch((*etat)){

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
                (*etat) = MENU_PRINCIPAL;
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
                    (*etat) = MENU_SOUS_JOUER;
                }
                /*Clic sur le bouton "Options"*/
                else if (mouseY >= menuY + ((SPACING/2) * heightFactor) && mouseY <= menuY + 0.9 * (MENU_HEIGHT * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_OPTIONS;
                }
                /*Clic sur le bouton "Crédits"*/
                else if (mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_CREDITS;
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
                    (*etat) = MENU_SOUS_SON;
                }
                /*Clic sur le bouton "Résolution"*/
                else if (mouseY >= menuY + ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*ancienReso) = MENU_SOUS_OPTIONS;
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_RESOLUTION;
                }
                /*Clic sur le bouton "Retour"*/
                else if (mouseY >= menuY + 2 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) - SPACING) {
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_PRINCIPAL;
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
                        (*etat) = MENU_SOUS_OPTIONS;
                    }
                    else if((*ancienReso) == OPTION_JEU){
                        (*etat) = OPTION_JEU;
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
                    (*etat) = MENU_PRINCIPAL;
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
                        (*etat) = MENU_SOUS_OPTIONS;
                    }
                    else if((*ancienSon) == OPTION_JEU){
                        (*etat) = OPTION_JEU;
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
                    (*etat) = MENU_SOUS_SOLO;
                }
                /*Clic sur le bouton "En ligne"*/
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_ENLIGNE;
                } 
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_PRINCIPAL;
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
                    (*etat) = MENU_DIFFICULTE;
                }
                /*Clic sur le bouton "Reprendre Partie"*/
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = JOUER_CHARGER;

                    
                } 
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_JOUER;
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
                    (*etat) = MENU_SOUS_CREER;
                }
                /*Clic sur le bouton "Rejoindre Partie"*/
                else if(mouseY >= menuY + 1.2 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor) && mouseY <= menuY + 1.8 * (MENU_HEIGHT * heightFactor) + (SPACING * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état de menu*/
                    (*etat) = MENU_SOUS_REJOINDRE;
                } 
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) && mouseY <= menuY + 3 * ((MENU_HEIGHT + SPACING) * heightFactor) + MENU_HEIGHT){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_JOUER;
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
                    (*etat) = MENU_SOUS_CREER_VALIDE;
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
                    (*etat) = MENU_SOUS_ENLIGNE;
                }
            }
            break;

        /*Vérifier si le clic est dans la zone du menu Difficulté*/
        case MENU_DIFFICULTE:
            /*Calcul de la position de x et y*/
            menuX = (w - (MENU_WIDTH * widthFactor)) / 2; //Position horizontale
            menuY = (h - ((MENU_HEIGHT * heightFactor) + (SPACING * heightFactor))) / 2; //Position verticale

            if (mouseX >= menuX  && mouseX <= menuX + (MENU_WIDTH * widthFactor) &&
                mouseY >= menuY && mouseY <= menuY + (((4 * MENU_HEIGHT) + (3 * SPACING))  * heightFactor) ){
                /*Clic sur le bouton "Facile"*/
                if(mouseY >= menuY + (10 * heightFactor) && mouseY <= menuY + ((MENU_HEIGHT - 10) * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                      Mix_PlayChannel(1, click, 0);
                    }
                    /*Modifie la difficulté*/
                    j1->gold = 800;
                    ordi->difficulte = EASY;
                    (*etat) = JOUER;
                    (*lastUlti) = currentTime;
                }
                /*Clic sur le bouton "Moyen"*/
                else if(mouseY >= menuY + (((MENU_HEIGHT - 10) + SPACING) * heightFactor) && mouseY <= menuY + ((2 * MENU_HEIGHT + SPACING) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Modifie la difficulté*/
                    j1->gold = 600;
                    ordi->difficulte = MEDIUM;
                    (*etat) = JOUER;
                    (*lastUlti) = currentTime;
                }
                /*Clic sur le bouton "Difficile"*/
                else if(mouseY >= menuY + ((2 * (MENU_HEIGHT) + 2 * SPACING) * heightFactor) && mouseY <= menuY + (( 3 * (MENU_HEIGHT) + 2 * SPACING) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Modifie la difficulté*/
                    j1->gold = 400;
                    ordi->difficulte = HARD;
                    (*etat) = JOUER;
                    (*lastUlti) = currentTime;
                }
                /*Clic sur le bouton "Retour"*/
                else if(mouseY >= menuY + ((3 * (MENU_HEIGHT) + 3 * SPACING) * heightFactor) && mouseY <= menuY + (( 4 * (MENU_HEIGHT) + 3 * SPACING) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état menu*/
                    (*etat) = MENU_SOUS_SOLO;
                }
            }
            break;


        /*********/
        /*--JEU--*/
        /*********/
        case JOUER_RESEAU_CREER :
        case JOUER_RESEAU_REJOINDRE :
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
                (*etat) = OPTION_JEU;
            }
            /*Clic sur le bouton d'upgrade*/
            else if(mouseX >= (20 * widthFactor) && mouseX <= (70 * widthFactor) &&
                    mouseY >= (105 * heightFactor) && mouseY <= (155 * heightFactor)){
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                    Mix_PlayChannel(1, click, 0);
                }
                /*On change d'âge en appelant la fonction dédiée*/
                upgrade_building(&j1->building,&j1->xp);
                (*troupe_formee)[0] = -1;
                (*troupe_formee)[1] = -1;
                (*troupe_formee)[2] = -1;
                (*troupe_formee)[3] = -1;

                // reseau
                *reseau_action = PASSAGE_AGE;
                *reseau_action2 = AUCUN_ACTION;
            }
            /*Clic sur le personnage 1*/
            else if(mouseX >= (250 * widthFactor) && mouseX <= (314 * widthFactor) &&
                    mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                    Mix_PlayChannel(1, click, 0);
                }
                (*troupe_formee)[0] = melee;
                /*Le joueur achète un caractère*/
                buy_character(&j1, tab_de_charactere, melee);
                (*nb)[0]++;
                (*lastTroupe)[0] = currentTime;

                // reseau
                *reseau_action = ACHAT_CHARACTER;
                *reseau_action2 = age + melee;
            }
            /*Clic sur le personnage 2*/
            else if(mouseX >= (319 * widthFactor) && mouseX <= (383 * widthFactor) &&
                    mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                    Mix_PlayChannel(1, click, 0);
                }
                (*troupe_formee)[1] = marksman;
                /*Le joueur achète un caractère*/
                buy_character(&j1, tab_de_charactere, marksman);
                (*nb)[1]++;
                (*lastTroupe)[1] = currentTime;

                 // reseau
                *reseau_action = ACHAT_CHARACTER;
                *reseau_action2 = age + marksman;
            }
            /*Clic sur le personnage 3*/
            else if(mouseX >= (388 * widthFactor) && mouseX <= (452 * widthFactor) &&
                    mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                    Mix_PlayChannel(1, click, 0);
                }
                (*troupe_formee)[2] = tank;
                /*Le joueur achète un caractère*/
                buy_character(&j1, tab_de_charactere, tank);
                (*nb)[2]++;
                (*lastTroupe)[2] = currentTime;

                // reseau
                *reseau_action = ACHAT_CHARACTER;
                *reseau_action2 = age + tank;
            }
            /*Clic sur le personnage 4*/
            else if(mouseX >= (457 * widthFactor) && mouseX <= (521 * widthFactor) &&
                    mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                    Mix_PlayChannel(1, click, 0);
                }
                (*troupe_formee)[3] = specialist;
                /*Le joueur achète un caractère*/
                buy_character(&j1, tab_de_charactere, specialist);
                (*nb)[3]++;
                (*lastTroupe)[3] = currentTime;

                // reseau
                *reseau_action = ACHAT_CHARACTER;
                *reseau_action2 = age + specialist;
            }
            /*Clic sur le bouton d'ulti*/
            else if(mouseX >= (85 * widthFactor) && mouseX <= (125 * widthFactor) &&
                    mouseY >= (105 * heightFactor) && mouseY <= (155 * heightFactor)){
                //Bruit quand on clique sur l'élément
                if(!(*index_effet)){
                    Mix_PlayChannel(1, click, 0);
                }
                /*Utilisation de l'ulti*/
                if((*diff_time) >= DELAI_ULTI){
                    switch(*etat){
                            case JOUER_RESEAU_CREER :
                            case JOUER_RESEAU_REJOINDRE : 
                                ulti(&(j2_distant->characters));
                                break;
                            case JOUER :
                                ulti(&(ordi->characters));
                                delete_character(&(ordi->characters));
                                break;
                            default :
                                break;
                    }
                    (*lastUlti) = currentTime;

                    // reseau
                    *reseau_action = ULTI;
                    *reseau_action2 = j1->xp;
                    (*etat) = ULTIME;
                }
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
                    (*etat) = JOUER;
                }
                /*Clic sur le bouton 'Sauvegarde'*/
                else if(mouseY >= menuY + (SPACING + 10 * heightFactor) && mouseY <= menuY + (((MENU_HEIGHT + SPACING) - 10) * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SAUVEGARDER;
                }
                /*Clic sur le bouton 'Musique/Son'*/
                else if(mouseY >= menuY + ((MENU_HEIGHT + 2 * SPACING) + 10) * heightFactor && mouseY <= menuY + (( 2 * (MENU_HEIGHT + SPACING) - 10) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*ancienSon) = OPTION_JEU;
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_SON;
                    
                }
                /*Clic sur le bouton 'Résolution*/
                else if(mouseY >= menuY + ((2 * MENU_HEIGHT + 3 * SPACING) + 10) * heightFactor && mouseY <= menuY + (( 3 * (MENU_HEIGHT + SPACING) - 10) * heightFactor) ){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    (*ancienReso) = OPTION_JEU;
                    /*Changement d'état du menu*/
                    (*etat) = MENU_SOUS_RESOLUTION;
                }
                else if(mouseY >= menuY + ((3 * MENU_HEIGHT + 4 * SPACING) + 10) * heightFactor && mouseY <= menuY + (( 4 * (MENU_HEIGHT + SPACING) - 10) * heightFactor)){
                    //Bruit quand on clique sur l'élément
                    if(!(*index_effet)){
                        Mix_PlayChannel(1, click, 0);
                    }
                    /*Changement d'état du menu*/
                    (*etat) = MENU_PRINCIPAL;
                }
            }
            break;
        
        default : 
            break;
    }
}

/**
 * \fn void relachement(etat_t* etat, int menuX, int menuY, int w, int h, float* widthFactor, float* heightFactor, int mouseX, int mouseY)
 * \brief Gestion du relâchement du clic de la souris sur les éléments du menu.
 * 
 * \param etat Pointeur vers l'état du jeu.
 * \param menuX Position horizontale du menu.
 * \param menuY Position verticale du menu.
 * \param w Largeur de la fenêtre.
 * \param h Hauteur de la fenêtre.
 * \param widthFactor Facteur de mise à l'échelle horizontale.
 * \param heightFactor Facteur de mise à l'échelle verticale.
 * \param mouseX Position horizontale du curseur de la souris.
 * \param mouseY Position verticale du curseur de la souris.
 */
void relachement(etat_t* etat, int menuX, int menuY, int w, int h, float* widthFactor, float* heightFactor, int mouseX, int mouseY)
{
    /*Gestion du relachement du clique de la souris*/
    if((*etat) == MENU_SOUS_SON){
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

/**
 * \fn void deplacement_souris(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police, Mix_Chunk* music, SDL_Event evenement, 
                        float widthFactor, float heightFactor, int etat, character_t* tab_charactere, int* survol)
 * \brief Gestion du déplacement de la souris sur les éléments du menu.
 * 
 * \param rendu Le renderer de la SDL.
 * \param fenetre La fenêtre de la SDL.
 * \param police La police de caractères.
 * \param music Le son de la musique.
 * \param evenement L'événement de la SDL.
 * \param widthFactor Facteur de mise à l'échelle horizontale.
 * \param heightFactor Facteur de mise à l'échelle verticale.
 * \param etat L'état actuel du jeu.
 * \param tab_charactere Le tableau de personnages disponibles.
 * \param survol Pointeur vers la valeur de survol.
 */
void deplacement_souris(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police, Mix_Chunk* music, SDL_Event evenement, 
                        float widthFactor, float heightFactor, int etat, character_t* tab_charactere, int* survol)
{
    /*Récupère les coordonnées du pointeur de la souris*/
    int mouseX = evenement.motion.x;
    int mouseY = evenement.motion.y;

    switch(etat){
        case MENU_SOUS_SON:
            /*Déplacer le curseur si l'utilisateur déplace la souris tout en maintenant le bouton de la souris enfoncé*/
            if (estLache) {
                if (mouseX < volumeBar->x) {
                    mouseX = volumeBar->x;
                } else if (mouseX > volumeBar->x + (volumeBar->w - 14 )) {
                    mouseX = volumeBar->x + (volumeBar->w - 14);
                }
                volume = ((mouseX - volumeBar->x) / 2) / widthFactor;
                Mix_VolumeChunk(music, volume);
                volumeCursor->x = mouseX;
            }
            break;
        
        case JOUER_RESEAU_CREER :
        case JOUER_RESEAU_REJOINDRE :
        case JOUER:
            /*Affichage au survol d'un élément*/
            if(mouseX >= (250 * widthFactor) && mouseX <= (314 * widthFactor) &&
               mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                (*survol) = PERSO1;
            }
            else if(mouseX >= (319 * widthFactor) && mouseX <= (383 * widthFactor) &&
                    mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                (*survol) = PERSO2;
            }
            else if(mouseX >= (388 * widthFactor) && mouseX <= (452 * widthFactor) &&
                    mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                (*survol) = PERSO3;
            }
            else if(mouseX >= (457 * widthFactor) && mouseX <= (521 * widthFactor) &&
                    mouseY >= (36 * heightFactor) && mouseY <= (100 * heightFactor)){
                (*survol) = PERSO4;
            }
            /*Survol du bouton XP*/
            else if(mouseX >= (20 * widthFactor) && mouseX <= (70 * widthFactor) &&
                    mouseY >= (105 * heightFactor) && mouseY <= (155 * heightFactor)){
                (*survol) = XP;
            }
            /*Survol du bouton Ulti*/
            else if(mouseX >= (85 * widthFactor) && mouseX <= (125 * widthFactor) &&
                    mouseY >= (105 * heightFactor) && mouseY <= (155 * heightFactor)){
                (*survol) = ULTIM;
            }
            else{
                (*survol) = -1;
            }
            
            break;
    }
}



/**
 * \fn void destruction(int* selecElement, int* index_effet, int* continuer, etat_t* etat, float* widthFactor, float* heightFactor, int* textInputActive, int* isValid, int* keyCounts, int* ancienSon, int* etatAge, int* ancienReso)
 * \brief Fonction de destruction des variables pour le menu.
 * 
 * \param selecElement Pointeur vers l'élément sélectionné.
 * \param index_effet Pointeur vers l'indice de l'effet.
 * \param continuer Pointeur vers la variable de boucle de jeu.
 * \param etat Pointeur vers l'état du jeu.
 * \param widthFactor Pointeur vers le facteur de mise à l'échelle horizontale.
 * \param heightFactor Pointeur vers le facteur de mise à l'échelle verticale.
 * \param textInputActive Pointeur vers l'état de la saisie de texte.
 * \param isValid Pointeur vers la validité de la saisie de texte.
 * \param keyCounts Pointeur vers le nombre de touches pressées.
 * \param ancienSon Pointeur vers l'ancien niveau de son.
 * \param etatAge Pointeur vers l'état de l'âge.
 * \param ancienReso Pointeur vers l'ancienne résolution.
 */
void destruction(int* selecElement, int* index_effet, int* continuer, etat_t* etat, float* widthFactor, float* heightFactor, int* textInputActive, int* isValid, int* keyCounts, int* ancienSon, int* etatAge, int* ancienReso)
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
    free(etat);
    free(widthFactor);
    free(heightFactor);
}

/**
 * \fn int validateRegex(const char *input, const char *pattern) 
 * \brief Fonction pour vérifier si une chaîne de caractères respecte une expression régulière.
 * 
 * \param input La chaîne de caractères à vérifier.
 * \param pattern Le motif de l'expression régulière.
 * \return 1 si la chaîne de caractères respecte le motif, 0 sinon.
 */
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
/**
 * \fn void touches(SDL_Event evenement, int* textInputActive, int* keyCounts, int* isValid, char* textInput,const char* ipPattern, int * valide)
 * \brief Gère les événements liés à la saisie de texte.
 * 
 * \param evenement L'événement SDL.
 * \param textInputActive Pointeur vers l'état de la saisie de texte.
 * \param keyCounts Pointeur vers le nombre de touches pressées.
 * \param isValid Pointeur vers la validité de la saisie de texte.
 * \param textInput La chaîne de caractères saisie.
 * \param ipPattern Le motif de l'expression régulière pour une adresse IP.
 * \param valide Pointeur vers la validité de l'adresse IP saisie.
 */
void touches(SDL_Event evenement, int* textInputActive, int* keyCounts, int* isValid, char* textInput,const char* ipPattern, int * valide)
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
            if ( *isValid )
            {
                if( init_reseau_client(textInput) )
                {
                    *valide = TRUE;
                }
                else
                {
                    strcpy(textInput,"");
                }
            }
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

/**
 * \fn void reinitialiser_partie(player_t ** player, ordi_t ** ordi)
 * \brief Réinitialise la partie en libérant la mémoire allouée.
 * 
 * \param player Pointeur vers le joueur.
 * \param ordi Pointeur vers l'ordinateur.
 */
void reinitialiser_partie(player_t ** player, ordi_t ** ordi)
{
    destroy_player(player);
    detr_ordi(ordi);
}

/**
 * \fn int fin_partie(player_t * player, ordi_t * ordi, player_t * player_online, int etat)
 * \brief Détermine l'issue de la partie.
 * 
 * \param player Le joueur.
 * \param ordi L'ordinateur.
 * \param player_online Le joueur en ligne.
 * \param etat L'état actuel du jeu.
 * \return Le résultat de la partie.
 */
int fin_partie(player_t * player, ordi_t * ordi, player_t * player_online, int etat)
{
    /* jouer en ligne */
    if ( etat == JOUER_RESEAU_CREER || etat == JOUER_RESEAU_REJOINDRE )
    {
        if ( player->building->pv <= 0 ) return JOUEUR_EN_LIGNE_GAGNE;
        if ( player_online->building->pv <= 0 ) return JOUEUR_GAGNE;
    }

    /* si on joue en solo contre ordinateur */
    if ( etat == JOUER )
    {
        if ( player->building->pv <= 0 ) return ORDI_GAGNE;
        if ( ordi->building->pv <= 0) return JOUEUR_GAGNE;
    }

    return AUCUN_GAGNANT;
}

/**
 * \fn void traitement_pre_jeu(   etat_t * etat, int * a_deja_lancer_partie, player_t ** j1, ordi_t ** o, 
                                player_t * j2_distant, SDL_Texture * image[], int * ancien_lvl, character_t * tab_de_charactere, 
                                int * connexion_reussi, int * valide, int * resultat, SDL_Renderer* rendu)
 * \brief Traitement avant le début du jeu.
 *
 * Effectue divers traitements avant le début d'une partie, tels que la réinitialisation des données, la gestion des sauvegardes, etc.
 *
 * \param etat Pointeur vers l'état du jeu.
 * \param a_deja_lancer_partie Pointeur vers un entier indiquant si une partie a déjà été lancée.
 * \param j1 Double pointeur vers le joueur local.
 * \param o Double pointeur vers l'ordinateur.
 * \param j2_distant Pointeur vers le joueur distant en cas de jeu en réseau.
 * \param image Tableau de textures pour les images du jeu.
 * \param ancien_lvl Pointeur vers l'ancien niveau de jeu.
 * \param tab_de_charactere Tableau de caractères représentant les personnages du jeu.
 * \param connexion_reussi Pointeur vers un entier indiquant si la connexion a réussi.
 * \param valide Pointeur vers un entier indiquant si une action est valide.
 * \param resultat Pointeur vers un entier contenant le résultat de la partie.
 * \param rendu Le rendu SDL.
 */
void traitement_pre_jeu(   etat_t * etat, int * a_deja_lancer_partie, player_t ** j1, ordi_t ** o, 
                                player_t * j2_distant, SDL_Texture * image[], int * ancien_lvl, character_t * tab_de_charactere, 
                                int * connexion_reussi, int * valide, int * resultat, SDL_Renderer* rendu)
{        
        /* variables locales tampons */
        player_t * buffer_player = NULL;
        ordi_t   * buffer_ordi = NULL;
        int i;

        /* qaund on lance une nouvelle partie, on detruit bien toute les données */
        if ( !(*a_deja_lancer_partie) && ( *etat == JOUER || *etat == JOUER_RESEAU_CREER || *etat == JOUER_RESEAU_REJOINDRE ) )
        {
            (*a_deja_lancer_partie) = TRUE;
        }

        /* si le joueur est retourné au menu principal et qu'il a déja creer une partie */
        if ( (*a_deja_lancer_partie) && (*etat) == MENU_PRINCIPAL )
        {
            reinitialiser_partie(j1,o);
            for(i=0;i< NB_CHARACTER*2;i++)
                if(i<4)
                    image[i]=IMG_LoadTexture(rendu,tab_de_charactere[Prehistoire+i].sprite);
                else
                    image[i]=NULL;
            (*ancien_lvl)=Prehistoire;
            (*a_deja_lancer_partie) = FALSE;
        }

        /* si la connexion a été acceptée */
        if ( (*valide) ) // si on souhaite rejoindre une partie en ligne
        {
            /* on mets l'etat du menu a jour */
            (*etat) = JOUER_RESEAU_REJOINDRE;
            (*valide) = FALSE;
        }

        switch((*etat))
        {
            /* si le joueur clique sur reprendre partie */
            case JOUER_CHARGER : 
                reinitialiser_partie(j1,o);
                if ( load(&buffer_ordi, &buffer_player, tab_de_charactere) )
                {
                    (*j1) = buffer_player;
                    (*o) = buffer_ordi;
                    buffer_player = NULL;
                    buffer_ordi = NULL;
                    (*etat) = JOUER;
                }
                else
                {
                    (*etat) = MENU_SOUS_JOUER;
                }

                break;

            /* quand l'utilisateur clique sur sauvegarder */
            case MENU_SAUVEGARDER :
                save((*o),(*j1));
                (*etat) = OPTION_JEU;
                break;
            
            /* on chercher un gagnant dans une partie en cours */
            case JOUER :
            case JOUER_RESEAU_CREER :
            case JOUER_RESEAU_REJOINDRE :
                (*resultat) = fin_partie((*j1),(*o),j2_distant,(*etat));
                if ( (*resultat) != AUCUN_GAGNANT ) (*etat) = FIN_PARTIE;
                break;
            
            /* quand on essaie de jouer une partie en mode reseau etant le serveur (creer) */
            case MENU_SOUS_CREER :
                if ( init_reseau_serveur() && !(*connexion_reussi) )
                {
                    (*connexion_reussi) = TRUE;
                    (*etat) = JOUER_RESEAU_CREER;
                }
                else (*etat) = MENU_SOUS_ENLIGNE;
                break;
            
            default :
                break;
        }
    
}

/**
 * \fn void traitement_en_jeu(    etat_t * etat, player_t ** j1, player_t ** j2_distant, ordi_t ** o, 
                                Uint32 * diff_time, Uint32 * lastUlti, Uint32 * delai_ulti, 
                                int * reseau_action, int * reseau_action2, int * to_server_socket, int * client_socket, 
                                character_t * tab_de_charactere, SDL_Renderer * rendu, SDL_Rect * playerImg, SDL_Rect * ordiImg, 
                                SDL_Rect * playerAttackImg, SDL_Rect * ordiAttackImg, int * first_attaque, SDL_Rect playerPosition[], 
                                SDL_Rect ordiPosition[], int * ancien_lvl, SDL_Texture * image[], SDL_Texture * img_char[], 
                                Uint32 currentTime, Uint32 * lastMovement, int w, int h, int * cameraX, int * cameraY, 
                                unsigned long int * debut_sprite, unsigned long int * fin_sprite, SDL_Texture * img_c_ordi[])
 * \brief Traitement en cours de jeu.
 *
 * Effectue divers traitements pendant le jeu, tels que le calcul des actions, l'affichage, etc.
 *
 * \param etat Pointeur vers l'état du jeu.
 * \param j1 Double pointeur vers le joueur local.
 * \param j2_distant Double pointeur vers le joueur distant en cas de jeu en réseau.
 * \param o Double pointeur vers l'ordinateur.
 * \param diff_time Pointeur vers le temps écoulé depuis la dernière action.
 * \param lastUlti Pointeur vers le dernier usage d'une attaque ultime.
 * \param delai_ulti Pointeur vers le délai avant la prochaine attaque ultime.
 * \param reseau_action Pointeur vers l'action réseau du joueur local.
 * \param reseau_action2 Pointeur vers l'action réseau du joueur distant.
 * \param to_server_socket Pointeur vers le socket du serveur.
 * \param client_socket Pointeur vers le socket du client.
 * \param tab_de_charactere Tableau de caractères représentant les personnages du jeu.
 * \param rendu Le rendu SDL.
 * \param playerImg Rectangles représentant la position de l'image du joueur local.
 * \param ordiImg Rectangles représentant la position de l'image de l'ordinateur.
 * \param playerAttackImg Rectangles représentant la position de l'attaque du joueur local.
 * \param ordiAttackImg Rectangles représentant la position de l'attaque de l'ordinateur.
 * \param first_attaque Pointeur vers un entier indiquant si c'est la première attaque.
 * \param playerPosition Tableau de rectangles représentant la position du joueur local.
 * \param ordiPosition Tableau de rectangles représentant la position de l'ordinateur.
 * \param ancien_lvl Pointeur vers l'ancien niveau de jeu.
 * \param image Tableau de textures pour les images du jeu.
 * \param img_char Tableau de textures pour les images de caractères.
 * \param currentTime Temps actuel.
 * \param lastMovement Pointeur vers le dernier mouvement.
 * \param w Largeur de l'écran.
 * \param h Hauteur de l'écran.
 * \param cameraX Pointeur vers la position horizontale de la caméra.
 * \param cameraY Pointeur vers la position verticale de la caméra.
 * \param debut_sprite Pointeur vers le début du sprite.
 * \param fin_sprite Pointeur vers la fin du sprite.
 * \param img_c_ordi Tableau de textures pour les images d'ordinateur.
 */
void traitement_en_jeu(    etat_t * etat, player_t ** j1, player_t ** j2_distant, ordi_t ** o, 
                                Uint32 * diff_time, Uint32 * lastUlti, Uint32 * delai_ulti, 
                                int * reseau_action, int * reseau_action2, int * to_server_socket, int * client_socket, 
                                character_t * tab_de_charactere, SDL_Renderer * rendu, SDL_Rect * playerImg, SDL_Rect * ordiImg, 
                                SDL_Rect * playerAttackImg, SDL_Rect * ordiAttackImg, int * first_attaque, SDL_Rect playerPosition[], 
                                SDL_Rect ordiPosition[], int * ancien_lvl, SDL_Texture * image[], SDL_Texture * img_char[], 
                                Uint32 currentTime, Uint32 * lastMovement, int w, int h, int * cameraX, int * cameraY, 
                                unsigned long int * debut_sprite, unsigned long int * fin_sprite, SDL_Texture * img_c_ordi[])
{
    int action = AUCUN_ACTION, action2 = AUCUN_ACTION;

    switch((*etat))
    {
        case JOUER : // si on joue une partie classique contre un ordinateur
             /*Calcul du temps avant d'utiliser l'ulti*/
            (*diff_time) = currentTime - (*lastUlti);
            (*delai_ulti) = DELAI_ULTI - (*diff_time);
            envoie_char(j1);
            jeu_ordi((*o),(*j1),tab_de_charactere);

            affichageSprite(rendu, (*j1), (*o), playerImg, ordiImg, playerAttackImg, ordiAttackImg, first_attaque, playerPosition, ordiPosition, ancien_lvl, 
                            tab_de_charactere, image, img_char, img_c_ordi, currentTime, lastMovement, w, h, cameraX, cameraY);
            break;
        
        case JOUER_RESEAU_CREER :
        case JOUER_RESEAU_REJOINDRE :

            /*Calcul du temps avant d'utiliser l'ulti*/
            (*diff_time) = currentTime - (*lastUlti);
            (*delai_ulti) = DELAI_ULTI - (*diff_time);

            switch((*etat))
            {
                case JOUER_RESEAU_CREER :
                    recevoir((*client_socket),&action,&action2);
                    envoyer((*client_socket),reseau_action,reseau_action2);
                    break;

                case JOUER_RESEAU_REJOINDRE :
                    recevoir((*to_server_socket),&action,&action2);
                    envoyer((*to_server_socket),reseau_action, reseau_action2);
                    break;
                
                default:
                    break;
            }
            switch(action)
            {
                case AUCUN_ACTION : // si adversaire fait aucune action
                    break;

                case ACHAT_CHARACTER : // adversaire achete un perso 
                    if ( action2 != AUCUN_ACTION )
                    {
                        buy_character(j2_distant,tab_de_charactere,action2);
                    }
                    break;

                case PASSAGE_AGE : // adversaire passe a l'age suivant
                    if ( action2 != AUCUN_ACTION )
                    {
                        upgrade_building(&((*j2_distant)->building),&action2);
                    }
                    break;

                case ULTI : // adversaire met ultime
                    ulti(&((*j1)->characters));
                    break;

                default : 
                    break;
            }

            envoie_char(j1); // on envoie file d'attente
            envoie_char(j2_distant); // envoie file d'attente du joueur 2
            
            affichageSpriteReseau(  rendu, (*j1), (*j2_distant), playerImg, ordiImg, playerAttackImg, ordiAttackImg, first_attaque, playerPosition, ordiPosition, ancien_lvl, 
                                    tab_de_charactere, image, img_char, img_c_ordi, currentTime, lastMovement, w, h, cameraX, cameraY);
            break;

        default :
            break;
    }
}                           

/**
 * \fn void traitement_post_jeu(   character_t ** tab_de_charactere, player_t ** j1, player_t ** j2_distant, ordi_t ** o, int * cameraX,
                            int * cameraY, char * buffer, int * survol, Uint32 * lastUlti, Uint32 * diff_time, Uint32 * delai_ulti,
                            int * reseau_action, int * reseau_action2, int * troupe_formee[], int * nb[], Uint32 * lastTroupe[],
                            Mix_Chunk * musique_fin, int * ancien_lvl )
 * \brief Traitement après la fin du jeu, effectue divers traitements après la fin d'une partie, tels que la libération de mémoire, etc.
 *
 * \param tab_de_charactere Double pointeur vers le tableau de caractères.
 * \param j1 Double pointeur vers le joueur local.
 * \param j2_distant Double pointeur vers le joueur distant en cas de jeu en réseau.
 * \param o Double pointeur vers l'ordinateur.
 * \param cameraX Pointeur vers la position horizontale de la caméra.
 * \param cameraY Pointeur vers la position verticale de la caméra.
 * \param buffer Pointeur vers le tampon de mémoire.
 * \param survol Pointeur vers l'indicateur de survol.
 * \param lastUlti Pointeur vers le dernier usage d'une attaque ultime.
 * \param diff_time Pointeur vers le temps écoulé depuis la dernière action.
 * \param delai_ulti Pointeur vers le délai avant la prochaine attaque ultime.
 * \param reseau_action Pointeur vers l'action réseau du joueur distant.
 * \param reseau_action2 Pointeur vers l'action réseau du joueur distant.
 * \param troupe_formee Tableau d'entiers indiquant si une troupe est formée.
 * \param nb Tableau d'entiers contenant le nombre.
 * \param lastTroupe Tableau de temps de la dernière troupe.
 * \param musique_fin Pointeur vers la musique de fin de partie.
 * \param ancien_lvl Pointeur vers l'ancien niveau de jeu.
 */
void traitement_post_jeu(   character_t ** tab_de_charactere, player_t ** j1, player_t ** j2_distant, ordi_t ** o, int * cameraX,
                            int * cameraY, char * buffer, int * survol, Uint32 * lastUlti, Uint32 * diff_time, Uint32 * delai_ulti,
                            int * reseau_action, int * reseau_action2, int * troupe_formee[], int * nb[], Uint32 * lastTroupe[],
                            Mix_Chunk * musique_fin, int * ancien_lvl )
{
    int i;

    free(ancien_lvl);
    destroy_tab_character(tab_de_charactere);
    destroy_player(j1);
    destroy_player(j2_distant);
    detr_ordi(o);
    free(cameraX);
    free(cameraY);
    free(buffer);
    free(survol);
    free(lastUlti);
    free(diff_time);
    free(delai_ulti);
    free(reseau_action);
    free(reseau_action2);

    for(i = 0; i < 4; i++){
        free(troupe_formee[i]);
    }
    for(i = 0; i < 4; i++){
        free(nb[i]);
    }
    for(i = 0; i < 4; i++){
        free(lastTroupe[i]);
    }
    Mix_FreeChunk(musique_fin);
}