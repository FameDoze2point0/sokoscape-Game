#ifndef SDL_h
#define SDL_h
#include <SDL2/SDL.h>
#endif

#ifndef SDL_image_h
#include "SDL2/SDL_image.h"
#endif

#ifndef math_h
#define math_h
#include <math.h>
#endif


#ifndef SDL_ttf_h
#define SDL_ttf_h
#include "SDL2/SDL_ttf.h"
#endif

#ifndef tailleCharTab
#define tailleCharTab 255   //taille max (-1) des chaines de caractères
#endif

#ifndef vitesse
#define vitesse 10
#endif

#ifndef tailleTuile
#define tailleTuile 64
#endif

#ifndef STRUCT_TEXTURE
#define STRUCT_TEXTURE
    typedef struct texture{
        char adresse[tailleCharTab];
        SDL_Texture * texture;
        SDL_Rect position; // joueur
        SDL_Rect hitbox;
        double angle; // joueur
    }texture;
#endif
/**
 * @brief Fonction qui déplace le joueur (ou l'arme) dans une direction
 * 
 * @param id    ID : 1 gauche | 2 droite | 3 devant | 4 derrière
 * @param joueur    L'objet / joueur qu'il faut déplacer
 */
void mouvement(int id,texture * joueur);

/**
 * @brief Fonction qui permet de faire tourner l'arme autour du joueur
 * 
 * @param id    ID : 1 gauche | 2 droite
 * @param arme  Arme qu'il faut faire tourner
 * @param joueur Le joueur où l'arme tourne autour
 */
void mouvementRotation(int id,texture * arme, texture joueur);

/**
 * @brief Fonction qui vérifie s'il y a une collision entre un mur, un trou, le fleu, la flaque ou encore un bord de la carte
 * 
 * @param id        ID donnant le sens dans lequel le joueur va : 1 en avant | 0 an arrière
 * @param hauteur   Hauteur de la fenêtre (en nombre de cellule texture)
 * @param largeur   Largeur de la fenêtre (en nombre de cellule texture)
 * @param joueur    Le joueur concerné
 * @param TabTuile  Tableau des textures tuiles
 * @param cartePos  Emplacement des tuiles
 * @param TabObjet  Tableau des textures objets
 * @param nbObjet   Nombre d'objet
 * @param renderer  Rendu
 * @param epee      Epee du joueur
 * @return int      Retourne 0 si le joueur meurt | 1 si le joueur touche un mur | 2 si le joueur a gagné 
 */
int collisionJoueurTuile(int id, int hauteur,int largeur,texture *joueur, texture TabTuile[],int ** cartePos,texture TabObjet[], int nbObjet,SDL_Renderer * renderer,texture * epee);

/**
 * @brief   Fonction vérifiant s'il y a une collision entre un objet et un mur/ trou / feu ou encore un bord de la carte
 * 
 * @param id        ID donnant le sens dans lequel le joueur va : 1 en avant | 0 an arrière
 * @param numObjet 
 * @param objet 
 * @param hauteur   Hauteur de la fenêtre (en nombre de cellule texture)
 * @param largeur   Largeur de la fenêtre (en nombre de cellule texture)
 * @param cartePos 
 * @param TabTuile 
 * @param TabObjet 
 * @param nbObjet 
 * @param joueur 
 * @param renderer 
 * @param epee 
 */
void collisionObjetTuile(int id, int numObjet, texture * objet, int hauteur, int largeur, int ** cartePos,texture TabTuile[],texture TabObjet[],int nbObjet,texture joueur,SDL_Renderer * renderer,texture epee);

/**
 * @brief Fonction permettant de pousser la caisse via le joueur en vérifiant la collision entre eux
 * 
 * @param id        ID donnant le sens dans lequel le joueur va : 1 en avant | 0 an arrière
 * @param nbObjet 
 * @param joueur 
 * @param TabObjet 
 * @param hauteur 
 * @param largeur 
 * @param cartePos 
 * @param TabTuile 
 * @param renderer 
 * @param epee 
 */
void collisionObjet(int id, int nbObjet, texture * joueur,texture TabObjet[], int hauteur, int largeur, int ** cartePos,texture TabTuile[],SDL_Renderer * renderer,texture * epee);

/**
 * @brief Fonction faisant l'animation du coup d'épée
 * 
 * @param arme      Arme utilisée
 * @param renderer 
 * @param hauteur   Hauteur de la fenêtre (en nombre de cellule texture)
 * @param largeur   Largeur de la fenêtre (en nombre de cellule texture)
 * @param TabTuile 
 * @param cartePos 
 * @param TabObjet 
 * @param nbObjet 
 * @param joueur 
 */
void animationCoup(texture * arme,SDL_Renderer * renderer,int hauteur, int largeur, texture TabTuile[], int ** cartePos, texture TabObjet[],int nbObjet, texture joueur);

/**
 * @brief Fonction qui vérifie s'il y a une collision avec un objet, si oui il "supprime" l'objet en question
 * 
 * @param arme  
 * @param nbObjet   Nombre d'objet
 * @param TabObjet  Tableau des textures des objets    
 */
void collisionArme(texture arme,int nbObjet, texture TabObjet[]);

/**
 * @brief Fonction faisant revenir le joueur ainsi que son arme au début
 * 
 * @param joueur 
 * @param arme 
 * @param debut 
 */
void retourDebut(texture * joueur, texture * arme, SDL_Rect debut);