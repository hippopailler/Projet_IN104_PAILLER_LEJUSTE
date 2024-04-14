#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <stdbool.h>

bool victoire (CouleurPion** grille, CouleurPion joueur){
    // passage de la variable victory en true pour marqué une fin de partie
    // récupération position bobail
    int ligne;
    int colonne;
    for (int i=0; i<5;++i){
        for (int j=0;j<5;++j){
            if (grille[i][j]==VERT){
                if (joueur ==BLEU){
                    if (i==0){
                        printf("bord");
                        return true;
                    }
                }
                if (joueur==ROUGE){
                    if (i==4){
                        printf("bord");
                        return true;
                    }
                }
            ligne=i;
            colonne=j;
            }
        }
    }
    // le bobail peut-il encore bouger ? existence d'une case blanche autour de lui ?

    for (int i=-1;i<=1;++i){
        for (int j=-1;j<=1;++j){
            //on vérifie les sorties de terrain
            if (0<=ligne+i && ligne+i<=4){
                if (0<=colonne+j && colonne+j<=4){
                    if (grille[ligne+i][colonne+j]==BLANC){
                        return false;
                    }
                }
            }
        }
    }
    //aucune case blanche autour du bobail
    printf("calins");
    return true;
}

