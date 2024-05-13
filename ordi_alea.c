#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <time.h>
#include <stdbool.h>


/*
Pour cette version de l'IA on procède par un jeu aléatoire
Etape 1 : choix d'un pion en aléatoire
Etape 2 : vérifier que ce pion peut bouger 
Etape 3 : choisir un des déplacements en aléatoire
Etape 4 : réaliser le mouvement 

On initiale le temps pour la fonction rand dans la fonction main.
*/

CouleurPion** position_bobai_alea (CouleurPion** grille){
    //srand(time(NULL));
    int ligne = (rand()%3)-1;
    int colonne = (rand ()%3)-1;
    int ligne_b;
    int colonne_b;
    for (int i =0; i<5; i++){
        for (int j= 0; j<5; j++){
            if (grille[i][j]==VERT){
                ligne_b=i;
                colonne_b=j;
            }
        }
     }
     
     if ((ligne_b+ligne)<=4 && (ligne_b+ligne)>=0 && (colonne_b+colonne)<=4 && (colonne_b+colonne)>=0 ){
        if (grille[ligne_b+ligne][colonne_b+colonne]==BLANC){
            grille[ligne_b+ligne][colonne_b+colonne]=VERT;
            grille[ligne_b][colonne_b]=BLANC;
        }
        else{
            position_bobai_alea(grille);
        }
     }
     else {
        position_bobai_alea(grille);
     }
    return grille;
}



CouleurPion** position_pion_alea (CouleurPion** grille){
//on choisit un nombre entre 0 et 4 puis on parcourt la grille on s'arrête au Xème pion rencontré, puis on le bouge dans un direction aléatoire en vérifiant au préalable qu'il peut bien bouger
    int choix = (rand() %5); //le temps est initialisé dans le main
    //printf("choix  =%d\n",choix);
    int compteur = 0;
    int ligne_p; //pour récupérer les coordonnées du pion
    int colonne_p;
    for (int i =0; i<5; i++){
        for (int j= 0; j<5; j++){
            if (grille[i][j] == BLEU){
                if (compteur == choix){
                    ligne_p = i;
                    colonne_p = j;
                    compteur+=1;
                }
                else{
                    compteur+=1;
                }
            }
        
        }
    }
    //printf("i =%d; j=%d\n",ligne_p ,colonne_p);

    // on vérifie que le pion peut bien bouger --> existence d'une case blanche autour de lui et on compte le nombre de possibilité
    int nb_choix = 0;
    for (int i=-1;i<=1;++i){
        for (int j=-1;j<=1;++j){
            if (0<=ligne_p+i && ligne_p+i<=4){
                if (0<=colonne_p+j && colonne_p+j<=4){
                    if (grille[ligne_p+i][colonne_p+j]==BLANC){
                        nb_choix+=1;
                    }
                }
            }
        }
    }

    if (nb_choix==0){ //aucune case blanche on relance la fonction en espérant tomber sur un autre pion --> les 5 pions ne peuvent pas être bloqué au même temps
        position_pion_alea(grille);
    }

    int coup=(rand()%(nb_choix)); //on choisit aléatoirement un des coups possibles

    // on récupère les coordonnées du début du mouvement
    int debut_i;
    int debut_j=2;
    int repere=0;
    //printf("coup = %d\n", coup);
    for (int i=-1;i<=1;++i){
        for (int j=-1;j<=1;++j){
            if (0<=ligne_p+i && ligne_p+i<=4){
                if (0<=colonne_p+j && colonne_p+j<=4){
                    if (grille[ligne_p+i][colonne_p+j]==BLANC){
                        
                        if (repere == coup){
                            debut_i=ligne_p+i;
                            debut_j=colonne_p+j;
                            repere +=1;
                        }
                        else{
                            repere += 1;
                        }
                        
                    }
                    /*
                    if (repere == coup && grille[ligne_p+i][colonne_p+j]==BLANC ){
                        debut_i=ligne_p+i;
                        debut_j=colonne_p+j;
                        repere +=1;
                    }
                    else{
                        repere +=1;
                    }
                    */
                }
            }
        }
    }
    //printf("i_d = %d, j_deb = %d\n",debut_i,debut_j);

    // maintenant on deplace le pion jusqu'à rencontrer un obstacle ou le bord du terrain.

    bool indicateur = true; //déplacement en cours
    int decalage_ligne = debut_i - ligne_p; //ces deux variables vont nous permettre de caractériser le déplacement sans faire de disjonctions suivant le type de déplacement
    int decalage_colonne= debut_j - colonne_p;
    int fin_i =ligne_p;
    int fin_j=colonne_p;
    int p=1;
    while(indicateur){
        if (ligne_p + p*decalage_ligne <=4 && ligne_p + p*decalage_ligne >=0 && colonne_p + p*decalage_colonne <=4 && colonne_p + p*decalage_colonne >=0){
            if (grille[ligne_p + (p+1)*decalage_ligne][colonne_p+ (p+1)*decalage_colonne]!=BLANC){
                fin_i=ligne_p + p*decalage_ligne;
                fin_j=colonne_p+ p*decalage_colonne;
                indicateur=false;
                //printf("1\n");
            }
            else {
                p+=1;
            }
        }
        else{
            fin_i=ligne_p + (p-1)*decalage_ligne;
            fin_j=colonne_p+ (p-1)*decalage_colonne;
            //printf("2\n");
            indicateur=false;
        }
    }
    //printf("%d,%d\n",fin_i,fin_j);
    grille[fin_i][fin_j]=BLEU;
    grille[ligne_p][colonne_p]=BLANC;
    return grille;
}
