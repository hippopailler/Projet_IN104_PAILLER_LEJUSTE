#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h> // Pour la fonction sleep()
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
    CouleurPion joueur;
    
    printf("\n Bienvenue dans ce jeu de BOBAIL augmenté par le numérique. \n \n Le Bobail est un ancien jeu traditionnel africain dans lequel on essai de ramener le pion central, appelé Bobail, dans son camp. Les pions ne peuvent pas se sauter mais servent d'obstacles.\n ");
    printf("\n");
    //sleep(6);
    printf("Regles : \n Les joueurs jouent à tour de rôle. \n A chaque tour, le joueur déplace d’abord le bobail puis un de ses pions. \n Le Bobail se déplace dans tous les sens d’une seule case à la fois. \n Les pions se déplacent également dans toutes les directions mais ils doivent aller au bout de leur déplacement (jusqu’au bord du plateau ou jusqu’à rencontrer un autre pion ou le Bobail).\n ");
    printf("\n");
    //sleep(10);
    printf("Victoire : \n Ramener le Bobail sur une case où se trouvaient ses propres pions au début. \n Ou \n Encercler le Bobail afin que l’adversaire ne puisse pas le déplacer au début de son tour.\n");
    printf("\n");
    //sleep(5);
    printf("Premier tour : \n  Le joueur qui commence la partie, ne déplace pas le Bobail. Il déplace uniquement un de ses pions. \n");
    printf("\n");
    //sleep(3);
    printf("Contre qui voulez jouer : taper 1 pour jouer contre votre ami, taper 2 pour jouer contre un ordinateur : \n");
    
    int ret =scanf("%d",&choix);
    if (ret != 1) {
        printf("Format invalide. Veuillez saisir un entier.\n");
        // Pour vider le tampon d'entrée en cas de saisie incorrecte
        while (getchar() != '\n'); // Vide le tampon jusqu'à la fin de ligne
        return 0;
    }
    CouleurPion** grille = creer_grille(lignes, colonnes);
    // on procède au switch pour séparer les différents modes de jeu : 1 contre 1/ contre ordi aléatoire / contre IA ?
    switch(choix){
        case 1:
            // on pourrait demander le nom des joueurs ?

            // Créer la grille de jeu

            joueur = BLEU;
            CouleurPion victory = BLANC;
            afficher2(grille);
            position_pion(grille,joueur); //premier tour, le joueur ne peut que déplacer l'un de ses pions
            afficher2(grille);
            joueur=ROUGE;

            while (victory == BLANC){
                position_bobai(grille,joueur);
                afficher2(grille);
                victory=victoire(grille,joueur);
                if (victory == ROUGE){
                        printf("Victoire du joueur Rouge\n");
                        break;}
                else if (victory == BLEU){
                        printf("Victoire du joueur Bleu\n");
                        break;
                    }
                
                

                position_pion(grille,joueur);
                afficher2(grille);

                victory=victoire(grille,joueur);
                if (victory == ROUGE){
                        printf("Victoire du joueur Rouge\n");
                        break; }
                else if (victory == BLEU){
                        printf("Victoire du joueur Bleu\n");
                        break; 
                    }
                    


                if (joueur == ROUGE){
                    joueur=BLEU;
                }
                else {
                    joueur=ROUGE;
                }

            }
            break; 

        case 2:
            printf("Hello and welcome\n");
            // l'ordi aura les pions bleu dans un souci d'affichage
            
            //Creer la grille 
            victory = BLANC;

            // mouvement ordi
            position_pion_alea(grille, BLEU);
            afficher2(grille);

            joueur = ROUGE;

            while (victory == BLANC){
                position_bobai(grille,ROUGE);
                afficher2(grille);
                victory=victoire(grille,joueur);
                if (victory == ROUGE){
                        printf("Victoire du joueur Rouge\n");
                        break;}
                else if (victory == BLEU){
                        printf("Victoire du joueur Bleu\n");
                        break;
                    }
                
                

                position_pion(grille,ROUGE);
                afficher2(grille);

                victory=victoire(grille,joueur);
                if (victory == ROUGE){
                        printf("Victoire du joueur Rouge\n");
                        break; }
                else if (victory == BLEU){
                        printf("Victoire du joueur Bleu\n");
                        break; 
                    }

                    // On fait jouer l'ordi
                    joueur=BLEU;
                    position_bobai_alea(grille);
                    afficher2(grille);
                    victory=victoire(grille,joueur);
                    
                    if (victory == ROUGE){
                        printf("Victoire du joueur Rouge\n");
                        break; }
                    else if (victory == BLEU){
                        printf("Victoire du joueur Bleu\n");
                        break; 
                    }
                    position_pion_alea (grille, BLEU);
                    afficher2(grille);
                    victory=victoire(grille,joueur);
                    
                    if (victory == ROUGE){
                        printf("Victoire du joueur Rouge\n");
                        break; }
                    else if (victory == BLEU){
                        printf("Victoire du joueur Bleu\n");
                        break; 
                    }
                
                joueur=ROUGE;                
            }

    }

    // Libérer la mémoire allouée pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
    }

    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(grille);

    return 0;
    
}