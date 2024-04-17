/**
 * \file affichage_jeu.c
 * \brief Contient les fonctions d'affichages en jeu
 * \author Poirier Victor
 * \date 09 févrirer 2024
 * 
 * 
*/
#include "../lib/affichage_jeu.h"

/**
 * @brief Affiche l'interface utilisateur du HUD (Heads-Up Display) comprenant divers éléments tels que les boutons, les indicateurs de ressources, etc.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 * @param police_texte Police de caractères pour le texte.
 * @param parametre Texture du bouton de paramètre.
 * @param upgrade Texture du bouton d'upgrade.
 * @param gold Texture de l'indicateur d'or.
 * @param xp Texture de l'indicateur d'XP.
 * @param joueur Structure de données représentant le joueur.
 * @param sprite_hud Tableau de textures des têtes des personnages du joueur.
 * @param ultim Texture du bouton de compétence ultime.
 * @param age Âge actuel du jeu.
 */
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

    /*Affichage du bouton d'ultim*/
    SDL_Rect rect_ultim = creationRectangle(fenetre, 80, 105, 50, 50);
    SDL_RenderCopy(rendu, ultim, NULL, &rect_ultim);

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

/**
 * @brief Affiche l'image de fond du jeu et gère le déplacement de la souris pour défiler l'image.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 * @param fond_jeu Texture de l'image de fond du jeu.
 * @param cameraX Pointeur vers la position horizontale de la caméra.
 * @param cameraY Pointeur vers la position verticale de la caméra.
 */
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

/**
 * @brief Affiche l'image de fond en fonction de l'âge du jeu.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 * @param etatAge Pointeur vers l'état actuel de l'âge du jeu.
 * @param prehistoire Texture de l'ère préhistorique.
 * @param antiquite Texture de l'Antiquité.
 * @param moyen_age Texture du Moyen Âge.
 * @param moderne Texture de l'ère moderne.
 * @param futuriste Texture de l'ère futuriste.
 * @param j1 Structure de données représentant le joueur.
 * @param o Structure de données représentant l'ordinateur.
 * @param cameraX Pointeur vers la position horizontale de la caméra.
 * @param cameraY Pointeur vers la position verticale de la caméra.
 */
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

/**
 * @brief Affiche le menu des options en jeu.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param police Police de caractères pour le texte.
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 */void afficherOptionJeu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre)
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

/**
 * @brief Insère les images des personnages en fonction de leur âge dans un tableau.
 * 
 * @param characters Tableau de personnages.
 * @param age Âge actuel du jeu.
 * @param img_c Tableau de textures d'images de personnages.
 * @param tab Tableau de textures d'images.
 */
void img_charactere_inser(tab_charactere_t * characters, int age, SDL_Texture* img_c[], SDL_Texture* tab[])
{
    int i;
    if(characters==NULL)
        return;
    for(i=0;i<characters->nb;i++){
        switch (characters->tab[i]->classe)
        {
        case melee:
            if(characters->tab[i]->age < age)
                img_c[i]=tab[NB_CHARACTER+melee];
            else
                img_c[i]=tab[0];
            break;
            
        case marksman:
            if(characters->tab[i]->age < age)
                img_c[i]=tab[NB_CHARACTER+marksman];
            else
                img_c[i]=tab[marksman];
            break;
            
        case tank:
            if(characters->tab[i]->age < age)
                img_c[i]=tab[NB_CHARACTER+tank];
            else
                img_c[i]=tab[tank];
            break;
            
        case specialist:
            if(characters->tab[i]->age < age)
                img_c[i]=tab[NB_CHARACTER+specialist];
            else
                img_c[i]=tab[specialist];
            break;
            
        default:
            break;
        }
    }
}

/**
 * @brief Interpolation linéaire entre deux valeurs.
 * 
 * @param a Première valeur.
 * @param b Deuxième valeur.
 * @param t Temps.
 * @return float Valeur interpolée.
 */
float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

/**
 * @brief Affiche les sprites des personnages et gère leur déplacement.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param j1 Structure de données représentant le joueur.
 * @param o Structure de données représentant l'ordinateur.
 * @param playerImg Rectangle délimitant le sprite du joueur.
 * @param ordiImg Rectangle délimitant le sprite de l'ordinateur.
 * @param attaque Indicateur d'attaque.
 * @param playerPosition Tableau de rectangles délimitant la position des sprites du joueur.
 * @param ordiPosition Tableau de rectangles délimitant la position des sprites de l'ordinateur.
 * @param ancien_lvl Pointeur vers le niveau précédent.
 * @param tab_de_charactere Tableau des caractéristiques des personnages.
 * @param image Tableau de textures des images.
 * @param img_char Tableau de textures des images de personnages du joueur.
 * @param img_c_ordi Tableau de textures des images de personnages de l'ordinateur.
 * @param currentTime Temps actuel.
 * @param lastMovement Pointeur vers le dernier mouvement.
 * @param w Largeur de la fenêtre.
 * @param h Hauteur de la fenêtre.
 * @param cameraX Pointeur vers la position horizontale de la caméra.
 * @param cameraY Pointeur vers la position verticale de la caméra.
 */void affichageSprite(SDL_Renderer* rendu, player_t* j1, ordi_t* o, SDL_Rect* playerImg, SDL_Rect* ordiImg, int attaque,
                     SDL_Rect playerPosition[], SDL_Rect ordiPosition[], int* ancien_lvl, character_t* tab_de_charactere,
                     SDL_Texture* image[], SDL_Texture* img_char[], SDL_Texture* img_c_ordi[], Uint32 currentTime, Uint32* lastMovement,
                     int w, int h, int* cameraX, int* cameraY)
{
    int i,level, frame_deplace;

    /*Calcul du temps écoulé depuis la dernière mise à jour*/
    float t = (float)(currentTime - *lastMovement) / MOVEMENT_DURATION;
    if (t > 1.0f) {
        t = 1.0f;
    }

    /*Calcul de la position cible de la caméra pour chaque sprite*/
    int targetCameraX = *cameraX;
    int targetCameraY = *cameraY;

    /*Interpolation linéaire entre la position actuelle de la caméra et la position cible*/
    int interpolatedCameraX = lerp(*cameraX, targetCameraX, t);
    int interpolatedCameraY = lerp(*cameraY, targetCameraY, t);

    for(i=0; i<j1->characters->nb; i++){
        /*Calcul de la position cible du joueur en fonction de la caméra*/
        int targetPlayerX = j1->characters->tab[i]->x - interpolatedCameraX;
        int targetPlayerY = h - (TAILLE_SPRITE * 2) - 16;

        /*Interpolation linéaire entre la position actuelle du joueur et la position cible*/
        int interpolatedPlayerX = lerp(playerPosition[i].x, targetPlayerX, t);
        int interpolatedPlayerY = lerp(playerPosition[i].y, targetPlayerY, t);

        /*Mise à jour de la position du joueur*/
        playerPosition[i].x = interpolatedPlayerX;
        playerPosition[i].y = interpolatedPlayerY;
    }

    for(i=0; i<o->characters->nb; i++){
        /*Calcul de la position cible de l'ordinateur en fonction de la caméra*/
        int targetOrdiX = o->characters->tab[i]->x - interpolatedCameraX;
        int targetOrdiY = h - (TAILLE_SPRITE * 2) - 16;

        /*Interpolation linéaire entre la position actuelle de l'ordinateur et la position cible*/
        int interpolatedOrdiX = lerp(ordiPosition[i].x, targetOrdiX, t);
        int interpolatedOrdiY = lerp(ordiPosition[i].y, targetOrdiY, t);

        /*Mise à jour de la position de l'ordinateur*/
        ordiPosition[i].x = interpolatedOrdiX;
        ordiPosition[i].y = interpolatedOrdiY;
    }

    /*Mise à jour de la position de la caméra*/
    *cameraX = interpolatedCameraX;
    *cameraY = interpolatedCameraY;


    /*Déplacement du sprite*/
    if(currentTime - (*lastMovement) >= 100 && attaque == 0 && (j1->characters->nb > 0 || o->characters->nb > 0)){ /*le sprite va avancer tout les 100 ms*/
        if(playerImg->x == TAILLE_SPRITE*8) 
            playerImg->x = TAILLE_SPRITE; /*si on arrive a la fin de l'animation on retourne a la premiere pour faire l'animation en continu*/
        else {
            playerImg->x += TAILLE_SPRITE;/*on passe a l'image suivante pour l'animation*/
        }
        
        if(ordiImg->x == TAILLE_SPRITE*8) 
            ordiImg->x = TAILLE_SPRITE; /*si on arrive a la fin de l'animation on retourne a la premiere pour faire l'animation en continu*/
        else {
            ordiImg->x += TAILLE_SPRITE;/*on passe a l'image suivante pour l'animation*/
        }

        deplacement(j1->characters, o->characters->tab[0], POS_DEP_AD);
        deplacement(o->characters, j1->characters->tab[0], POS_DEP);

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
    //afficher_player(j1);
    level = max(o->building->level,j1->building->level);
    if((*ancien_lvl) < level){
        for(i=0;i<NB_CHARACTER;i++)
            image[i]= IMG_LoadTexture(rendu,tab_de_charactere[level*NB_CHARACTER+i].sprite);
        for(i=0;i<NB_CHARACTER;i++)
            image[i+NB_CHARACTER]= IMG_LoadTexture(rendu,tab_de_charactere[(*ancien_lvl)*NB_CHARACTER+i].sprite);
        
        (*ancien_lvl)=level;
    }

        
    img_charactere_inser(j1->characters,level,img_char,image);
    img_charactere_inser(o->characters,level,img_c_ordi,image);
        
    for(i=0;i<j1->characters->nb;i++){
        if(j1->characters->tab[i]->x == j1->characters->tab[i]->x_pred){
            frame_deplace=playerImg->x;
            playerImg->x=0;
            SDL_RenderCopy(rendu, img_char[i], playerImg, &playerPosition[i]);
            playerImg->x=frame_deplace;
        }else
            SDL_RenderCopy(rendu, img_char[i], playerImg, &playerPosition[i]);

    }
    for(i=0;i<o->characters->nb;i++){
        if(o->characters->tab[i]->x == o->characters->tab[i]->x_pred){
            frame_deplace=ordiImg->x;
            ordiImg->x=0;
            SDL_RenderCopy(rendu, img_c_ordi[i], ordiImg, &ordiPosition[i]);
            ordiImg->x=frame_deplace;
        }else
            SDL_RenderCopy(rendu, img_c_ordi[i], ordiImg, &ordiPosition[i]);
    }
}

/**
 * @brief Affiche les bâtiments en fonction de l'âge du joueur et de l'ordinateur.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 * @param building Tableau de textures des bâtiments.
 * @param cameraX Position horizontale de la caméra.
 * @param cameraY Position verticale de la caméra.
 * @param joueur_level Niveau du joueur.
 * @param ordi_level Niveau de l'ordinateur.
 */
void affichageBulding(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* building[],
                      int cameraX, int cameraY, int joueur_level, int ordi_level)
{
    int w, h;
    SDL_GetWindowSize(fenetre, &w, &h);

    SDL_Rect rect_build = {0, h - 300, 350, 291};
    SDL_Rect rect_build_ad = {IMAGE_WIDTH - 350, h - 300, 350, 291}; 

    /*Ajouter la position de la caméra à la position des bases*/
    /*Pour le déplacement de la caméra*/
    rect_build.x -= cameraX;
    rect_build.y -= cameraY;

    rect_build_ad.x -= cameraX;
    rect_build_ad.y -= cameraY;
    
    /*Affichage de la base du joueur en fonctions de l'age*/
    if(joueur_level == Prehistoire){
        SDL_RenderCopy(rendu, building[0], NULL, &rect_build);
    }
    else if(joueur_level == Antiquite){
        SDL_RenderCopy(rendu, building[2], NULL, &rect_build);
    }
    else if(joueur_level == Moyen_Age){
        SDL_RenderCopy(rendu, building[4], NULL, &rect_build);
    }
    else if(joueur_level == Ere_Moderne){
        SDL_RenderCopy(rendu, building[6], NULL, &rect_build);
    }
    else if(joueur_level == Ere_Futuriste){
        SDL_RenderCopy(rendu, building[8], NULL, &rect_build);
    }

    /*Affichage de la base de l'ordi en fonctions de l'age*/
    if(ordi_level == Prehistoire){
        SDL_RenderCopy(rendu, building[1], NULL, &rect_build_ad);
    }
    else if(ordi_level == Antiquite){
        SDL_RenderCopy(rendu, building[3], NULL, &rect_build_ad);
    }
    else if(ordi_level == Moyen_Age){
        SDL_RenderCopy(rendu, building[5], NULL, &rect_build_ad);
    }
    else if(ordi_level == Ere_Moderne){
        SDL_RenderCopy(rendu, building[7], NULL, &rect_build_ad);
    }
    else if(ordi_level == Ere_Futuriste){
        SDL_RenderCopy(rendu, building[9], NULL, &rect_build_ad);
    }
}

/**
 * @brief Affiche les points de vie des bases des joueurs.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param font Police de caractères pour le texte.
 * @param pointsDeVie_1 Points de vie de la base du joueur 1.
 * @param pointsDeVie_2 Points de vie de la base du joueur 2.
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 * @param cameraX Position horizontale de la caméra.
 * @param cameraY Position verticale de la caméra.
 */
void affichagePointDeVie(SDL_Renderer * rendu, TTF_Font * font, int pointsDeVie_1, int pointsDeVie_2, SDL_Window* fenetre, int cameraX, int cameraY)
{
    int w, h;
    /*Récupération dimension fenêtre*/
    SDL_GetWindowSize(fenetre, &w, &h);

    /*Convertir le nombre de points de vie en chaîne de caractères*/
    char * pv_1 = malloc(sizeof(char) * 10000);
    char * pv_2 = malloc(sizeof(char) * 10000);
    sprintf(pv_1, "PV : %d", pointsDeVie_1);
    sprintf(pv_2, "PV : %d", pointsDeVie_2);
    SDL_Surface * pv_1_surface = TTF_RenderUTF8_Solid(font, pv_1, BLACK);
    SDL_Surface * pv_2_surface = TTF_RenderUTF8_Solid(font, pv_2, BLACK);

    /*Affichage des rectangles translucide*/
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 128);
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
    SDL_Rect fond_g = {30, h - 400, pv_1_surface->w-15 , 50};
    SDL_Rect fond_d = {IMAGE_WIDTH - 250,  h - 400, pv_2_surface->w-15, 50};


    /*Ajouter la position de la caméra à la position des bases*/
    /*Pour le déplacement de la caméra*/
    fond_g.x -= cameraX;
    fond_d.x -= cameraX;
    SDL_RenderFillRect(rendu, &fond_d);
    SDL_RenderFillRect(rendu, &fond_g);

    SDL_Texture * pv_1_texture = SDL_CreateTextureFromSurface(rendu, pv_1_surface);
    SDL_Texture * pv_2_texture = SDL_CreateTextureFromSurface(rendu, pv_2_surface);

    SDL_Rect rect_pv_1 = {30, h - 400, pv_1_surface->w-15 , 50};;
    SDL_Rect rect_pv_2 = {IMAGE_WIDTH - 250,  h - 400, pv_2_surface->w-15, 50};
    
    // Ajouter la position de la caméra à la position de la base
    rect_pv_1.x -= cameraX;

    rect_pv_2.x -= cameraX;

    SDL_RenderCopy(rendu, pv_1_texture, NULL, &rect_pv_1);
    SDL_RenderCopy(rendu, pv_2_texture, NULL, &rect_pv_2);

    SDL_FreeSurface(pv_1_surface);
    SDL_FreeSurface(pv_2_surface);

    SDL_DestroyTexture(pv_1_texture);
    SDL_DestroyTexture(pv_2_texture);

    free(pv_1);
    free(pv_2);
}

/**
 * @brief Affiche les informations des personnages lorsque la souris survole leur image.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 * @param police Police de caractères pour le texte.
 * @param survol Indicateur du personnage survolé.
 * @param tab_charactere Tableau des caractéristiques des personnages.
 * @param age Âge actuel du jeu.
 * @param joueur Structure de données représentant le joueur.
 */
void affichageSurvolSouris(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police, int survol, character_t* tab_charactere, 
                           int age, player_t* joueur)
{
    char desc[100] = "";
    char cost[100] = "";
    char dammage[100] = "";
    char pv[100] = "";
    switch(survol){
        /*Affichage des information du perso1*/
        case PERSO1:
            /*Affichage du rectangle en fond*/
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 128);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
            SDL_Rect Perso1 = creationRectangle(fenetre, 250, 36 + TAILLE_SPRITE, 200, 80);
            SDL_RenderFillRect(rendu, &Perso1);

            /*Affichage des informations du personnages*/
            strcpy(desc, tab_charactere[age * NB_CHARACTER + 0].description);
            SDL_Surface * desc_0_surface = TTF_RenderUTF8_Solid(police, desc, WHITE);
            sprintf(cost, "Coût : %d", tab_charactere[age * NB_CHARACTER + 0].cost);
            SDL_Surface * cost_0_surface = TTF_RenderUTF8_Solid(police, cost, WHITE);
            sprintf(dammage, "Dégat : %d", tab_charactere[age * NB_CHARACTER + 0].dammage);
            SDL_Surface * dammage_0_surface = TTF_RenderUTF8_Solid(police, dammage, WHITE);
            sprintf(pv, "Pv : %d", tab_charactere[age * NB_CHARACTER + 0].max_pv);
            SDL_Surface * pv_0_surface = TTF_RenderUTF8_Solid(police, pv, WHITE);

            SDL_Texture * desc_0_texture = SDL_CreateTextureFromSurface(rendu, desc_0_surface);
            SDL_Texture * cost_0_texture = SDL_CreateTextureFromSurface(rendu, cost_0_surface);
            SDL_Texture * dammage_0_texture = SDL_CreateTextureFromSurface(rendu, dammage_0_surface);
            SDL_Texture * pv_0_texture = SDL_CreateTextureFromSurface(rendu, pv_0_surface);

            
            SDL_Rect desc_0_rect = creationRectangle(fenetre, 250, 100, 180, 20);
            SDL_Rect cost_0_rect = creationRectangle(fenetre, 250, 120, 130, 20);
            SDL_Rect dammage_0_rect = creationRectangle(fenetre, 250, 140, 130, 20);
            SDL_Rect pv_0_rect = creationRectangle(fenetre, 250, 160, 130, 20);

            
            SDL_RenderCopy(rendu, desc_0_texture, NULL, &desc_0_rect);
            SDL_RenderCopy(rendu, cost_0_texture, NULL, &cost_0_rect);
            SDL_RenderCopy(rendu, dammage_0_texture, NULL, &dammage_0_rect);
            SDL_RenderCopy(rendu, pv_0_texture, NULL, &pv_0_rect);

            SDL_FreeSurface(desc_0_surface);
            SDL_DestroyTexture(desc_0_texture);
            SDL_FreeSurface(cost_0_surface);
            SDL_DestroyTexture(cost_0_texture);
            SDL_FreeSurface(dammage_0_surface);
            SDL_DestroyTexture(dammage_0_texture);
            SDL_FreeSurface(pv_0_surface);
            SDL_DestroyTexture(pv_0_texture);
            break;

        /*Affichage des information du perso1*/
        case PERSO2:
            /*Affichage du rectangle en fond*/
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 128);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
            SDL_Rect Perso2 = creationRectangle(fenetre, 319, 36 + TAILLE_SPRITE, 200, 80);
            SDL_RenderFillRect(rendu, &Perso2);
            
            /*Affichage des informations du personnages*/
            strcpy(desc, tab_charactere[age * NB_CHARACTER + 1].description);
            SDL_Surface * desc_1_surface = TTF_RenderUTF8_Solid(police, desc, WHITE);
            sprintf(cost, "Coût : %d", tab_charactere[age * NB_CHARACTER + 1].cost);
            SDL_Surface * cost_1_surface = TTF_RenderUTF8_Solid(police, cost, WHITE);
            sprintf(dammage, "Dégat : %d", tab_charactere[age * NB_CHARACTER + 1].dammage);
            SDL_Surface * dammage_1_surface = TTF_RenderUTF8_Solid(police, dammage, WHITE);
            sprintf(pv, "Pv : %d", tab_charactere[age * NB_CHARACTER + 1].max_pv);
            SDL_Surface * pv_1_surface = TTF_RenderUTF8_Solid(police, pv, WHITE);

            SDL_Texture * desc_1_texture = SDL_CreateTextureFromSurface(rendu, desc_1_surface);
            SDL_Texture * cost_1_texture = SDL_CreateTextureFromSurface(rendu, cost_1_surface);
            SDL_Texture * dammage_1_texture = SDL_CreateTextureFromSurface(rendu, dammage_1_surface);
            SDL_Texture * pv_1_texture = SDL_CreateTextureFromSurface(rendu, pv_1_surface);

            
            SDL_Rect desc_1_rect = creationRectangle(fenetre, 319, 100, 180, 20);
            SDL_Rect cost_1_rect = creationRectangle(fenetre, 319, 120, 130, 20);
            SDL_Rect dammage_1_rect = creationRectangle(fenetre, 319, 140, 130, 20);
            SDL_Rect pv_1_rect = creationRectangle(fenetre, 319, 160, 130, 20);

        
            SDL_RenderCopy(rendu, desc_1_texture, NULL, &desc_1_rect);
            SDL_RenderCopy(rendu, cost_1_texture, NULL, &cost_1_rect);
            SDL_RenderCopy(rendu, dammage_1_texture, NULL, &dammage_1_rect);
            SDL_RenderCopy(rendu, pv_1_texture, NULL, &pv_1_rect);

            SDL_FreeSurface(desc_1_surface);
            SDL_DestroyTexture(desc_1_texture);
            SDL_FreeSurface(cost_1_surface);
            SDL_DestroyTexture(cost_1_texture);
            SDL_FreeSurface(dammage_1_surface);
            SDL_DestroyTexture(dammage_1_texture);
            SDL_FreeSurface(pv_1_surface);
            SDL_DestroyTexture(pv_1_texture);
            break;
    
        /*Affichage des information du perso1*/
        case PERSO3:
            /*Affichage du rectangle en fond*/
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 128);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
            SDL_Rect Perso3 = creationRectangle(fenetre, 388, 36 + TAILLE_SPRITE, 200, 80);
            SDL_RenderFillRect(rendu, &Perso3);
            
            /*Affichage des informations du personnages*/
            strcpy(desc, tab_charactere[age * NB_CHARACTER + 2].description);
            SDL_Surface * desc_2_surface = TTF_RenderUTF8_Solid(police, desc, WHITE);
            sprintf(cost, "Coût : %d", tab_charactere[age * NB_CHARACTER + 2].cost);
            SDL_Surface * cost_2_surface = TTF_RenderUTF8_Solid(police, cost, WHITE);
            sprintf(dammage, "Dégat : %d", tab_charactere[age * NB_CHARACTER + 2].dammage);
            SDL_Surface * dammage_2_surface = TTF_RenderUTF8_Solid(police, dammage, WHITE);
            sprintf(pv, "Pv : %d", tab_charactere[age * NB_CHARACTER + 2].max_pv);
            SDL_Surface * pv_2_surface = TTF_RenderUTF8_Solid(police, pv, WHITE);

            SDL_Texture * desc_2_texture = SDL_CreateTextureFromSurface(rendu, desc_2_surface);
            SDL_Texture * cost_2_texture = SDL_CreateTextureFromSurface(rendu, cost_2_surface);
            SDL_Texture * dammage_2_texture = SDL_CreateTextureFromSurface(rendu, dammage_2_surface);
            SDL_Texture * pv_2_texture = SDL_CreateTextureFromSurface(rendu, pv_2_surface);

            
            SDL_Rect desc_2_rect = creationRectangle(fenetre, 388, 100, 180, 20);
            SDL_Rect cost_2_rect = creationRectangle(fenetre, 388, 120, 130, 20);
            SDL_Rect dammage_2_rect = creationRectangle(fenetre, 388, 140, 130, 20);
            SDL_Rect pv_2_rect = creationRectangle(fenetre, 388, 160, 130, 20);

        
            SDL_RenderCopy(rendu, desc_2_texture, NULL, &desc_2_rect);
            SDL_RenderCopy(rendu, cost_2_texture, NULL, &cost_2_rect);
            SDL_RenderCopy(rendu, dammage_2_texture, NULL, &dammage_2_rect);
            SDL_RenderCopy(rendu, pv_2_texture, NULL, &pv_2_rect);

            SDL_FreeSurface(desc_2_surface);
            SDL_DestroyTexture(desc_2_texture);
            SDL_FreeSurface(cost_2_surface);
            SDL_DestroyTexture(cost_2_texture);
            SDL_FreeSurface(dammage_2_surface);
            SDL_DestroyTexture(dammage_2_texture);
            SDL_FreeSurface(pv_2_surface);
            SDL_DestroyTexture(pv_2_texture);
            
            break;
        
        /*Affichage des information du perso1*/
        case PERSO4:
            /*Affichage du rectangle en fond*/
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 128);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
            SDL_Rect Perso4 = creationRectangle(fenetre, 457, 36 + TAILLE_SPRITE, 200, 80);
            SDL_RenderFillRect(rendu, &Perso4);
            
            /*Affichage des informations du personnages*/
            strcpy(desc, tab_charactere[age * NB_CHARACTER + 3].description);
            SDL_Surface * desc_3_surface = TTF_RenderUTF8_Solid(police, desc, WHITE);
            sprintf(cost, "Coût : %d", tab_charactere[age * NB_CHARACTER + 3].cost);
            SDL_Surface * cost_3_surface = TTF_RenderUTF8_Solid(police, cost, WHITE);
            sprintf(dammage, "Dégat : %d", tab_charactere[age * NB_CHARACTER + 3].dammage);
            SDL_Surface * dammage_3_surface = TTF_RenderUTF8_Solid(police, dammage, WHITE);
            sprintf(pv, "Pv : %d", tab_charactere[age * NB_CHARACTER + 3].max_pv);
            SDL_Surface * pv_3_surface = TTF_RenderUTF8_Solid(police, pv, WHITE);

            SDL_Texture * desc_3_texture = SDL_CreateTextureFromSurface(rendu, desc_3_surface);
            SDL_Texture * cost_3_texture = SDL_CreateTextureFromSurface(rendu, cost_3_surface);
            SDL_Texture * dammage_3_texture = SDL_CreateTextureFromSurface(rendu, dammage_3_surface);
            SDL_Texture * pv_3_texture = SDL_CreateTextureFromSurface(rendu, pv_3_surface);

            
            SDL_Rect desc_3_rect = creationRectangle(fenetre, 457, 100, 180, 20);
            SDL_Rect cost_3_rect = creationRectangle(fenetre, 457, 120, 130, 20);
            SDL_Rect dammage_3_rect = creationRectangle(fenetre, 457, 140, 130, 20);
            SDL_Rect pv_3_rect = creationRectangle(fenetre, 457, 160, 130, 20);

        
            SDL_RenderCopy(rendu, desc_3_texture, NULL, &desc_3_rect);
            SDL_RenderCopy(rendu, cost_3_texture, NULL, &cost_3_rect);
            SDL_RenderCopy(rendu, dammage_3_texture, NULL, &dammage_3_rect);
            SDL_RenderCopy(rendu, pv_3_texture, NULL, &pv_3_rect);

            SDL_FreeSurface(desc_3_surface);
            SDL_DestroyTexture(desc_3_texture);
            SDL_FreeSurface(cost_3_surface);
            SDL_DestroyTexture(cost_3_texture);
            SDL_FreeSurface(dammage_3_surface);
            SDL_DestroyTexture(dammage_3_texture);
            SDL_FreeSurface(pv_3_surface);
            SDL_DestroyTexture(pv_3_texture);
            break;

        /*Affichage des information de l'XP*/
        case XP:
            /*Affichage du rectangle en fond*/
            SDL_SetRenderDrawColor(rendu, 0, 0, 0, 128);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
            SDL_Rect rect_XP = creationRectangle(fenetre, 15, 157, 200, 80);
            SDL_RenderFillRect(rendu, &rect_XP);

            switch(joueur->building->level){
                case Prehistoire:
                    strcpy(desc,"Prochain âge : Antiquité");
                    break;
                
                case Antiquite:
                    strcpy(desc,"Prochain âge : Moyen-Âge");
                    break;

                case Moyen_Age:
                    strcpy(desc,"Prochain âge : Moderne");
                    break;

                case Ere_Moderne:
                    strcpy(desc,"Prochain âge : Futuriste");
                    break;
                
                case Ere_Futuriste:
                    strcpy(desc,"Dernier âge");
                    break;
            }
            
            SDL_Surface * next_age_surface = TTF_RenderUTF8_Solid(police, desc, WHITE);
            SDL_Texture* next_age_texture = SDL_CreateTextureFromSurface(rendu, next_age_surface);
            SDL_Rect next_age_rect = creationRectangle(fenetre, 15, 157, 190, 40);
            SDL_RenderCopy(rendu, next_age_texture, NULL, &next_age_rect);
            SDL_FreeSurface(next_age_surface);
            SDL_DestroyTexture(next_age_texture);

            if(joueur->building->level != Ere_Futuriste){
                sprintf(cost,"Coût : %d XP", joueur->building->XP_cost);
            }
            else{
                strcpy(cost,"Gagnez la partie !");
            }
            
            SDL_Surface * next_age_xp_surface = TTF_RenderUTF8_Solid(police, cost, WHITE);
            SDL_Texture* next_age_xp_texture = SDL_CreateTextureFromSurface(rendu, next_age_xp_surface);
            SDL_Rect next_age_xp_rect = creationRectangle(fenetre, 15, 197, 190, 40);
            SDL_RenderCopy(rendu, next_age_xp_texture, NULL, &next_age_xp_rect);
            SDL_FreeSurface(next_age_xp_surface);
            SDL_DestroyTexture(next_age_xp_texture);
            
            break;

        
        default:
            break;
    }
}

/**
 * @brief Affiche l'image de victoire ou de défaite et un message associé.
 * 
 * @param rendu Renderer SDL pour le rendu des éléments.
 * @param font Police de caractères pour le texte.
 * @param choix Indicateur du résultat (victoire ou défaite).
 * @param fenetre Fenêtre SDL dans laquelle le rendu est effectué.
 * @param cameraX Position horizontale de la caméra.
 * @param cameraY Position verticale de la caméra.
 * @param win Texture de l'image de victoire.
 * @param lose Texture de l'image de défaite.
 */
void affichage_gagnant( SDL_Renderer * rendu, TTF_Font * font, int choix ,SDL_Window* fenetre, int cameraX, int cameraY, SDL_Texture * win, SDL_Texture * lose )
{
    int w, h, x, y;    
    SDL_GetWindowSize(fenetre, &w, &h);
    x = w/2;
    y = h/2;

    /* pour image */
    if (  choix == JOUEUR_GAGNE )
    {
        SDL_Rect rec_win = creationRectangle(fenetre, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_RenderCopy(rendu, win, NULL, &rec_win);
    }
    else
    {
        SDL_Rect rec_lose = creationRectangle(fenetre, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_RenderCopy(rendu, lose, NULL, &rec_lose);
    }

    /* affichage message */
    char * chaine = malloc(sizeof(char) * MAX_DESCRIPTION);
    strcpy(chaine,"APPUYER SUR UNE TOUCHE POUR CONTINUER...");
    SDL_Surface * surface2 = TTF_RenderUTF8_Solid(font, chaine, WHITE);;
    SDL_Texture * texture2 = SDL_CreateTextureFromSurface(rendu, surface2);
    SDL_Rect rect_winner2 = creationRectangle(fenetre, x-400, y+200, surface2->w, surface2->h);
    SDL_RenderCopy(rendu, texture2, NULL, &rect_winner2);
    SDL_FreeSurface(surface2);
    SDL_DestroyTexture(texture2);
    free(chaine);
}
