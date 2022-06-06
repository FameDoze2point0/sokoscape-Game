#include "chargementFichier.h"

#include "ChargementTexture.h"

#include "Affichage.h"

#include "MouvementCollision.h"

#ifndef stdlib_h
#include <stdlib.h>
#endif

#ifndef stdio_h
#include <stdio.h>
#endif

#ifndef string_h
#include <string.h>
#endif

#ifndef SDL_h
#include "SDL2/SDL.h"
#endif

#ifndef math_h
#include <math.h>
#endif

#ifndef SDL_image_h
#include "SDL2/SDL_image.h"
#endif

#ifndef SDL_ttf_h
#include "SDL2/SDL_ttf.h"
#endif

#ifndef SDL_mixer_h
#include "SDL2/SDL_mixer.h"
#endif

#ifndef tailleCharTab
#define tailleCharTab 255
#endif
#ifndef nbrMaxTuile
#define nbrMaxTuile 30
#endif
#ifndef nbrMaxObjet
#define nbrMaxObjet 20
#endif
#ifndef tailleObjet
#define tailleObjet 46
#endif
#ifndef tailleTuile
#define tailleTuile 64
#endif
#ifndef vitesse
#define vitesse 10
#endif

// N'hésiter pas à mettre le curseur de la souris sur les fonctions personnalisées, il y a des informations sur leur(s) utilité(s)
// Tous les sons et images sont libres !
//Il se peut qu'il y ait des erreurs si vous essayez de joueur, cela est sûrement dû au timer, si vous voulez essayer dans de meilleures conditions vous pouvez mettre la ligne 478 en commentaire


int main(int argc, char const *argv[])
{
    char nom[tailleCharTab],meilleur[tailleCharTab]="AUCUN:0";
    int hauteur=0,largeur=0, nbrTuile=0,nbrObjet=0,nbrObjet2=0, jouer=1,vieJoueur=2;
    int ETAT=EXIT_SUCCESS,ERROR,etatfin;
    FILE * fichier=NULL;

    texture TabTuile[nbrMaxTuile];
    texture TabObjet[nbrMaxObjet];
    texture joueur;
    texture epee;
    SDL_Rect posDebut;
    int ** cartePos=NULL;

    SDL_Window * window=NULL;
    SDL_Renderer * renderer=NULL;

    Mix_Chunk * ambianceSon = NULL;
    Mix_Chunk * pasSon = NULL;
    Mix_Chunk * epeeSon = NULL;
    SDL_Event event;

    TTF_Font * police= NULL;
    TTF_Font * police2= NULL;
    int debut,fin,temps;
    char tempsChar[tailleCharTab];
    SDL_Texture * menuMessage=NULL;
    SDL_Texture * menuMessageMeilleur=NULL;
    SDL_Rect espaceMenu;
    SDL_Rect espaceMenuMeilleur;
    SDL_Color white={255,255,255};


    printf("\t\t=== Bienvenu sur le jeu ===\n\nLe but du jeu est de sortir de l'étage le plus vite possible, pour ce faire vous aurez des obstacles, cependant voici quelques indications :\n\n\t- Vous pouvez vous déplacer avec les flèches directionnelles\n\t- Vous pouvez attaquer avec 'ESPACE', attention à ne pas casser les caisses !\n\t- Vous pouvez revenir au début avec 'RETURN'\n\t- Pour quitter le jeu, faites 'ESCAPE' ou la croix\n\t- N'hésitez pas à allumer le son de l'ordinateur !\n\t- Attention au flac d'eau vous pourriez glisser dessus !\n\t- Attention à ne pas marcher dans un trou ou sur le feu si vous ne voulez pas mourir !\n\t- Vous pouvez remplir un trou avec une caisse\n\t- Vous avez 3 vies, si vous tombez dans un trou ou dans le feu vous revenez au début\n\n");

    NomJoueurFonc(nom,tailleCharTab); //récupération du nom du joueur
    fichier=fopen("../map/etage1.txt","r");
        if (fichier == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Le fichier n'a pas été trouvée\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    hauteur=hauteurFonc(fichier); //récupération de la hauteur
    largeur=largeurFonc(fichier); //récupération de la largeur
        if (hauteur == -1 || largeur ==-1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Au moins une des dimensions n'a pas été trouvée\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    nbrObjet=nbObjetFonc(fichier); //récupération du nombre d'objet
        if (nbrObjet == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Le nombre d'objet n'a pas été trouvé\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    nbrObjet2=objetFonc(fichier,TabObjet,nbrObjet);//récupération des adresses, des hitbox et du nombre d'objet réel
    nbrTuile=AdresseFonc(fichier,TabTuile,nbrMaxTuile);//récupération des adresses des tuiles, renvoie le nombre de tuiles différentes
        if (nbrTuile == -1 || nbrObjet2 == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Récupération des adresses des tuiles ou des objets\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    nbrTuile++; // + car on commence à 0

    //création d'un "tableau" à deux dimensions pour y mettre les emplacements de chaque tuile
    cartePos=(int**)malloc(hauteur*sizeof(int*));
    for (int i = 0; i < hauteur; i++)
    {
        cartePos[i]=(int*)malloc(largeur*sizeof(int));
    }

    ERROR=cartePosFonc(fichier,cartePos,hauteur,largeur); //récupération des emplacements
        if (ERROR != largeur*hauteur)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Récupération des emplacements des tuiles\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    ERROR=hitboxFonc(fichier,TabTuile);//Récupération des hitbox
        if (ERROR == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Récupération des hitbox des tuiles\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    joueur=joueurPosFonc(fichier,joueur,&posDebut);//récupération des informations sur le joueur
        if (joueur.angle == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Récupération du joueur\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    epee=armeFonc(fichier,epee); //récupération des informations sur l'arme
        if (epee.angle == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Récupération de l'épée\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    fclose(fichier);


    ERROR=SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO); //initialisation de l'audio et de la vidéo
        if (ERROR!=0)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Initialisation SDL (audio ou video)\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    ERROR=TTF_Init();
        if (ERROR != 0)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Initialisation TTF\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    ERROR=Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //ouverture de l'audio
        if (ERROR != 0)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Initialisation audio\n");
            goto fin;
        }
//----------------------------------------------------------------------------------------------------- 
    police=TTF_OpenFont("../font/Starjedi.ttf",50); // ouverture de la police Jedi
        if (police == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Police introuvable\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    police2=TTF_OpenFont("../font/font.ttf",50); // ouverture de la police basique 
        if (police2 == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Police introuvable\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    ERROR=Mix_AllocateChannels(3); // allocation de 3 canaux pour l'audio
        if (ERROR != 3)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Allocation des pistes audio\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    ambianceSon = Mix_LoadWAV("../sons/ambianceSon.mp3"); // chargement du son d'ambiance
        if (ambianceSon == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Son ambiance introuvable\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    pasSon = Mix_LoadWAV("../sons/courseSon.mp3"); // chargement du son des pas
        if (pasSon == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Son pas introuvable\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    epeeSon = Mix_LoadWAV("../sons/sonEpee.mp3");// chargement du son de l'épée
        if (epeeSon == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Son épée introuvable\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    //réglage du volument / MIX_MAX_VOLUME est le volume maximal
    Mix_Volume(0, MIX_MAX_VOLUME*0.70);
    Mix_Volume(1, MIX_MAX_VOLUME);
    Mix_Volume(2, MIX_MAX_VOLUME);

//-----------------------------------------------------------------------------------------------------
    //On joue les musiques sur les différentes pistes audio (-1 pour que ça soit en boucle), on met en pause les pas et l'épée
    Mix_PlayChannel(0,ambianceSon,-1);
    Mix_PlayChannel(1,pasSon,-1);
    Mix_PlayChannel(2,epeeSon,-1);
    Mix_Pause(1);
    Mix_Pause(2);
//-----------------------------------------------------------------------------------------------------
//Création de la fenetre
    window=SDL_CreateWindow("Etape 3 - CARPENTIER Antonin",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,largeur*tailleTuile,hauteur*tailleTuile,0);
        if (window == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement de la fenêtre\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
//Creation du rendu
    renderer=SDL_CreateRenderer(window,-1,0);
        if (renderer == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement du rendu\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    ERROR= ChargementTexture(TabTuile,nbrTuile,renderer); // chargement des textures des tuiles à partir des adresses
        if (ERROR == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement des textures (tuile)\n");
            goto fin;

        }
//-----------------------------------------------------------------------------------------------------
    ERROR= ChargementTexture(TabObjet,nbrObjet,renderer); // chargement des textures des objets à partir des adresses
        if (ERROR == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement des textures (objet)\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    joueur.texture=IMG_LoadTexture(renderer,joueur.adresse); // chargement de la texture du joueur
        if (joueur.texture == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement des textures (joueur)\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    epee.texture=IMG_LoadTexture(renderer,epee.adresse); // chargement de la texture de l'épée
        if (epee.texture == NULL)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement des textures (epee)\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------
    ERROR=meilleurSave(meilleur); // Recherche du meilleur temps
        if (ERROR==-1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement meilleur joueur\n");
            goto fin;
        }
//-----------------------------------------------------------------------------------------------------                   
    // on place le temps et le meilleur joueur / temps
        espaceMenuMeilleur.x=tailleTuile*8;
        espaceMenuMeilleur.y=(hauteur-1.1)*tailleTuile;
        espaceMenuMeilleur.w=strlen(meilleur)*20;
        espaceMenuMeilleur.h=tailleTuile*1.5;

        espaceMenu.x=tailleTuile*2;
        espaceMenu.y=(hauteur-1.1)*tailleTuile;
        espaceMenu.w=45;
        espaceMenu.h=tailleTuile*1.5;
//-----------------------------------------------------------------------------------------------------
// chargement du meilleur joueur / temps
    ERROR=ChargementMenu(0,hauteur,largeur,meilleur,tempsChar,&menuMessage,&menuMessageMeilleur,espaceMenu,espaceMenuMeilleur,white,renderer);
    if (ERROR == -1)
    {
        ETAT=EXIT_FAILURE;
        fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement meilleur joueur (rendu)\n");
        goto fin;
    }
//-----------------------------------------------------------------------------------------------------
    debut=SDL_GetTicks();
    while (jouer)
    {   
        ERROR=SDL_RenderClear(renderer); // on nettoie le rendu
        if (ERROR == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Effacement du rendu\n");
            goto fin;
        }
        // on recherche les potentielles événements
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN: // une touche est enfoncée

                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_ESCAPE: // échap-> on quitte
                            jouer=0;
                            break;
                        
                        case SDL_SCANCODE_LEFT: // on tourne à gauche
                            mouvement(1,&joueur);
                            mouvementRotation(1,&epee,joueur);
                            break;

                        case SDL_SCANCODE_RIGHT:// on tourne à droite
                            mouvement(2,&joueur);
                            mouvementRotation(2,&epee,joueur);
                            break;

                        case SDL_SCANCODE_UP:// on avance
                            Mix_Resume(1);
                            mouvement(3,&joueur);
                            mouvement(3,&epee);
                            //recherche des potentielles collisions
                            etatfin=collisionJoueurTuile(1,hauteur,largeur,&joueur,TabTuile,cartePos,TabObjet,nbrObjet,renderer,&epee);
                            if (etatfin == 1 )
                            {
                                collisionObjet(1,nbrObjet,&joueur,TabObjet, hauteur,largeur,cartePos,TabTuile,renderer,&epee);
                            }else if (etatfin == 2)
                            {
                                messageFin(1,largeur,hauteur,renderer,police,nom,temps);
                                jouer=0;
                                
                            }else if (etatfin == 0)
                            {
                                if (vieJoueur == 0)
                                {
                                    messageFin(0,largeur,hauteur,renderer,police,nom,temps);
                                    jouer=0;
                                }else{
                                    retourDebut(&joueur,&epee,posDebut);
                                    printf("Il vous reste : %d vie(s)\n",vieJoueur);
                                    vieJoueur--;
                                }
                            }
                            break;

                        case SDL_SCANCODE_DOWN: // on recule
                            Mix_Resume(1);
                            mouvement(4,&joueur);
                            mouvement(4,&epee);
                            etatfin=collisionJoueurTuile(0,hauteur,largeur,&joueur,TabTuile,cartePos,TabObjet,nbrObjet,renderer,&epee);
                            if (etatfin == 1 )
                            {
                                collisionObjet(0,nbrObjet,&joueur,TabObjet, hauteur,largeur,cartePos,TabTuile,renderer,&epee);
                            }else if (etatfin == 2)
                            {
                                messageFin(1,largeur,hauteur,renderer,police,nom,temps);
                                jouer=0;
                                
                            }else if (etatfin == 0)
                            {
                                if (vieJoueur == 0)
                                {
                                    messageFin(0,largeur,hauteur,renderer,police,nom,temps);
                                    jouer=0;
                                }else{
                                    retourDebut(&joueur,&epee,posDebut);
                                    printf("Il vous reste : %d vie(s)\n",vieJoueur);
                                    vieJoueur--;
                                    
                                }
                            }
                            
                                                            
                            break;
                        case SDL_SCANCODE_SPACE: // on attaque
                                Mix_Resume(2); // on fait le son de l'épée
                                animationCoup(&epee,renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbrObjet,joueur); // animation de l'épée
                                collisionArme(epee,nbrObjet,TabObjet); // vérification s'il y a une collision avec une caisse si oui on supprime
                                Mix_Pause(2); // on met en pause le son
                            break;
                        case SDL_SCANCODE_RETURN:
                            retourDebut(&joueur,&epee,posDebut);
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_QUIT: // si on clique sur la croix

                    jouer=0;
                    break;
                case SDL_KEYUP: // si on relève une otuche on met en pause les pas
                    Mix_Pause(1);
                    break;
                default:
                    break;
            }
        }
        ERROR=Affichage(renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbrObjet,joueur,epee); // affichage du joueur / tuile / objet / arme
        if (ERROR == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Affichage des textures\n");
            goto fin;
        }
        
        fin=SDL_GetTicks(); // récupératoin du temps et calcul de celui ci
        temps=(fin-debut)/(double)1000;
        sprintf(tempsChar,"%d",temps);
        // Chargement du temps en texture
        ERROR=ChargementMenu(1,hauteur,largeur,meilleur,tempsChar,&menuMessage,&menuMessageMeilleur,espaceMenu,espaceMenuMeilleur,white,renderer);
        if (ERROR == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Chargement du temps\n");
            goto fin;
        }
        //affichage du menu (temps, meilleur joueur / temps) 
        ERROR=AffichageMenu(renderer,espaceMenu,menuMessage,menuMessageMeilleur,espaceMenuMeilleur);
        if (ERROR == -1)
        {
            ETAT=EXIT_FAILURE;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Affichage menu\n");
            goto fin;
        }
        //Affichage du tout
        SDL_RenderPresent(renderer);
    }   

    fin: // label pour simplifier la gestion des erreurs pour éviter d'avoir beaucoup de else
//-----------------------------------------------------------------------------------------------------
//Destruction de la texture du temps
    if (menuMessage != NULL)
    {
        SDL_DestroyTexture(menuMessage);
    }
//-----------------------------------------------------------------------------------------------------
//Destruction de la texture du meilleur joueur / temps
    if (menuMessageMeilleur != NULL)
    {
        SDL_DestroyTexture(menuMessageMeilleur);
    }
//-----------------------------------------------------------------------------------------------------
//Destruction du son d'ambiance
    if (ambianceSon != NULL)
    {
        Mix_FreeChunk(ambianceSon);
    }
//-----------------------------------------------------------------------------------------------------
//Destruction du son des pas
    if (pasSon != NULL)
    {
        Mix_FreeChunk(pasSon);
    }
//-----------------------------------------------------------------------------------------------------
//Destruction du son de l'épée
    if (epeeSon != NULL)
    {
        Mix_FreeChunk(epeeSon);
    }
//-----------------------------------------------------------------------------------------------------
    if (cartePos != NULL)
    {
        for (int i = 0; i < hauteur; i++)
        {
            free(cartePos[i]);
        }
        free(cartePos);
    }
//-----------------------------------------------------------------------------------------------------
//Destruction des textures
    SDL_DestroyTexture(epee.texture);
    SDL_DestroyTexture(joueur.texture);
    DestructionTexture(TabObjet,nbrObjet);
    DestructionTexture(TabTuile,nbrTuile);
//-----------------------------------------------------------------------------------------------------
//Destruction du renderer et de la fenetre
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }
//-----------------------------------------------------------------------------------------------------
//destruction des polices
    if (police2 != NULL)
    {
        TTF_CloseFont(police2);
    }
    if (police != NULL)
    {
        TTF_CloseFont(police);
    }
//-----------------------------------------------------------------------------------------------------
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return ETAT;
}
