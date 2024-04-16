#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "affichage.h"
#include "position_bobai.h"
#include "case.h"
#include "position_pion.h"
#include "victoire.h"
#include "ordi_alea.h"
#include <time.h>

int main() {
    srand(time(NULL));
    int lignes = 5;
    int colonnes = 5;
    int choix;
    printf("Bienvenu dans ce jeu de BOBAIL augmenté par le numérique \n");
    printf("\n Contre qui voulez jouez : 1 pour local, 2 pour ordi\n");
    scanf("%d",&choix);
    CouleurPion** grille = creer_grille(lignes, colonnes);
    // on procède au switch pour séparer les différents modes de jeu : 1 contre 1/ contre ordi aléatoire / contre IA ?
    switch(choix){
        case 1:
            // Créer la grille de jeu
            CouleurPion joueur = BLEU;
            bool victory = false;
            afficher2(grille);
            position_bobai(grille,joueur); //premier tour, le joueur ne peut que déplacer l'un de ses pions
            afficher2(grille);
            joueur=ROUGE;

            while (! (victory)){
                position_bobai(grille,joueur);
                afficher2(grille);
                victory=victoire(grille,joueur);
                //le pion est arrivé à destination sur un des bords joueur
                if (victory){
                    if (joueur==ROUGE){
                        printf("Victoire du joueur rouge\n");
                    }
                    else{
                        printf("Victoire du joueur bleu\n");
                    }
                break;
                }

                position_pion(grille,joueur);
                afficher2(grille);

                victory=victoire(grille,joueur);
                //le bobail ne peut plus bouger
                if (victory){
                    if (joueur==ROUGE){
                        printf("Victoire du joueur rouge\n");
                    }
                    else{
                        printf("Victoire du joueur bleu\n");
                    }
                break;
                }


                if (joueur == ROUGE){
                    joueur=BLEU;
                }
                else {
                    joueur=ROUGE;
                }

            }

        case 2:{
            printf("Hello");
            // l'ordi aura les pions bleu dans un souci d'affichage
            //CouleurPion joueur=ROUGE;
            //bool victory = false;
            afficher2(grille);
            position_bobai_alea (grille);
            afficher2(grille);
            position_bobai_alea (grille);
            afficher2(grille);

        }
    }

    /*
    // Créer la grille de jeu
    CouleurPion** grille = creer_grille(lignes, colonnes);
    CouleurPion joueur = BLEU;
    bool victory = false;
    afficher2(grille);
    position_bobai(grille,joueur); //premier tour, le joueur ne peut que déplacer l'un de ses pions
    afficher2(grille);
    joueur=ROUGE;

    while (! (victory)){
        position_bobai(grille,joueur);
        afficher2(grille);
        victory=victoire(grille,joueur);
        //le pion est arrivé à destination sur un des bords joueur
        if (victory){
            if (joueur==ROUGE){
                printf("Victoire du joueur rouge\n");
            }
            else{
                printf("Victoire du joueur bleu\n");
            }
        break;
        }

        position_pion(grille,joueur);
        afficher2(grille);

        victory=victoire(grille,joueur);
        //le bobail ne peut plus bouger
        if (victory){
            if (joueur==ROUGE){
                printf("Victoire du joueur rouge\n");
            }
            else{
                printf("Victoire du joueur bleu\n");
            }
        break;
        }


        if (joueur == ROUGE){
            joueur=BLEU;
        }
        else {
            joueur=ROUGE;
        }

    }
    */
    // Libérer la mémoire allouée pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
    }

    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(grille);

    return 0;
}