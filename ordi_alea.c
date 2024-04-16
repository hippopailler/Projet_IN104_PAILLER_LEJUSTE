#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <time.h>

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
