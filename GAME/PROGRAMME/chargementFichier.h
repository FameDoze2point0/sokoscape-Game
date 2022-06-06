#ifndef SDL_h
#define SDL_h
#include <SDL2/SDL.h>
#endif

#ifndef tailleCharTab
#define tailleCharTab 255   //taille max (-1) des chaines de caractères
#endif

#ifndef tailleObjet
#define tailleObjet 46
#endif

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

void MAJ(char Tab[]);

/**
 * @brief  Fonction récupérant le nom du joueur
 * 
 * @param nom   Tableau qui contiendra le nom du joueur
 * @param taille    La taille max du tableau
 */
void NomJoueurFonc(char nom[],int taille);

/**
 * @brief Fonction cherchant la hauteur dans le fichier de la carte
 * 
 * @param fichier   Fichier de la carte
 * @return int  Hauteur de la carte (nombre de cellule "texture")
 */
int hauteurFonc(FILE * fichier);

//Fonction cherchant la largeur dans le fichier et renvoie celle-ci, (largeur = -1 pour les getions des erreurs)
/**
 * @brief Fonction cherchant la largeur dans le fichier de la carte
 * 
 * @param fichier   Fichier de la carte
 * @return int  Largeur de la carte (nombre de cellule "texture")
 */
int largeurFonc(FILE * fichier);


/**
 * @brief Fonction cherchant l'adresse de chaque tuile différente
 * 
 * @param fichier   Fichier de la carte
 * @param tuileTab  Tableau des textures
 * @param taille    Nombre maximum de texture différente
 * @return int  Nombre de texture différente
 */
int AdresseFonc(FILE * fichier,texture tuileTab[], int taille);

/**
 * @brief Fonction cherchant le nombre d'objet dans le fichier de la carte
 * 
 * @param fichier   Fichier de la carte
 * @return int  Nombre d'objet dans la carte
 */
int nbObjetFonc(FILE * fichier);

/**
 * @brief Fonction allant chercher l'adresse des objets, mais aussi la hitbox (zone de collision)
 * 
 * @param fichier   Fichier de la carte
 * @param TabObjet  Tableau des objets
 * @param MaxObjet  Nombre d'objet maximum
 * @return int Nombre d'objet trouvé
 */
int objetFonc(FILE * fichier,texture TabObjet[],int MaxObjet);

/**
 * @brief Fonction cherchant où vont les tuiles
 * 
 * @param fichier   Fichier de la carte
 * @param cartePos  Tableau qui contiendra les position des tuiles
 * @param hauteur   Hauteur de la fenêtre en nombre de cellule "texture"
 * @param largeur   Largeur de la fenêtre en nombre de cellule "texture"
 * @return int  Nombre de cellule au total
 */
int cartePosFonc(FILE * fichier,int **cartePos,int hauteur,int largeur);

/**
 * @brief Fonction allant chercher les zones de collision pour chaque texture différente
 * 
 * @param fichier   Fichier de la carte
 * @param TabTuile  Tableau de tuiles
 * @return int  Le nombre de hitbox différene trouvée
 */
int hitboxFonc(FILE * fichier, texture TabTuile[]);

/**
 * @brief Fonction allant chercher l'adresse, la position et la hitbox du personnage
 * 
 * @param fichier   Fichier de la carte
 * @param joueur    Joueur
 * @param debut     Position initiale du joueur
 * @return texture  Joueur
 */
texture joueurPosFonc(FILE * fichier, texture joueur,SDL_Rect * debut);

/**
 * @brief Fonction allant chercher l'adresse, la position et la hitbox de l'arme
 * 
 * @param fichier   Fichier de la carte
 * @param arme      Arme
 * @return texture  Arme
 */
texture armeFonc(FILE * fichier, texture arme);

/**
 * @brief Fonction allant chercher le meilleur joueur avec son temps
 * 
 * @param meilleur  Tableau qui contiendra le nom et le temps du meilleur joueur
 * @return int      Erreur 
 */
int meilleurSave(char meilleur[]);