#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif

#ifndef SDL_h
#define SDL_h
#include <SDL2/SDL.h>
#endif

#ifndef SDL_ttf_h
#define SDL_ttf_h
#include "SDL2/SDL_ttf.h"
#endif

#ifndef SDL_image_h
#define SDL_image_h
#include "SDL2/SDL_image.h"
#endif

#ifndef tailleCharTab
#define tailleCharTab 255   //taille max (-1) des chaines de caractères
#endif

#ifndef tailleTuile
#define tailleTuile 64      //taille des tuiles en px
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
 * @brief Fonction Affichant le fond, les objets, le joueur (avec son arme)
 * 
 * @param renderer  Rendu
 * @param hauteur   Hauteur de la fenêtre (nombre de cellule texture)
 * @param largeur   Largeur de la fenêtre (nombre de cellule texture)
 * @param TabTuile  Tableau de textures pour les tuiles (fond)
 * @param cartePos  Tableau emplacement des tuiles
 * @param TabObjet  Tableau de textures pour les objets
 * @param nbObjet   Nombre d'objet à afficher
 * @param joueur    Toutes les informations du joueur
 * @param arme      Information de l'arme du joueur
 */
int Affichage(SDL_Renderer * renderer,int hauteur, int largeur,texture TabTuile[], int ** cartePos, texture * TabObjet, int nbObjet, texture joueur,texture arme);

/**
 * @brief Fonction Affichant le message de fin (VICTORY ou GAME OVER)
 * 
 * @param etat      Etat donnant l'information si défaite (0) sinon victoire
 * @param largeur   Largeur de la fenêtre (nombre de cellule texture)
 * @param hauteur   Hauteur de la fenêtre (nombre de cellule texture)
 * @param renderer  Rendu
 * @param police    Police / font
 * @param nomJoueur Nom du joueur
 * @param temps     Temps que le joueur a mis
 */
void messageFin(int etat, int largeur, int hauteur, SDL_Renderer * renderer,TTF_Font * police, char nomJoueur[],int temps);

/**
 * @brief Fonction affichant le temps et le meilleur jour / temps
 * 
 * @param renderer          Rendu
 * @param destination       Espace où le temps actuel sera affiché
 * @param messageMenu       Texture du temps du joueur actuel
 * @param meilleur          Texture du meilleur joueur / temps
 * @param espaceMeilleur    Espace où le meilleur joueur / temps sera affiché
 * @return int              -1 si erreur sinon 0
 */
int AffichageMenu(SDL_Renderer * renderer, SDL_Rect destination,SDL_Texture * messageMenu,SDL_Texture * meilleur, SDL_Rect espaceMeilleur);