#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "affichage.h"
#include "deplacement_bobai.h"


int main() {
    int lignes = 5;
    int colonnes = 5;

    // Créer la grille
    int** grille = creer_grille(lignes, colonnes);


    afficher2(grille);
    //afficherbobail(grille);
    position_bobai(grille,1);
    afficher2(grille);
    // Libérer la mémoire allouée pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
    }

    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(grille);

    return 0;
}