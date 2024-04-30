#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"


CouleurPion** position_bobai (CouleurPion** grille, CouleurPion joueur){
    int ligne=0;
    int colonne =0;
    if (joueur == BLEU){ printf("Joueur Bleu : choix de la nouvelle position du bobai\n" );} // dire quel joueur
    if (joueur == ROUGE){ printf("Joueur Rouge : choix de la nouvelle position du bobai\n");} // dire quel joueur
   
    int ret = scanf("%d %d",&ligne, &colonne);
    //gestion des erreurs de type en entrée

    if (ret != 2) {
        printf("Format invalide. Veuillez saisir deux entiers.\n");
        // Pour vider le tampon d'entrée en cas de saisie incorrecte
        while (getchar() != '\n'); // Vide le tampon jusqu'à la fin de ligne
        position_bobai(grille,joueur);
        return grille;
    }

    if (ligne>=0 && ligne <5  && colonne >=0 && colonne <5){  
        
    for (int i =0; i<5; i++){
        for (int j= 0; j<5; j++){ //changement de position
            if (grille[i][j]==VERT){
                // verifier la possibilité du mouvement 
                if ((i == ligne && (colonne == j-1|| colonne == j+1)) || (i +1 == ligne && (colonne== j|| j-1 == colonne || j+1 == colonne)) || (i-1 == ligne && (j== colonne || j-1 == colonne || j+1 == colonne))){ // verifie que c'est a distance 1 du pion
                    if (grille[ligne][colonne]==BLANC){//verif si presence d'un pion
                        grille[i][j]=BLANC;// le bobai n'est plus là
                        grille[ligne][colonne]=VERT;
                        return grille;
                    }
                    else {
                    printf("Un pion est déjà sur cette case\n");
                    position_bobai(grille, joueur);
                    return grille;
                    }}
                else {
                    printf("Erreur déplacement invalide, le bobai ne peut bouger que de 1 seule case autour de lui.\n");
                    position_bobai(grille, joueur);
                    return grille;
                }
            }      
        }
    }
    }
    else {
        printf("Déplacement hors grille, respectez les nombres affichés ie de 0 à 4.\n");
        position_bobai(grille, joueur);
        return grille;
    }
    return grille;
    }