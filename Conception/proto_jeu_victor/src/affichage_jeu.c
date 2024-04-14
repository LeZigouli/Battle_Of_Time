#include "../lib/affichage_jeu.h"

int cameraX = 0;
int cameraY = 0;

/*Affichage de l4HUD*/
void afficherHUD(SDL_Renderer* rendu, SDL_Window* fenetre, TTF_Font* police_texte, SDL_Texture* parametre, 
                 SDL_Texture* upgrade, SDL_Texture* gold, SDL_Texture* xp, player_t* joueur, SDL_Texture** image)
{
    /*Affichage du bouton paramètre*/
    SDL_Rect rect_parametre = creationRectangle(fenetre, WINDOW_WIDTH - 60, 10, 50, 50);
    SDL_RenderCopy(rendu, parametre, NULL, &rect_parametre);

    /*Affichage du titre à côter du bouton paramètre*/
    afficherTitre(rendu, fenetre, WINDOW_WIDTH - 230, -20, 150, 100);

    /*Affichage du bouton d'upgrade*/
    SDL_Rect rect_upgrade = creationRectangle(fenetre, 20, 105, 50, 50);
    SDL_RenderCopy(rendu, upgrade, NULL, &rect_upgrade);

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

    SDL_Rect tete_perso = creationRectangle(fenetre, TAILLE_SPRITE * 0, TAILLE_SPRITE * 10, TAILLE_SPRITE, TAILLE_SPRITE); 
    /*Affichage de la tête des personnages dans les rectangles*/
    SDL_RenderCopy(rendu, image[0], &tete_perso, &Perso1);
    SDL_RenderCopy(rendu, image[1], &tete_perso, &Perso2);
    SDL_RenderCopy(rendu, image[2], &tete_perso, &Perso3);
    SDL_RenderCopy(rendu, image[3], &tete_perso, &Perso4);

}


/*Affichage de l'image de fond du jeu et gestion du déplacement de la souris pour défiler l'image*/
void afficherJeuFond(SDL_Renderer* rendu, SDL_Window* fenetre, SDL_Texture* fond_jeu)
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
    if (mouseX < margin && cameraX > 0) {
        cameraX -= SCROLL_SPEED;
    } else if (mouseX > w - margin) {
        cameraX += SCROLL_SPEED;
    }

    /*Calculer la position maximale de la caméra pour chaque axe*/
    int maxCameraX = IMAGE_WIDTH - w;


    /*Limitation des déplacements pour rester dans les limites de l'image*/
    /*Sur l'axe x*/
    if (cameraX < 0) {
        cameraX = 0;
    } else if (cameraX > maxCameraX){
        cameraX = maxCameraX;
    }

    /*Création des rectangles source(image) et destination(écran)*/
    SDL_Rect destRect =  {0, 0, w, h};
    SDL_Rect srcRect = {cameraX, cameraY, w, h};

    /*Nettoie le rendu et affiche l'image*/
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, fond_jeu, &srcRect, &destRect);

}

/*Affiche l'image de l'arrière plan en fonction de l'âge*/
void gestionAffichageFondJeu(SDL_Renderer* rendu, SDL_Window* fenetre, int* etatAge, 
                             SDL_Texture* prehistoire, SDL_Texture* antiquite, SDL_Texture* moyen_age,
                             SDL_Texture* moderne, SDL_Texture* futuriste, player_t* j1, ordi_t* o)
{
    /*Détermine le max du niveau des batiments entre l'ordi et le joueur*/
    (*etatAge) = max(j1->building->level, o->building->level);
    /*Affiche le fond correspondant*/
    switch((*etatAge)){
        case Prehistoire:
            afficherJeuFond(rendu, fenetre, prehistoire);
            break;
        case Antiquite:
            afficherJeuFond(rendu, fenetre, antiquite);
            break;
        case Moyen_Age:
            afficherJeuFond(rendu, fenetre, moyen_age);
            break;
        case Ere_Moderne:
            afficherJeuFond(rendu, fenetre, moderne);
            break;
        case Ere_Futuriste:
            afficherJeuFond(rendu, fenetre, futuriste);
            break;
                
        default:
            afficherJeuFond(rendu, fenetre, prehistoire);
            break;
    }
}

/*Fonction d'affichage du menu des options quand on est en jeu*/
void afficherOptionJeu(SDL_Renderer* rendu, TTF_Font* police, SDL_Window* fenetre)
{
    /*Calcul des positions x et y*/
    int menuX = (WINDOW_WIDTH - MENU_WIDTH) / 2;  // Position horizontale centrée pour le sous-menu
    int menuY = (WINDOW_HEIGHT - (4 * MENU_HEIGHT) + SPACING) / 2;  // Position verticale centrée pour le sous-menu

    /*Afficher les onglets du menu avec espacement*/
    afficherMenu(rendu, police, fenetre, "Reprendre", menuX, menuY, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Sauvegarder", menuX, menuY + MENU_HEIGHT + SPACING, MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Musique/Son", menuX, menuY + 2 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Résolution", menuX, menuY + 3 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
    afficherMenu(rendu, police, fenetre, "Retour au menu principal", menuX, menuY + 4 * (MENU_HEIGHT + SPACING), MENU_WIDTH, MENU_HEIGHT);
}