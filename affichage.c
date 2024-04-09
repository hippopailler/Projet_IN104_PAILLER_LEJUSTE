#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"


CouleurPion** creer_grille(int lignes, int colonnes) {
    // Allouer de la mémoire pour le tableau de pointeurs
    CouleurPion** grille = (CouleurPion**)malloc(lignes * sizeof(CouleurPion*));
    if (grille == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour chaque tableau d'entiers
    for (int i = 0; i < lignes; i++) {
        grille[i] = (CouleurPion*)malloc(colonnes * sizeof(CouleurPion));
        if (grille[i] == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    // Initialiser toutes les cases à zéro
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            grille[i][j] = BLANC;
        }
    }

    for (int j=0;j<5;j++){
        grille[0][j]=BLEU; // joueur 1 représenté par des 1
        grille[4][j]=ROUGE; //joeuur 2 représenté par des 2 sur la grille
    }

    grille[2][2]=VERT;

    return grille;
}

void afficher(CouleurPion** grille){
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


#include <stdio.h>

// Définition des caractères Unicode pour les disques pleins
#define DISQUE_JOUEUR "\xE2\x97\x8F"
#define DISQUE_ORDINATEUR "\xE2\x97\xBC"
#define DISQUE_BOBAIL "\xE2\x97\x8D"

// Définition des couleurs ANSI
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define BLUE    "\x1B[34m"
#define GREEN   "\x1B[32m"

void afficher2(CouleurPion** grille) {
    printf("\n");
    // Affichage des numéros de colonnes centrés
    printf("     0   1   2   3   4  \n");
    // Ligne de séparation supérieure
    printf("   \xE2\x94\x8C\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xAC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xAC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xAC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xAC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\x90\n");
    // Affichage de la grille avec les lignes et colonnes
    for (int i = 0; i < 5; ++i) {
        // Affichage du numéro de ligne
        printf("%d  ", i );
        
        for (int j = 0; j < 5; ++j) {
            // Ligne verticale à gauche de chaque cellule
            printf("\xE2\x94\x82 ");
            
            // Affichage des éléments de la grille
            switch (grille[i][j]) {
                case BLANC:
                    printf(". "); // Case vide
                    break;
                case BLEU:
                    printf(RED DISQUE_JOUEUR " " RESET); // Joueur
                    break;
                case ROUGE:
                    printf(BLUE DISQUE_ORDINATEUR " " RESET); // Ordinateur
                    break;
                case VERT:
                    printf(GREEN DISQUE_BOBAIL " " RESET); // Bobail
                    break;
                default:
                    printf("? "); // Valeur inconnue
                    break;
            }
        }
        // Ligne verticale à droite de la dernière cellule de chaque ligne
        printf("\xE2\x94\x82\n");
        // Ligne de séparation horizontale entre les lignes de la grille
        if (i < 4) {
            printf("   \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xA4\n");
        } else {
            // Ligne de séparation inférieure
            printf("   \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xBC\xE2\x94\x80\xE2\x94\x80\xE2\x94\x80\xE2\x94\xA4\n");
        }
    }
    printf("\n");
}

/*void afficherbobail(int** grille) {
    printf("\n");
    // Récupération de la position du bobail
    int hauteur = 0;
    int largeur = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grille[i][j] == 3) {
                hauteur = i;
                largeur = j;
            }
        }
    }

    // Définition des décalages pour les positions autour du bobail
    int decalage_i[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int decalage_j[8] = {1, 0, -1, 1, -1, 1, 0, -1};

    // Affichage de la grille avec les nombres de 1 à 8 autour de la position du bobail
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (grille[i][j] == 0) {
                printf(". ");
            } else if (grille[i][j] == 1) {
                printf("O "); // Le joueur sera représenté par des O
            } else if (grille[i][j] == 2) {
                printf("X "); // L'ordinateur sera représenté par des X
            } else if (grille[i][j] == 3) {
                printf("B "); // Le bobail
            } else {
                // Recherche des positions autour du bobail
                int afficher_nombre = 0;
                for (int k = 0; k < 8; k++) {
                    int ni = hauteur + decalage_i[k];
                    int nj = largeur + decalage_j[k];
                    if (ni >= 0 && ni < 5 && nj >= 0 && nj < 5 && grille[ni][nj] == 3) {
                        printf("%d ", k + 1);
                        afficher_nombre = 1;
                        break;
                    }
                }
                if (!afficher_nombre) {
                    printf(". "); // Si aucun nombre n'a été affiché, imprimer un point
                }
            }
        }
        printf("\n");
    }
}*/ 
// Au final cette fonction n'est pas super utile et assez compliquée à implémenter, on procédera à des coups type bataille pour faciliter les choses.


/*int main() {
    int lignes = 5;
    int colonnes = 5;

    // Créer la grille
    int** grille = creer_grille(lignes, colonnes);


    afficher2(grille);
    //afficherbobail(grille);
    // Libérer la mémoire allouée pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
    }

    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(grille);

    return 0;
}
*/