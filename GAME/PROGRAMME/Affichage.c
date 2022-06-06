#include "Affichage.h"

int Affichage(SDL_Renderer * renderer,int hauteur, int largeur,texture TabTuile[], int ** cartePos, texture * TabObjet, int nbObjet, texture joueur,texture arme){
    SDL_Rect image={0,0,64,64};
    int ERROR=0;
    for (int j = 0; j < hauteur; j++)
    {
        for (int i = 0; i < largeur; i++)
        {
            ERROR=SDL_RenderCopy(renderer,TabTuile[cartePos[j][i]].texture,NULL,&image);
            if (ERROR!=0){
                ERROR=-1;
                fprintf(stderr,"[INFO]: Une erreur est survenue : Affichage tuile\n");
                break;
            }  
            image.x+=tailleTuile;
        }
        image.x=0;
        image.y+=tailleTuile;
    }
    if (ERROR != -1)
    {
        for (int i = 0; i < nbObjet ; i++)
        {
            ERROR=SDL_RenderCopy(renderer,TabObjet[i].texture,NULL,&TabObjet[i].hitbox);
            if (ERROR!=0){
                ERROR=-1;
                fprintf(stderr,"[INFO]: Une erreur est survenue : Affichage objet\n");
                break;
            }
        }
        
    }
    if (ERROR != -1)
    {
        ERROR=SDL_RenderCopyEx(renderer,arme.texture,NULL,&arme.position,arme.angle,NULL,SDL_FLIP_NONE);
        if (ERROR!=0){
            ERROR=-1;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Affichage joueur\n");
        }
    }
    if (ERROR != -1)
    {
        ERROR=SDL_RenderCopyEx(renderer,joueur.texture,NULL,&joueur.position,joueur.angle,NULL,SDL_FLIP_NONE);
        if (ERROR!=0){
            ERROR=-1;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Affichage joueur\n");
        }
    }
    return ERROR;
}

void messageFin(int etat, int largeur, int hauteur, SDL_Renderer * renderer,TTF_Font * police, char nomJoueur[],int temps){
    FILE * fichier=NULL;
    SDL_Surface * texteSurface=NULL;
    SDL_Texture * message=NULL;
    SDL_Rect posMessage={largeur/4*tailleTuile,hauteur/4*tailleTuile,tailleTuile*largeur/2,tailleTuile*hauteur/2};
    int erreur=0;
    
    if (etat==0)
    {
        SDL_Color couleur={255,0,0};
        texteSurface=TTF_RenderText_Blended(police,"g a m e  o v e r  !",couleur);
        if (texteSurface==NULL)
        {
            erreur=1;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Le message de fin n'a pu être généré\n");
            printf("\n\n GAME OVER !\n");
        }

    }else{

        SDL_Color couleur={0,255,0};
        texteSurface=TTF_RenderText_Blended(police,"v i c t o r y  !",couleur);
        if (texteSurface==NULL)
        {
            
            fprintf(stderr,"[INFO]: Une erreur est survenue : Le message de fin n'a pu être généré (fin)\n");
            printf("\n\n VICTORY !\n");
        }
        fichier=fopen("saveTemps.txt","a");
        if (fichier==NULL)
        {
            erreur=1;
            fprintf(stderr,"[INFO]: Une erreur est survenue : Le fichier des sauvegardes n'a pu être ouvert\n");
        }else{
            fprintf(fichier,"%s:,%d\n",nomJoueur,temps);
            fclose(fichier);
        }
    }
    
    if (erreur!=1)
    {
        message=SDL_CreateTextureFromSurface(renderer,texteSurface);
        if (message!=NULL)
        {
            erreur=SDL_RenderCopy(renderer,message,NULL,&posMessage);
            if (erreur!=0)
            {
                fprintf(stderr,"[INFO]: Une erreur est survenue : La texture n'a pu être rendu (fin)\n");
                erreur=1;
            }else{
                SDL_RenderPresent(renderer);
                SDL_Delay(2000);
            }
        }else{
            fprintf(stderr,"[INFO]: Une erreur est survenue : La texture n'a pu être créée (fin)\n");
            erreur=1;
        }
        
    }
    SDL_DestroyTexture(message);
    SDL_FreeSurface(texteSurface);
}
int AffichageMenu(SDL_Renderer * renderer, SDL_Rect destination,SDL_Texture * messageMenu,SDL_Texture * meilleur, SDL_Rect espaceMeilleur){
    int erreur=0;

    erreur=SDL_RenderCopy(renderer,meilleur,NULL,&espaceMeilleur);
    if (erreur!=0)
    {
        fprintf(stderr,"[INFO]: Une erreur est survenue : La texture n'a pu être rendu (menu temps joueur)\n");
        erreur=1;
    }else{
        erreur=SDL_RenderCopy(renderer,messageMenu,NULL,&destination);
        if (erreur!=0)
        {
            fprintf(stderr,"[INFO]: Une erreur est survenue : La texture n'a pu être rendu (menu temps joueur)\n");
            erreur=1;
        }
    }
        
}