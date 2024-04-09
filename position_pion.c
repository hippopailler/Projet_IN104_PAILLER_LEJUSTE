#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"

CouleurPion** position_pion (CouleurPion** grille, CouleurPion joueur){
    int ligne_pion=0;
    int colonne_pion =0;
    int colonne_position =0;
    int ligne_position=0;

    if (joueur == BLEU){ printf("Joueur Bleu : choix de la nouvelle position d'un de tes pions\n" );} // dire quel joueur
    if (joueur == ROUGE){ printf("Joueur Rouge : choix de la nouvelle position d'un de tes pions'\n");} // dire quel joueur
    printf("Quel pion veux tu bouger ?(ligne colonne)");
    scanf("%d %d",&ligne_pion, &colonne_pion);
    printf("A quelle position ?(ligne colonne)");
    scanf("%d %d",&ligne_position, &colonne_position);

    int decalage_ligne = ligne_position-ligne_pion; 
    int decalage_colonne = colonne_pion-colonne_position;

    if (grille[ligne_pion][colonne_pion]==joueur){ //verif bon pion choisi
        if (ligne_pion==ligne_position || colonne_pion==colonne_position || decalage_colonne==decalage_ligne){//verif dep possible
        if (ligne_position>0 && ligne_position <4  && colonne_position >0 && colonne_position <4){ // d'abord on regarde s'il y a un obstacle hors bords   
            if(decalage_ligne == 0 && decalage_colonne>0 && grille[ligne_position][colonne_position+1]!=BLANC){
                grille[ligne_position][colonne_position]=joueur;
                grille[ligne_pion][colonne_pion]=BLANC;
                return grille;
            }
            else if(decalage_ligne == 0 && decalage_colonne<0 && grille[ligne_position][colonne_position-1]!=BLANC){
                grille[ligne_position][colonne_position]=joueur;
                grille[ligne_pion][colonne_pion]=BLANC;
                return grille;
            }
            else if(decalage_ligne < 0 && decalage_colonne==0 && grille[ligne_position+1][colonne_position]!=BLANC){
                grille[ligne_position][colonne_position]=joueur;
                grille[ligne_pion][colonne_pion]=BLANC;
                return grille;
            }
            else if(decalage_ligne > 0 && decalage_colonne==0 && grille[ligne_position-1][colonne_position]!=BLANC){
                grille[ligne_position][colonne_position]=joueur;
                grille[ligne_pion][colonne_pion]=BLANC;
                return grille;
            }
             else {
                    printf("Le mouvement n'est pas autorisé il faut un obstacle sur la case d'après\n");
                    position_pion(grille, joueur);
                    return grille;
                    }}
        else if ((ligne_position ==0 && (colonne_position==0 || colonne_position == 4)) || (ligne_position ==4 && (colonne_position==0 || colonne_position == 4))){
            grille[ligne_position][colonne_position]=joueur;
            grille[ligne_pion][colonne_pion]=BLANC;
            return grille;
        }
        else {
            printf("Erreur hors piste\n");
            position_pion(grille, joueur);
            return grille;
            }
        }}
        else {
            printf("Erreur, le déplacement n'est pas autorisé.");
            position_pion(grille, joueur);
            return grille;
        }      
    return grille;
    }