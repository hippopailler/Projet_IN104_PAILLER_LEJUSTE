#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int** creer_grille(int lignes, int colonnes) {
    // Allouer de la mémoire pour le tableau de pointeurs
    int** grille = (int**)malloc(lignes * sizeof(int*));
    if (grille == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour chaque tableau d'entiers
    for (int i = 0; i < lignes; i++) {
        grille[i] = (int*)malloc(colonnes * sizeof(int));
        if (grille[i] == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    // Initialiser toutes les cases à zéro
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            grille[i][j] = 0;
        }
    }

    for (int j=0;j<5;j++){
        grille[0][j]=1; // joueur 1 représenté par des 1
        grille[4][j]=2; //joeuur 2 représenté par des 2 sur la grille
    }

    grille[2][2]=3;

    return grille;
}

void afficher(int** grille){
    printf("\n");
    // la grille est representée par un tableau d'entiers, il faut convertir ces données pour le visuel soit plus sympa
    for (int i=0;i<5;++i){
        for (int j=0;j<5;++j){
            if (grille[i][j]==0){
                printf(". ");
            }
            if (grille[i][j]==1){
                printf("O ");//le joueur sera représenté par des O
            }
            if (grille[i][j]==2){
                printf("X ");//l'ordinateur sera représenté par des X
            }
            if (grille[i][j]==3){
                printf("B ");//l'ordinateur sera représenté par des X
            }
        }
        printf("\n");
        
        
    }
printf("\n");
}

int main() {
    int lignes = 5;
    int colonnes = 5;

    // Créer la grille
    int** grille = creer_grille(lignes, colonnes);


    afficher(grille);

    // Libérer la mémoire allouée pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
    }

    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(grille);

    return 0;
}