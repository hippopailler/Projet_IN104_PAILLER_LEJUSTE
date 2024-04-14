#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"


CouleurPion** creer_grille(int lignes, int colonnes) {
    // Allouer de la mémoire pour le tableau de pointeurs
    CouleurPion** grille = (CouleurPion**)malloc(lignes * sizeof(CouleurPion*));
    //test de l'allocation mémoire
    if (grille == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour chaque tableau d'entiers
    for (int i = 0; i < lignes; i++) {
        grille[i] = (CouleurPion*)malloc(colonnes * sizeof(CouleurPion));
        //Nouveau test d'allocation mémoire
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
        grille[0][j]=BLEU; // joueur 1 représenté par des pions bleus
        grille[4][j]=ROUGE; //joeuur 2 représenté par des pions rouges
        //les types enum bleu/rouge/vert et blanc sont définis dans le header case
    }

    grille[2][2]=VERT;

    return grille;
}
//Première version de l'affichage, toute simple
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

// Définition des caractères Unicode pour les disques pleins
#define DISQUE_JOUEUR "\xE2\x97\x8F"
#define DISQUE_ORDINATEUR "\xE2\x97\xBC" //actuellement le joueur 2 mais sera utilisé par la suite par l'IA
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
                    printf(BLUE DISQUE_JOUEUR " " RESET); // Joueur
                    break;
                case ROUGE:
                    printf(RED DISQUE_ORDINATEUR " " RESET); // Ordinateur
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

