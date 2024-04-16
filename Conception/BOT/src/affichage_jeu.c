#include "../lib/affichage_jeu.h"


/*Affichage de l4HUD*/
void afficherHUD(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police_texte, SDL_Texture* parametre, 
                 SDL_Texture* upgrade, SDL_Texture* gold, SDL_Texture* xp, player_t* joueur, SDL_Texture* sprite_hud[],
                 SDL_Texture* ultim, int age)
{
    /*Affichage du bouton paramètre*/
    SDL_Rect rect_parametre = creationRectangle(fenetre, WINDOW_WIDTH - 60, 10, 50, 50);
    SDL_RenderCopy(rendu, parametre, NULL, &rect_parametre);

    /*Affichage du titre à côter du bouton paramètre*/
    afficherTitre(rendu, fenetre, WINDOW_WIDTH - 230, -20, 150, 100);

    /*Affichage du bouton d'upgrade*/
    SDL_Rect rect_upgrade = creationRectangle(fenetre, 20, 105, 50, 50);
    SDL_RenderCopy(rendu, upgrade, NULL, &rect_upgrade);

    /*Affichage du bouton d'ultim
    SDL_Rect rect_ultim = creationRectangle(fenetre, 80, 105, 50, 50);
    SDL_RenderCopy(rendu, ultim, NULL, &rect_ultim);*/

    /*Affichage du rectangle translucide contenant l'or et l'xp*/
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_gold_xp = creationRectangle(fenetre, 20, 20, 220, 80);
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_gold_xp);

    /*Affichage du logo des gold*/
    SDL_Rect rect_gold = creationRectangle(fenetre, 30, 25, 30, 30);
    SDL_RenderCopy(rendu, gold, NULL, &rect_gold);

    /*Affichage du logo des xp*/
    SDL_Rect rect_xp = creationRectangle(fenetre, 30, 65, 30,30);
    SDL_RenderCopy(rendu, xp, NULL, &rect_xp);

    /*Affichage de l'or*/
    char text_gold[30] ;
    sprintf(text_gold, "%.2f", joueur->gold);
    SDL_Surface* surface_text_gold = TTF_RenderUTF8_Solid(police_texte, text_gold, WHITE);
    SDL_Texture* texture_text_gold = SDL_CreateTextureFromSurface(rendu, surface_text_gold);
    SDL_Rect rect_text_gold = creationRectangle(fenetre, 70, 25, surface_text_gold->w - 100, 25);
    SDL_RenderCopy(rendu, texture_text_gold, NULL, &rect_text_gold);
    SDL_FreeSurface(surface_text_gold);
    SDL_DestroyTexture(texture_text_gold);


    /*Affichage de l'xp*/
    char text_xp[30] ;
    sprintf(text_xp, "%d", joueur->xp);
    SDL_Surface* surface_text_xp = TTF_RenderUTF8_Solid(police_texte, text_xp, WHITE);
    SDL_Texture* texture_text_xp = SDL_CreateTextureFromSurface(rendu, surface_text_xp);
    SDL_Rect rect_text_xp = creationRectangle(fenetre, 70, 65, surface_text_xp->w - 80, 25);
    SDL_RenderCopy(rendu, texture_text_xp, NULL, &rect_text_xp);
    SDL_FreeSurface(surface_text_xp);
    SDL_DestroyTexture(texture_text_xp);


    /*Affichage des rectangles derrière les personnages*/
    SDL_SetRenderDrawColor(rendu, 240, 240, 240, 180);/*Couleur semi-transparente*/
    SDL_Rect Perso1 = creationRectangle(fenetre, 250, 36, TAILLE_SPRITE, TAILLE_SPRITE);
    SDL_Rect Perso2 = creationRectangle(fenetre, 319, 36, TAILLE_SPRITE, TAILLE_SPRITE);
    SDL_Rect Perso3 = creationRectangle(fenetre, 388, 36, TAILLE_SPRITE, TAILLE_SPRITE);
    SDL_Rect Perso4 = creationRectangle(fenetre, 457, 36, TAILLE_SPRITE, TAILLE_SPRITE);
    SDL_RenderFillRect(rendu, &Perso1);
    SDL_RenderFillRect(rendu, &Perso2);
    SDL_RenderFillRect(rendu, &Perso3);
    SDL_RenderFillRect(rendu, &Perso4);

    SDL_Rect tete_perso = creationRectangle(fenetre, 0, 0, 45, 60); 
    /*Affichage de la tête des personnages dans les rectangles*/
    switch(age){
        case Prehistoire:
            SDL_RenderCopy(rendu, sprite_hud[0], &tete_perso, &Perso1);
            SDL_RenderCopy(rendu, sprite_hud[1], &tete_perso, &Perso2);
            SDL_RenderCopy(rendu, sprite_hud[2], &tete_perso, &Perso3);
            SDL_RenderCopy(rendu, sprite_hud[3], &tete_perso, &Perso4);
            break;
        
        case Antiquite:
            SDL_RenderCopy(rendu, sprite_hud[4], &tete_perso, &Perso1);
            SDL_RenderCopy(rendu, sprite_hud[5], &tete_perso, &Perso2);
            SDL_RenderCopy(rendu, sprite_hud[6], &tete_perso, &Perso3);
            SDL_RenderCopy(rendu, sprite_hud[7], &tete_perso, &Perso4);
            break;
        
        case Moyen_Age:
            SDL_RenderCopy(rendu, sprite_hud[8], &tete_perso, &Perso1);
            SDL_RenderCopy(rendu, sprite_hud[9], &tete_perso, &Perso2);
            SDL_RenderCopy(rendu, sprite_hud[10], &tete_perso, &Perso3);
            SDL_RenderCopy(rendu, sprite_hud[11], &tete_perso, &Perso4);
            break;
        
        case Ere_Moderne:
            SDL_RenderCopy(rendu, sprite_hud[12], &tete_perso, &Perso1);
            SDL_RenderCopy(rendu, sprite_hud[13], &tete_perso, &Perso2);
            SDL_RenderCopy(rendu, sprite_hud[14], &tete_perso, &Perso3);
            SDL_RenderCopy(rendu, sprite_hud[15], &tete_perso, &Perso4);
            break;

        case Ere_Futuriste:
            SDL_RenderCopy(rendu, sprite_hud[16], &tete_perso, &Perso1);
            SDL_RenderCopy(rendu, sprite_hud[17], &tete_perso, &Perso2);
            SDL_RenderCopy(rendu, sprite_hud[18], &tete_perso, &Perso3);
            SDL_RenderCopy(rendu, sprite_hud[19], &tete_perso, &Perso4);
            break;
    }
}

/*Affichage de l'image de fond du jeu et gestion du déplacement de la souris pour défiler l'image*/
void afficherJeuFond(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* fond_jeu, int* cameraX, int* cameraY)
{
    /*Récupère les dimensions de la fenêtre*/
    int w, h;
    SDL_GetWindowSize(fenetre, &w, &h);

    /*Définir une marge de déplacement pour activer le déplacement de la caméra*/
    int margin = 40;

    /*Récupère la position de la souris*/
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    /*Contrôle du déplacement sur l'axe X de la caméra*/
    if (mouseX < margin && (*cameraX) > 0) {
        (*cameraX) -= SCROLL_SPEED;
    } else if (mouseX > w - margin) {
        (*cameraX) += SCROLL_SPEED;
    }

    /*Calculer la position maximale de la caméra pour chaque axe*/
    int maxCameraX = IMAGE_WIDTH - w;

    /*Limitation des déplacements pour rester dans les limites de l'image*/
    /*Sur l'axe x*/
    if ((*cameraX) < 0) {
        (*cameraX) = 0;
    } else if ((*cameraX) > maxCameraX){
        (*cameraX) = maxCameraX;
    }
    
    /*Création des rectangles source(image) et destination(écran)*/
    SDL_Rect destRect =  {0, 0, w, h};
    SDL_Rect srcRect = {(*cameraX), (*cameraY), w, h};

    /*Nettoie le rendu et affiche l'image*/
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, fond_jeu, &srcRect, &destRect);
}

/*Affiche l'image de l'arrière plan en fonction de l'âge*/
void gestionAffichageFondJeu(SDL_Renderer* rendu, SDL_Window* fenetre, int* etatAge, 
                             SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age,
                             SDL_Texture* moderne, SDL_Texture* futuriste, player_t* j1, ordi_t* o,
                             int* cameraX, int* cameraY)
{
    /*Détermine le max du niveau des batiments entre l'ordi et le joueur*/
    (*etatAge) = max(j1->building->level, o->building->level);
    /*Affiche le fond correspondant*/
    switch((*etatAge)){
        case Prehistoire:
            afficherJeuFond(rendu, fenetre, prehistoire, cameraX, cameraY);
            break;
        case Antiquite:
            afficherJeuFond(rendu, fenetre, antiquite, cameraX, cameraY);
            break;
        case Moyen_Age:
            afficherJeuFond(rendu, fenetre, moyen_age, cameraX, cameraY);
            break;
        case Ere_Moderne:
            afficherJeuFond(rendu, fenetre, moderne, cameraX, cameraY);
            break;
        case Ere_Futuriste:
            afficherJeuFond(rendu, fenetre, futuriste, cameraX, cameraY);
            break;
                
        default:
            afficherJeuFond(rendu, fenetre, prehistoire, cameraX, cameraY);
            break;
    }
}

/*Fonction d'affichage du menu des options quand on est en jeu*/
void afficherOptionJeu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT - (4 * MENU_HEIGHT) + SPACING) / 2;  // Position verticale centrée pour le sous-menu

    /*Affichage du rectangle translucide derrière le menu*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);/*Couleur semi-transparente*/
    SDL_Rect rect_menu = creationRectangle(fenetre, menuX, menuY, MENU_WIDTH, (5 * MENU_HEIGHT) + (4 * SPACING));
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rendu, &rect_menu);

    /*Afficher les onglets du menu avec espacement*/
    afficherMenu(rendu, police, fenetre, "Reprendre", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Sauvegarder", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Musique/Son", menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Résolution", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour au menu principal", menuX, menuY + 4 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}

void img_charactere_inser(tab_charactere_t * characters,building_t * building, SDL_Texture* img_c[], SDL_Texture* tab[])
{
    int i;
    if(characters==NULL)
        return;
    for(i=0;i<characters->nb;i++){
        switch (characters->tab[i]->classe)
        {
        case melee:
            if(characters->tab[i]->age < building->level)
                img_c[i]=tab[NB_CHARACTER+melee];
            else
                img_c[i]=tab[0];
            break;
            
        case marksman:
            if(characters->tab[i]->age < building->level)
                img_c[i]=tab[NB_CHARACTER+marksman];
            else
                img_c[i]=tab[marksman];
            break;
            
        case tank:
            if(characters->tab[i]->age < building->level)
                img_c[i]=tab[NB_CHARACTER+tank];
            else
                img_c[i]=tab[tank];
            break;
            
        case specialist:
            if(characters->tab[i]->age < building->level)
                img_c[i]=tab[NB_CHARACTER+specialist];
            else
                img_c[i]=tab[specialist];
            break;
            
        default:
            break;
        }
    }
}

/*Affichage des sprite et gestion de leur déplacement*/
void affichageSprite(SDL_Renderer* rendu, player_t* j1, ordi_t* o, SDL_Rect* playerImg, SDL_Rect* ordiImg, int attaque,
                     SDL_Rect playerPosition[], SDL_Rect ordiPosition[], int* upgrade_j, character_t* tab_de_charactere,
                     SDL_Texture* image[], SDL_Texture* img_char[], SDL_Texture* img_c_ordi[], Uint32 currentTime, Uint32* lastMovement,
                     int w, int h, int* cameraX, int* cameraY)
{
    int i;


    if(currentTime - (*lastMovement) >= 100 && attaque == 0 && (j1->characters->nb > 0 || o->characters->nb > 0)){ //le sprite va avancer tout les 100 ms
        if(playerImg->x == TAILLE_SPRITE*8) 
            playerImg->x = TAILLE_SPRITE; //si on arrive a la fin de l'animation on retourne a la premiere pour faire l'animation en continu
        else {
            playerImg->x += TAILLE_SPRITE;//on passe a l'image suivante pour l'animation
        }
        
        if(ordiImg->x == TAILLE_SPRITE*8) 
            ordiImg->x = TAILLE_SPRITE; //si on arrive a la fin de l'animation on retourne a la premiere pour faire l'animation en continu
        else {
            ordiImg->x += TAILLE_SPRITE;//on passe a l'image suivante pour l'animation
        }

        deplacement(j1->characters, o->characters->tab[0], IMAGE_WIDTH - 700);
        deplacement(o->characters, j1->characters->tab[0], 350);

        for(i=0; i<j1->characters->nb; i++){
            playerPosition[i].x = j1->characters->tab[i]->x - (*cameraX);//on avance
            playerPosition[i].y = h - (TAILLE_SPRITE * 2) - 16;
        }
        for(i=0; i<o->characters->nb; i++){
            ordiPosition[i].x = o->characters->tab[i]->x - (*cameraX);
            ordiPosition[i].y = h - (TAILLE_SPRITE * 2) - 16;
        }

        (*lastMovement)= SDL_GetTicks();
    }

    if((*upgrade_j)){
        for(i=0;i<NB_CHARACTER;i++)
            image[i]= IMG_LoadTexture(rendu,tab_de_charactere[j1->building->level*NB_CHARACTER+i].sprite);
        for(i=0;i<NB_CHARACTER;i++)
            image[i+NB_CHARACTER]= IMG_LoadTexture(rendu,tab_de_charactere[(j1->building->level-1)*NB_CHARACTER+i].sprite);
        (*upgrade_j)=0;
    }
        
    img_charactere_inser(j1->characters,j1->building,img_char,image);
    img_charactere_inser(o->characters,o->building,img_c_ordi,image);
        
    for(i=0;i<j1->characters->nb;i++){
        SDL_RenderCopy(rendu, img_char[i], playerImg, &playerPosition[i]);
    }
    for(i=0;i<o->characters->nb;i++){
        SDL_RenderCopy(rendu, img_c_ordi[i], ordiImg, &ordiPosition[i]);
    }
}

/*Affichage des buildings*/
void affichageBulding(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* building[], int age,
                      int cameraX, int cameraY)
{
    int w, h;
    SDL_GetWindowSize(fenetre, &w, &h);

    SDL_Rect rect_build = {30, h - 300, 350, 291};
    SDL_Rect rect_build_ad = {IMAGE_WIDTH - 350, h - 300, 350, 291}; 

    // Ajouter la position de la caméra à la position de la base
    rect_build.x -= cameraX;
    rect_build.y -= cameraY;

    rect_build_ad.x -= cameraX;
    rect_build_ad.y -= cameraY;
    
     switch(age){
        case Prehistoire:
            SDL_RenderCopy(rendu, building[0], NULL, &rect_build);
            SDL_RenderCopy(rendu, building[1], NULL, &rect_build_ad);
            break;
        
        case Antiquite:
            SDL_RenderCopy(rendu, building[2], NULL, &rect_build);
            SDL_RenderCopy(rendu, building[3], NULL, &rect_build_ad);
            break;
        
        case Moyen_Age:
            SDL_RenderCopy(rendu, building[4], NULL, &rect_build);
            SDL_RenderCopy(rendu, building[5], NULL, &rect_build_ad);
            break;
        
        case Ere_Moderne:
            SDL_RenderCopy(rendu, building[6], NULL, &rect_build);
            SDL_RenderCopy(rendu, building[7], NULL, &rect_build_ad);
            break;

        case Ere_Futuriste:
            SDL_RenderCopy(rendu, building[8], NULL, &rect_build);
            SDL_RenderCopy(rendu, building[9], NULL, &rect_build_ad);
            break;
    }
}