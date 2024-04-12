#include "lib/affichage_jeu.h"

int cameraX = 0;
int cameraY = 0;

/*Affichage de l4HUD*/
void afficherHUD(SDL_Renderer* rendu, SDL_Window* fenetre)
{
    /*Calcul du milieu de l'écran*/
    int x = WINDOW_WIDTH / 2;
    int y = WINDOW_HEIGHT / 2;

    /*Affichage du bouton paramètre*/
    SDL_Texture* parametre = chargementImg(rendu, fenetre, "../img/parametre.png");
    SDL_Rect rect_parametre = creationRectangle(fenetre, WINDOW_WIDTH - 60, 10, 50, 50);
    SDL_RenderCopy(rendu, parametre, NULL, &rect_parametre);

    SDL_DestroyTexture(parametre);
}

/*Affichage de l'image de fond du jeu et gestion du déplacement de la souris pour défiler l'image*/
void afficherJeuFond(SDL_Renderer* rendu, SDL_Window* fenetre, char* path)
{
    /*Récupère les dimensions de la fenêtre*/
    int w, h;
    SDL_GetWindowSize(fenetre, &w, &h);
    
    /*Chargement de l'image à partir du chemin passé en paramètre*/
    SDL_Texture* fond_jeu = chargementImg(rendu, fenetre, path);

    /*Définir une marge de déplacement pour activer le déplacement de la caméra*/
    int margin = 20;

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

    /*Destruction des variables de travail*/
    SDL_DestroyTexture(fond_jeu);
}

void gestionAffichageFondJeu(SDL_Renderer* rendu, SDL_Window* fenetre, age_t etatAge)
{
    switch(etatAge){
        case Prehistoire:
            afficherJeuFond(rendu, fenetre, "../img/Fond/Préhistoire_v2.jpg");
            break;
        case Antiquite:
            afficherJeuFond(rendu, fenetre, "../img/Fond/Antiquité_v2.jpg");
            break;
        case Moyen_Age:
            afficherJeuFond(rendu, fenetre, "../img/Fond/Moyen-Âge_v2.jpg");
            break;
        case Ere_Moderne:
            afficherJeuFond(rendu, fenetre, "../img/Fond/Moderne_v2.jpg");
            break;
        case Ere_Futuriste:
            afficherJeuFond(rendu, fenetre, "../img/Fond/Futuriste_v2.jpg");
            break;
                
        default:
            afficherJeuFond(rendu, fenetre, "../img/Fond/Préhistoire_v2.jpg");
            break;
    }
}