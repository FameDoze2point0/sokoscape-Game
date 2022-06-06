#include "ChargementTexture.h"

int ChargementTexture(texture Tab[],int nbTexture, SDL_Renderer * renderer){
    int i;
    for (i = 0; i < nbTexture; i++)
    {
        Tab[i].texture=IMG_LoadTexture(renderer,Tab[i].adresse);
        if (Tab[i].texture == NULL)
        {
            i=-1;
            break;
        }
    }
    return i;
}

int ChargementMenu(int id,int hauteur,int largeur,char meilleur[],char temps[], SDL_Texture ** tempsTexture, SDL_Texture ** meilleurTexture, SDL_Rect menuTemps, SDL_Rect menuMeilleur, SDL_Color white, SDL_Renderer * renderer){
    SDL_Surface * surface=NULL;
    TTF_Font * police=TTF_OpenFont("../font/font.ttf",50);
    int erreur=0;
    if (id == 1)
    {
        surface=TTF_RenderText_Solid(police,temps,white);
        if (surface!=NULL)
        {
            *tempsTexture=SDL_CreateTextureFromSurface(renderer,surface);
            if (*tempsTexture!=NULL)
            {
                
            }else{
                fprintf(stderr,"[INFO]: Une erreur est survenue : La texture n'a pu être créée (menu meilleur joueur)\n");
                erreur=-1;
            }
        }else{
            fprintf(stderr,"[INFO]: Une erreur est survenue : Le message de fin n'a pu être généré (menu meilleur joueur)\n");
            erreur=-1;
        }
    }else{
        surface=TTF_RenderText_Solid(police,meilleur,white);
        if (surface!=NULL)
        {
            *meilleurTexture=SDL_CreateTextureFromSurface(renderer,surface);
            if (*meilleurTexture!=NULL)
            {
                
            }else{
                fprintf(stderr,"[INFO]: Une erreur est survenue : La texture n'a pu être créée (menu meilleur joueur)\n");
                erreur=-1;
            }
        }else{
            fprintf(stderr,"[INFO]: Une erreur est survenue : Le message de fin n'a pu être généré (menu meilleur joueur)\n");
            erreur=-1;
        }
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(police);
    return erreur;
}

void DestructionTexture(texture Tab[],int nbTexture){
    for (int i = 0; i < nbTexture; i++)
    {
        if (Tab[i].texture != NULL)
        {
            SDL_DestroyTexture(Tab[i].texture);
        }
    }
}