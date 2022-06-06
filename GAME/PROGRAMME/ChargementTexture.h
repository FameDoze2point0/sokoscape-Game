#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif

#ifndef string_h
#define string_h
#include <string.h>
#endif

#ifndef SDL_h
#define SDL_h
#include <SDL2/SDL.h>
#endif

#ifndef SDL_image_h
#define SDL_image_h
#include "SDL2/SDL_image.h"
#endif

#ifndef SDL_ttf_h
#define SDL_ttf_h
#include "SDL2/SDL_ttf.h"
#endif

#ifndef tailleCharTab
#define tailleCharTab 255   //taille max (-1) des chaines de caractères
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
 * @brief Fonction qui va charger toutes les textures d'un tableau de texture dans le rendu
 * 
 * @param Tab           Tableau de texture
 * @param nbTexture     Le nombre de texture à charger dans le rendu
 * @param renderer      Le rendu
 * @return int          Renvoie le nombre de textures chargées ou -1 s'il y a une erreur
 */
int ChargementTexture(texture Tab[],int nbTexture, SDL_Renderer * renderer);

/**
 * @brief Charge le temps du joueur mais aussi le meilleur temps / joueur
 * 
 * @param id        0 on charge le meilleur joueur / temps, 1 le temps actuel du joueur
 * @param hauteur   Hauteur de la fenêtre en cellule texture
 * @param largeur   Largeur de la fenêtre en cellule texture
 * @param meilleur  Tableau de caractère correspondant au meilleur joueur + son temps
 * @param temps     Temps du joueur actuel
 * @param tempsTexture  Texture du temps actuel
 * @param meilleurTexture   Texture du meilleur temps / joueur
 * @param menuTemps     Espace où le temps sera affiché
 * @param menuMeilleur  Espace où le meilleur joueur / temps sera affiché
 * @param white         Couleur de la police
 * @param renderer      Rendu
 * @return int          Gestion d'erreur : 0 si pas d'erreur sinon -1
 */
int ChargementMenu(int id,int hauteur,int largeur,char meilleur[],char temps[], SDL_Texture ** tempsTexture, SDL_Texture ** meilleurTexture, SDL_Rect menuTemps, SDL_Rect menuMeilleur, SDL_Color white, SDL_Renderer * renderer);

/**
 * @brief Fonction qui détruit toutes les textures existante d'un tableau
 * 
 * @param Tab       Tableau de texture
 * @param nbTexture Nombre de texture
 */
void DestructionTexture(texture Tab[],int nbTexture);