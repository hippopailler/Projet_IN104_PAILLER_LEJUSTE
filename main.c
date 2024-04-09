#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "affichage.h"
#include "position_bobai.h"
#include "case.h"
#include "position_pion.h"

int main() {
    int lignes = 5;
    int colonnes = 5;
    printf("Bienvenu dans ce jeu de BOBAIL augmenté par le numérique");
    // Créer la grille de jeu
    CouleurPion** grille = creer_grille(lignes, colonnes);
    CouleurPion joueur = BLEU;
    //bool encours = true;
    afficher2(grille);
    position_bobai(grille,joueur); //premier tour, le joueur ne peut que déplacer l'un de ses pions
    /*afficher2(grille);
    joueur=ROUGE;
    while (encours){
        position_bobai(grille,joueur);
        afficher2(grille);
        position_pion(grille,joueur);
        afficher2(grille);
        if (joueur == ROUGE){
            joueur=BLEU;
        }
        else {
            joueur=ROUGE;
        }

    }
    */
    afficher2(grille);

    position_bobai(grille,BLEU);
    afficher2(grille);
    // Libérer la mémoire allouée pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
    }

    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(grille);

    return 0;
}