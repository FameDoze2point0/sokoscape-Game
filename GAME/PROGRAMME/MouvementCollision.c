#include "MouvementCollision.h"

#include "Affichage.h"


void mouvement(int id,texture * joueur){
    switch (id)
    {
    case 1:
        (*joueur).angle-=3*vitesse;
        if ((*joueur).angle<0)(*joueur).angle+=360;
        break;
    case 2:
        (*joueur).angle+=3*vitesse;
        if ((*joueur).angle>360)(*joueur).angle-=360;
        break;
    case 3:
        (*joueur).position.x-=vitesse*sin((*joueur).angle/180*M_PI);
        (*joueur).position.y+=vitesse*cos((*joueur).angle/180*M_PI);
        (*joueur).hitbox.x-=vitesse*sin((*joueur).angle/180*M_PI);
        (*joueur).hitbox.y+=vitesse*cos((*joueur).angle/180*M_PI);
        break;
    case 4:
        (*joueur).position.x+=vitesse*sin((*joueur).angle/180*M_PI);
        (*joueur).position.y-=vitesse*cos((*joueur).angle/180*M_PI);
        (*joueur).hitbox.x+=vitesse*sin((*joueur).angle/180*M_PI);
        (*joueur).hitbox.y-=vitesse*cos((*joueur).angle/180*M_PI);
        break;
    default:
        break;
    }
}
void mouvementRotation(int id,texture * arme, texture joueur){
    switch (id)
    {
    case 1:
        (*arme).angle-=3*vitesse;
        if ((*arme).angle<0)(*arme).angle+=360;
        (*arme).position.x=joueur.position.x+cos((*arme).angle/180*M_PI);
        (*arme).position.y=joueur.position.y+sin((*arme).angle/180*M_PI);
        break;
    case 2:
        (*arme).angle+=3*vitesse;
        if ((*arme).angle>360)(*arme).angle-=360;
        (*arme).position.x=joueur.position.x+cos((*arme).angle/180*M_PI);
        (*arme).position.y=joueur.position.y+sin((*arme).angle/180*M_PI);
        break;
    default:
        break;
    }
}
int collisionJoueurTuile(int id, int hauteur,int largeur,texture *joueur, texture TabTuile[],int ** cartePos,texture TabObjet[], int nbObjet,SDL_Renderer * renderer,texture * epee){
    int i,j;
    SDL_Rect image;
    int rep=1,collision=0;
    for (int j = 0; j < hauteur; j++)
    {
        for (int i = 0; i < largeur; i++)
        {
            image.x=i*tailleTuile+TabTuile[cartePos[j][i]].hitbox.x;
            image.y=j*tailleTuile+TabTuile[cartePos[j][i]].hitbox.y;
            image.w=TabTuile[cartePos[j][i]].hitbox.w;
            image.h=TabTuile[cartePos[j][i]].hitbox.h;
            if (SDL_HasIntersection(&(*joueur).hitbox,&image))
            {
                if (cartePos[j][i] == 23)
                {
                    rep=0;
                }else if (cartePos[j][i] == 25)
                {
                    rep=0;
                }else if (cartePos[j][i] == 24)
                {
                    for (j = 0; j < hauteur; j++)
                    {
                        for (i = 0; i < largeur; i++)
                        {
                            image.x=i*tailleTuile+TabTuile[cartePos[j][i]].hitbox.x;
                            image.y=j*tailleTuile+TabTuile[cartePos[j][i]].hitbox.y;
                            image.w=TabTuile[cartePos[j][i]].hitbox.w;
                            image.h=TabTuile[cartePos[j][i]].hitbox.h;
                            while (SDL_HasIntersection(&(*joueur).hitbox,&image))
                            {
                                
                                if (id == 0)
                                {
                                    (*joueur).position.x+=vitesse*sin((*joueur).angle/180*M_PI);
                                    (*joueur).position.y-=vitesse*cos((*joueur).angle/180*M_PI);
                                    (*joueur).hitbox.x+=vitesse*sin((*joueur).angle/180*M_PI);
                                    (*joueur).hitbox.y-=vitesse*cos((*joueur).angle/180*M_PI);

                                    (*epee).position.x+=vitesse*sin((*epee).angle/180*M_PI);
                                    (*epee).position.y-=vitesse*cos((*epee).angle/180*M_PI);
                                }else{
                                    (*joueur).position.x-=vitesse*sin((*joueur).angle/180*M_PI);
                                    (*joueur).position.y+=vitesse*cos((*joueur).angle/180*M_PI);
                                    (*joueur).hitbox.x-=vitesse*sin((*joueur).angle/180*M_PI);
                                    (*joueur).hitbox.y+=vitesse*cos((*joueur).angle/180*M_PI);

                                    (*epee).position.x-=vitesse*sin((*epee).angle/180*M_PI);
                                    (*epee).position.y+=vitesse*cos((*epee).angle/180*M_PI);
                                }
                                
                                
                                Affichage(renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbObjet,*joueur,*epee);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(20);
                                SDL_RenderClear(renderer);
                            }
                        }
                    }
                    while (!collision)
                    {
                    
                        for (j = 0; j < hauteur; j++)
                        {
                            for (i = 0; i < largeur; i++)
                            {
                                image.x=i*tailleTuile+TabTuile[cartePos[j][i]].hitbox.x;
                                image.y=j*tailleTuile+TabTuile[cartePos[j][i]].hitbox.y;
                                image.w=TabTuile[cartePos[j][i]].hitbox.w;
                                image.h=TabTuile[cartePos[j][i]].hitbox.h;
                                if (SDL_HasIntersection(&(*joueur).hitbox,&image))
                                {
                                    collision=1;
                                    break;
                                }
                            }
                        }
                        if (id == 0)
                        {
                            (*joueur).position.x+=vitesse*sin((*joueur).angle/180*M_PI);
                            (*joueur).position.y-=vitesse*cos((*joueur).angle/180*M_PI);
                            (*joueur).hitbox.x+=vitesse*sin((*joueur).angle/180*M_PI);
                            (*joueur).hitbox.y-=vitesse*cos((*joueur).angle/180*M_PI);

                            (*epee).position.x+=vitesse*sin((*epee).angle/180*M_PI);
                            (*epee).position.y-=vitesse*cos((*epee).angle/180*M_PI);
                        }else{
                            (*joueur).position.x-=vitesse*sin((*joueur).angle/180*M_PI);
                            (*joueur).position.y+=vitesse*cos((*joueur).angle/180*M_PI);
                            (*joueur).hitbox.x-=vitesse*sin((*joueur).angle/180*M_PI);
                            (*joueur).hitbox.y+=vitesse*cos((*joueur).angle/180*M_PI);

                            (*epee).position.x-=vitesse*sin((*epee).angle/180*M_PI);
                            (*epee).position.y+=vitesse*cos((*epee).angle/180*M_PI);
                        }
                        Affichage(renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbObjet,*joueur,*epee);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(20);
                        SDL_RenderClear(renderer);
                    }
                    if (id == 1)
                    {
                        (*joueur).position.x+=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).position.y-=vitesse*cos((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.x+=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.y-=vitesse*cos((*joueur).angle/180*M_PI);

                        (*epee).position.x+=vitesse*sin((*epee).angle/180*M_PI);
                        (*epee).position.y-=vitesse*cos((*epee).angle/180*M_PI);
                    }else{
                        (*joueur).position.x-=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).position.y+=vitesse*cos((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.x-=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.y+=vitesse*cos((*joueur).angle/180*M_PI);

                        (*epee).position.x-=vitesse*sin((*epee).angle/180*M_PI);
                        (*epee).position.y+=vitesse*cos((*epee).angle/180*M_PI);
                    }
                    
                }else if (cartePos[j][i] == 15 || cartePos[j][i] == 16 || cartePos[j][i] == 17 || cartePos[j][i] == 18)
                {
                    rep=2;
                }else{

                    if (id == 1)
                    {
                        (*joueur).position.x+=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).position.y-=vitesse*cos((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.x+=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.y-=vitesse*cos((*joueur).angle/180*M_PI);

                        (*epee).position.x+=vitesse*sin((*epee).angle/180*M_PI);
                        (*epee).position.y-=vitesse*cos((*epee).angle/180*M_PI);
                    }else{
                        (*joueur).position.x-=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).position.y+=vitesse*cos((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.x-=vitesse*sin((*joueur).angle/180*M_PI);
                        (*joueur).hitbox.y+=vitesse*cos((*joueur).angle/180*M_PI);

                        (*epee).position.x-=vitesse*sin((*epee).angle/180*M_PI);
                        (*epee).position.y+=vitesse*cos((*epee).angle/180*M_PI);
                    }
                }
 
            }
        }
    }
    return rep;
}
void collisionObjetTuile(int id, int numObjet, texture * objet, int hauteur, int largeur, int ** cartePos,texture TabTuile[],texture TabObjet[],int nbObjet,texture joueur,SDL_Renderer * renderer,texture epee){
    int i,j,collision=0;
    SDL_Rect image;

    for (int j = 0; j < hauteur; j++)
    {
        for (int i = 0; i < largeur; i++)
        {
            image.x=i*tailleTuile+TabTuile[cartePos[j][i]].hitbox.x;
            image.y=j*tailleTuile+TabTuile[cartePos[j][i]].hitbox.y;
            image.w=TabTuile[cartePos[j][i]].hitbox.w;
            image.h=TabTuile[cartePos[j][i]].hitbox.h;
            if (SDL_HasIntersection(&(*objet).hitbox,&image))
            {
                if (cartePos[j][i] == 23)
                {
                    (*objet).hitbox.x=-100;
                    (*objet).hitbox.y=-100;
                    cartePos[j][i]=26;
                }else if (cartePos[j][i] == 25)
                {
                    (*objet).hitbox.x=-100;
                    (*objet).hitbox.y=-100;
                }else if (cartePos[j][i] == 24)
                {
                    for (j = 0; j < hauteur; j++)
                    {
                        for (i = 0; i < largeur; i++)
                        {
                            image.x=i*tailleTuile+TabTuile[cartePos[j][i]].hitbox.x;
                            image.y=j*tailleTuile+TabTuile[cartePos[j][i]].hitbox.y;
                            image.w=TabTuile[cartePos[j][i]].hitbox.w;
                            image.h=TabTuile[cartePos[j][i]].hitbox.h;
                            while (SDL_HasIntersection(&(*objet).hitbox,&image))
                            {
                                if (id == 1)
                                {
                                    (*objet).hitbox.x-=vitesse*sin(joueur.angle/180*M_PI);
                                    (*objet).hitbox.y+=vitesse*cos(joueur.angle/180*M_PI);
                                }else{
                                    (*objet).hitbox.x+=vitesse*sin(joueur.angle/180*M_PI);
                                    (*objet).hitbox.y-=vitesse*cos(joueur.angle/180*M_PI);
                                }
                                
                                Affichage(renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbObjet,joueur,epee);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(20);
                                SDL_RenderClear(renderer);
                            }
                        }
                    }
                    while (!collision)
                    {
                        for (j = 0; j < hauteur; j++)
                        {
                            for (i = 0; i < largeur; i++)
                            {
                                image.x=i*tailleTuile+TabTuile[cartePos[j][i]].hitbox.x;
                                image.y=j*tailleTuile+TabTuile[cartePos[j][i]].hitbox.y;
                                image.w=TabTuile[cartePos[j][i]].hitbox.w;
                                image.h=TabTuile[cartePos[j][i]].hitbox.h;
                                if (SDL_HasIntersection(&(*objet).hitbox,&image))
                                {
                                    collision=1;
                                    break;
                                }
                            }
                        }
                        if (id == 1)
                        {
                            (*objet).hitbox.x-=vitesse*sin(joueur.angle/180*M_PI);
                            (*objet).hitbox.y+=vitesse*cos(joueur.angle/180*M_PI);
                        }else{
                            (*objet).hitbox.x+=vitesse*sin(joueur.angle/180*M_PI);
                            (*objet).hitbox.y-=vitesse*cos(joueur.angle/180*M_PI);
                        }
                        
                        Affichage(renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbObjet,joueur,epee);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(20);
                        SDL_RenderClear(renderer);
                    }
                    if (id == 0)
                    {
                        (*objet).hitbox.x-=vitesse*sin(joueur.angle/180*M_PI);
                        (*objet).hitbox.y+=vitesse*cos(joueur.angle/180*M_PI);
                    }else{
                        (*objet).hitbox.x+=vitesse*sin(joueur.angle/180*M_PI);
                        (*objet).hitbox.y-=vitesse*cos(joueur.angle/180*M_PI);
                    }
                }else{
                    if (id == 0)
                    {
                        (*objet).hitbox.x-=vitesse*sin(joueur.angle/180*M_PI);
                        (*objet).hitbox.y+=vitesse*cos(joueur.angle/180*M_PI);
                    }else{
                        (*objet).hitbox.x+=vitesse*sin(joueur.angle/180*M_PI);
                        (*objet).hitbox.y-=vitesse*cos(joueur.angle/180*M_PI);
                    }
                }
            }
            
        }
        
    }
    
}
void collisionObjet(int id, int nbObjet, texture * joueur,texture TabObjet[], int hauteur, int largeur, int ** cartePos,texture TabTuile[],SDL_Renderer * renderer,texture * epee){

    for (int i = 0; i < nbObjet; i++)
    {
        if (SDL_HasIntersection(&(*joueur).hitbox,&TabObjet[i].hitbox))
        {
            if (id == 1)
            {
                TabObjet[i].hitbox.x-=vitesse*sin((*joueur).angle/180*M_PI);
                TabObjet[i].hitbox.y+=vitesse*cos((*joueur).angle/180*M_PI);

                (*joueur).hitbox.x+=vitesse*sin((*joueur).angle/180*M_PI);
                (*joueur).hitbox.y-=vitesse*cos((*joueur).angle/180*M_PI);
                (*joueur).position.x+=vitesse*sin((*joueur).angle/180*M_PI);
                (*joueur).position.y-=vitesse*cos((*joueur).angle/180*M_PI);
                
                (*epee).position.x+=vitesse*sin((*epee).angle/180*M_PI);
                (*epee).position.y-=vitesse*cos((*epee).angle/180*M_PI);

            }else{
                TabObjet[i].hitbox.x+=vitesse*sin((*joueur).angle/180*M_PI);
                TabObjet[i].hitbox.y-=vitesse*cos((*joueur).angle/180*M_PI);
            
                (*joueur).hitbox.x-=vitesse*sin((*joueur).angle/180*M_PI);
                (*joueur).hitbox.y+=vitesse*cos((*joueur).angle/180*M_PI);
                (*joueur).position.x-=vitesse*sin((*joueur).angle/180*M_PI);
                (*joueur).position.y+=vitesse*cos((*joueur).angle/180*M_PI);

                (*epee).position.x-=vitesse*sin((*epee).angle/180*M_PI);
                (*epee).position.y+=vitesse*cos((*epee).angle/180*M_PI);
            }
            collisionObjetTuile(id,i,&TabObjet[i], hauteur,largeur,cartePos,TabTuile,TabObjet,nbObjet,*joueur,renderer,*epee);
        }
    }
}


void animationCoup(texture * arme,SDL_Renderer * renderer,int hauteur, int largeur, texture TabTuile[], int ** cartePos, texture TabObjet[],int nbObjet, texture joueur){
    for (int i = 0; i < 20; i++)
    {
        SDL_RenderClear(renderer);
        (*arme).position.x-=vitesse*sin((*arme).angle/180*M_PI)/10;
        (*arme).position.y+=vitesse*cos((*arme).angle/180*M_PI)/10;
        Affichage(renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbObjet,joueur,*arme);
        SDL_Delay(5);
        SDL_RenderPresent(renderer);
    }
    for (int i = 0; i < 20; i++)
    {
        SDL_RenderClear(renderer);
        (*arme).position.x+=vitesse*sin((*arme).angle/180*M_PI)/10;
        (*arme).position.y-=vitesse*cos((*arme).angle/180*M_PI)/10;
        Affichage(renderer,hauteur,largeur,TabTuile,cartePos,TabObjet,nbObjet,joueur,*arme);
        SDL_Delay(5);
        SDL_RenderPresent(renderer);
    }
}
void collisionArme(texture arme,int nbObjet, texture TabObjet[]){
    for (int i = 0; i < nbObjet; i++)
    {
        if (SDL_HasIntersection(&arme.position,&TabObjet[i].hitbox))
        {
            TabObjet[i].hitbox.x=-100;
            TabObjet[i].hitbox.y=-100;
        }
    }
}
void retourDebut(texture * joueur, texture * arme, SDL_Rect debut){
    (*joueur).position.x=debut.x;
    (*joueur).position.y=debut.y;
    (*joueur).hitbox.x=debut.x+7;
    (*joueur).hitbox.y=debut.y+12;
    (*joueur).angle=0;
    (*arme).position.x=debut.x;
    (*arme).position.y=debut.y;
    (*arme).angle=0;
}