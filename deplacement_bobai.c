#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int** position_bobai (int** grille, int joueur){
    int ligne=0;
    int colonne =0;
   if (joueur == 1){ printf("Joueur Bleu : choix de la nouvelle position du bobai\n" );} // dire quel joueur
    if (joueur == 0){ printf("Joueur Rouge : choix de la nouvelle position du bobai\n");} // dire quel joueur
   
    scanf("%d %d",&ligne, &colonne);
    if (ligne>0 && ligne <6  && colonne >0 && colonne <6){  
        
    for (int i =0; i<6; i++){
        for (int j= 0; j<6; j++){ //changement de position
            if (grille[i][j]==3){
                // verifier la possibilité du mouvement 
                if ((i == ligne || i +1 == ligne || i-1 == ligne) && (j== colonne || j-1 == colonne || j+1 == colonne)){ // verifie que c'est a distance 1 du pion
                    if (grille[ligne][colonne]==0){//verif si presence d'un pion
                        grille[i][j]=0;// le bobai n'est plus là
                        grille[ligne][colonne]=3;
                        return grille;
                    }
                    else {
                    printf("Un pion est déjà sur cette case\n");
                    position_bobai(grille, joueur);
                    }}
                else {
                    printf("Erreur déplacement invalide\n");
                    position_bobai(grille, joueur);
                }
            }      
        }
    }
    }
    else {
        printf("Déplacement hors grille\n");
        position_bobai(grille, joueur);
    }
    return grille;
    }

 


