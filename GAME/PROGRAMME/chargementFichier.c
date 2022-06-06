#include "chargementFichier.h"

void MAJ(char Tab[]){
    int i=0;
    while (Tab[i]!='\0'){

        Tab[i]=toupper(Tab[i]);
        i++;
    }
}

void NomJoueurFonc(char nom[],int taille){
    char saisi;
    int i=0;
    for (int i = 0; i < taille; i++)
    {
        nom[i]='\0';
    }
    printf("Veuillez écrire votre nom : ");
    while ((saisi=getchar())!='\n' && i<taille-1)
    {
        nom[i]=saisi;
        i++;
    }
    MAJ(nom);
}

//Fonction cherchant la hauteur dans le fichier et renvoie celle-ci, (hauteur = -1 pour les getions des erreurs)
int hauteurFonc(FILE * fichier){
    char saisi[tailleCharTab], *token=NULL;
    int hauteur=-1;
    rewind(fichier);
    while (fgets(saisi,tailleCharTab-1,fichier)!=NULL){

        token=strtok(saisi,":");    //recupère le titre
        if (token!=NULL){

            MAJ(token);
            if (strcmp(token,"HAUTEUR")==0){

                token=strtok(NULL,"\n");
                if (token!=NULL){

                    if (sscanf(token,"%d",&hauteur)==EOF){

                        hauteur=-1;
                        fprintf(stderr,"[INFO]: Une erreur est survenue : La longueur n'a pas été trouvée");
                    }
                }            
                break;
            }
        }
    }
    return hauteur;
}
//Fonction cherchant la largeur dans le fichier et renvoie celle-ci, (largeur = -1 pour les getions des erreurs)
int largeurFonc(FILE * fichier){
    char saisi[tailleCharTab], *token=NULL;
    int largeur=-1;
    rewind(fichier);
    while (fgets(saisi,tailleCharTab-1,fichier)!=NULL){

        token=strtok(saisi,":");    //recupère le titre
        if (token!=NULL){

            MAJ(token);
            if (strcmp(token,"LARGEUR")==0){
                
                token=strtok(NULL,"\n");
                if (token!=NULL){

                    if (sscanf(token,"%d",&largeur)==EOF){

                        largeur=-1;
                        fprintf(stderr,"[INFO]: Une erreur est survenue : La largeur n'a pas été trouvée");
                    }
                }
                break;
            }
        }
    }
    return largeur;
}

int AdresseFonc(FILE * fichier,texture tuileTab[], int taille){
    char saisi[tailleCharTab], *token=NULL;
    int indice=0,indiceMax=-1;
    rewind(fichier);
    
    while (fgets(saisi,tailleCharTab-1,fichier)!=NULL && indice<taille){

        token=strtok(saisi,":"); //recupère le titre
        if (token!=NULL){
            MAJ(token);

            if (strcmp(token,"TUILE")==0){

                token=strtok(NULL,",");
                if (token!=NULL){

                    if (sscanf(token,"%d",&indice)!=EOF){

                        token=strtok(NULL,"\n");
                        if (token!=NULL){

                            strncpy(tuileTab[indice].adresse,token,254);
                            indiceMax=(indice>indiceMax)?indice:indiceMax;
                        }else{

                            indiceMax=-1;
                            break;
                        }
                    }else{

                        indiceMax=-1;
                        break;
                    }
                }else{
                    indiceMax=-1;
                    break;
                }
            }
        }
    }
    return indiceMax;
}

//Fonction nous donnant le nombre d'objet dans le fichier (-1 pour la gestion d'erreur)
int nbObjetFonc(FILE * fichier){
    char saisi[tailleCharTab], *token=NULL;
    int nbObjet=-1;
    rewind(fichier);
    while (fgets(saisi,tailleCharTab-1,fichier)!=NULL){

        token=strtok(saisi,":");    //recupère le titre
        if (token!=NULL){

            MAJ(token);
            if (strcmp(token,"NOBJETS")==0){
            
                token=strtok(NULL,"\n");
                if (token!=NULL){

                    if (sscanf(token,"%d",&nbObjet)==EOF){

                        nbObjet=-1;
                    }   
                }
                break;
            }
        }
    }
    return nbObjet;  
}

//À l'instar de AdresseFonc, cette fonction nous donne les adresses des objets (-1 pour la gestion d'erreur)
int objetFonc(FILE * fichier,texture TabObjet[],int MaxObjet){
    char saisi[tailleCharTab], *token=NULL;
    int indice=-1;
    rewind(fichier);

    while (indice<MaxObjet-1 && fgets(saisi,tailleCharTab-1,fichier)!=NULL){

        token=strtok(saisi,":");    //recupère le titre
        if (token!=NULL){

            MAJ(token);
            if (strcmp(token,"OBJET")==0){

                token=strtok(NULL,",");
                if (token!=NULL){

                    if (sscanf(token,"%d",&indice)==EOF){

                        indice=-1;
                        break;
                    }else{

                        token=strtok(NULL,",");

                        if (token!=NULL){

                            strncpy(TabObjet[indice].adresse,token,254);
                            token=strtok(NULL,",");
                            if (token!=NULL){

                                if (sscanf(token,"%d",&TabObjet[indice].hitbox.x)==EOF){

                                    indice=-1;
                                    break;
                                }else{

                                    token=strtok(NULL,",");
                                    if (token!=NULL){

                                        if (sscanf(token,"%d",&TabObjet[indice].hitbox.y)==EOF){

                                            indice=-1;
                                            break;
                                        }else{
                                            TabObjet[indice].hitbox.w=tailleObjet;
                                            TabObjet[indice].hitbox.h=tailleObjet;
                                        }
                                    }else{
                                        indice=-1;
                                        break;
                                    }
                                } 
                            }else{
                                indice=-1;
                                break;
                            }
                        }else{
                            indice=-1;
                            break;
                        }
                    }
                }else{
                    indice=-1;
                    break;
                }
            }
        }
    }
    return indice;
}

int cartePosFonc(FILE * fichier,int **cartePos,int hauteur,int largeur){
    char saisi[tailleCharTab], *token=NULL;
    int x=0;
    rewind(fichier);

    while (fgets(saisi,tailleCharTab-1,fichier)!=NULL){

        token=strtok(saisi,":");    //recupère le titre
        if (token!=NULL){

            MAJ(token);
            if (strcmp(token,"TAB")==0){
            
                for (int j = 0; j < hauteur; j++){

                    for (int i = 0; i < largeur; i++){

                        fscanf(fichier,"%d",&cartePos[j][i]);
                        x++;
                    }
                } 
                break;
            }
        }
    }
    return x;
}

int hitboxFonc(FILE * fichier, texture TabTuile[]){
    char saisi[tailleCharTab], *token=NULL;
    int indice=-8;
    rewind(fichier);

    while(fgets(saisi,tailleCharTab-1,fichier)!=NULL){

        token=strtok(saisi,":");
        if (token!=NULL)
        {
            MAJ(token);
            if (strcmp(token,"HITBOX")==0)
            {   
                token=strtok(NULL,",");
                if (token!=NULL)
                {
                    if (sscanf(token,"%d",&indice)!=EOF)
                    {
                        token=strtok(NULL,",");
                        if (token!=NULL)
                        {
                            if (sscanf(token,"%d",&TabTuile[indice].hitbox.x)!=EOF)
                            {
                                token=strtok(NULL,",");
                                if (token!=NULL)
                                {
                                    if (sscanf(token,"%d",&TabTuile[indice].hitbox.y)!=EOF)
                                    {
                                        token=strtok(NULL,",");
                                        if (token!=NULL)
                                        {
                                            if (sscanf(token,"%d",&TabTuile[indice].hitbox.w)!=EOF)
                                            {
                                                token=strtok(NULL,",");
                                                if (token!=NULL)
                                                {
                                                    if (sscanf(token,"%d",&TabTuile[indice].hitbox.h)==EOF)
                                                    {
                                                        indice=-1;
                                                        break;
                                                    }
                                                }else{
                                                    indice=-1;
                                                    break;
                                                }
                                            }else{
                                                indice=-1;
                                                break;
                                            }
                                        }else{
                                            indice=-1;
                                            break;
                                        }
                                    }else{
                                        indice=-1;
                                        break;
                                    }
                                }else{
                                    indice=-1;
                                    break;
                                }
                            }else{
                                indice=-1;
                                break;
                            }
                        }else{
                            indice=-1;
                            break;
                        }
                    }else{
                        indice=-1;
                        break;
                    }
                }else{
                    indice=-1;
                    break;
                }
            }
        }
    }
    return indice;
}


//Fonction allant chercher l'adresse et et les positions du joueur puis charge le tout dans le rendu
texture joueurPosFonc(FILE * fichier, texture joueur,SDL_Rect * debut){
    char saisi[tailleCharTab], *token=NULL;
    rewind(fichier);

    while (fgets(saisi,tailleCharTab,fichier)!=NULL){

        token=strtok(saisi,":");    //recupère le titre
        if (token!=NULL){

            MAJ(token);
            if (strcmp(token,"JOUEUR")==0){
            
                token=strtok(NULL,",");
                if (token!=NULL){
                    
                    strncpy(joueur.adresse,token,tailleCharTab-1);

                    token=strtok(NULL,",");
                    if (token!=NULL){

                        if (sscanf(token,"%d",&joueur.position.x)!=EOF){

                            debut->x=joueur.position.x;

                            token=strtok(NULL,"\n");
                            if (token!=NULL){

                                if (sscanf(token,"%d",&joueur.position.y)!=EOF){

                                    debut->y=joueur.position.y;

                                    joueur.position.w=tailleObjet;
                                    joueur.position.h=tailleObjet;

                                    joueur.angle=0;

                                    joueur.hitbox.x=joueur.position.x+7;
                                    joueur.hitbox.y=joueur.position.y+12;
                                    joueur.hitbox.w=32;
                                    joueur.hitbox.h=20;
                                }else{
                                    joueur.angle=-1;
                                    break;
                                }
                            }else{
                                joueur.angle=-1;
                                break;
                            } 
                        }else{
                            joueur.angle=-1;
                            break;
                        }   
                    }else{
                        joueur.angle=-1;
                        break;
                    }                        
                }else{
                    joueur.angle=-1;
                    break;
                }
            }
        }
    }
    return joueur;
}

texture armeFonc(FILE * fichier, texture arme){
    char saisi[tailleCharTab], *token=NULL;
    rewind(fichier);

    while (fgets(saisi,tailleCharTab,fichier)!=NULL){

        token=strtok(saisi,":");    //recupère le titre
        if (token!=NULL){

            MAJ(token);
            if (strcmp(token,"ARME")==0){
            
                token=strtok(NULL,",");
                if (token!=NULL){
                    
                    strncpy(arme.adresse,token,tailleCharTab-1);

                    token=strtok(NULL,",");
                    if (token!=NULL){

                        if (sscanf(token,"%d",&arme.position.x)!=EOF){

                            token=strtok(NULL,"\n");
                            if (token!=NULL){

                                if (sscanf(token,"%d",&arme.position.y)!=EOF){

                                    arme.position.w=tailleObjet;
                                    arme.position.h=tailleObjet;
                                    arme.angle=0;

                                    arme.hitbox.x=arme.position.x;
                                    arme.hitbox.y=arme.position.y;
                                    arme.hitbox.w=14;
                                    arme.hitbox.h=32;
                                }else{
                                    arme.angle=-1;
                                    break;
                                }
                            }else{
                                arme.angle=-1;
                                break;
                            } 
                        }else{
                            arme.angle=-1;
                            break;
                        }   
                    }else{
                        arme.angle=-1;
                        break;
                    }                        
                }else{
                    arme.angle=-1;
                    break;
                }
            }
        }
    }
    return arme;

}

int meilleurSave(char meilleur[]){
    FILE * fichier=NULL;
    char saisi[tailleCharTab],* token=NULL;
    char nom[tailleCharTab],meilleurTemps[tailleCharTab];
    int temps,max,etat=0;
    int erreur=0;
    fichier=fopen("saveTemps.txt","r");
    if (fichier==NULL)
    {
        erreur=-1;
        fprintf(stderr,"[INFO]: Une erreur est survenue : Le fichier des sauvegardes n'a pu être ouvert\n");
    }else{
        while (fgets(saisi,tailleCharTab-1,fichier)!=NULL)
        {
            token=strtok(saisi,",");
            strncpy(nom,token,tailleCharTab-1);
            token=strtok(NULL,"\n");
            sscanf(token,"%d",&temps);
            if (etat==0)
            {
                max=temps;
                strncpy(meilleur,nom,tailleCharTab-1);
                sprintf(meilleurTemps,"%d",max);
                etat=1;
            }
            if (temps<max)
            {
                max=temps;
                strncpy(meilleur,nom,tailleCharTab-1);
                sprintf(meilleurTemps,"%d",max);
            }
        }
        fclose(fichier);
        strncat(meilleur,meilleurTemps,tailleCharTab-1);
    }
    return erreur;
}