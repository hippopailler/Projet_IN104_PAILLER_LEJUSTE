#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <stdbool.h>

bool position_pion (CouleurPion** grille, CouleurPion joueur){
    int ligne;
    int colonne;
    for (int i=0; i<5;++i){
        for (int j=0;j<5;++j){
            if (grille[i][j]==VERT){
                if (joueur ==BLEU){
                    if (i==0){
                        return false;
                    }
                }
                if (joueur==ROUGE){
                    if (i==5){
                        return true;
                    }
                }
            ligne=i;
            colonne=j;
            }
        }
    }
}

