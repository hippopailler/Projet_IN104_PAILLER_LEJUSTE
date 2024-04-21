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
    printf("Quel pion veux tu bouger ? (ligne colonne)\n");
    scanf("%d %d",&ligne_pion, &colonne_pion);

    if (grille[ligne_pion][colonne_pion]!=joueur){ //prend en compte le hors piste
        printf("Aucun de vos pions n'est à cet emplacement\n");
        position_pion(grille,joueur);
    }

    printf("où voulez vous le bouger ? (ligne colonne)\n");
    scanf("%d %d",&ligne_position, &colonne_position);

    if (ligne_position <0 || ligne_position >4 || colonne_position <0 || colonne_position >4){
        printf ("Erreur hors piste\n");
        position_pion(grille, joueur);
    }

    if (grille[ligne_position][colonne_position]!= BLANC){ //prends en compte le non mouvement
        printf("Erreur, position déjà prise\n");
        position_pion(grille,joueur);
    }

    int decalage_ligne = ligne_position-ligne_pion; 
    int decalage_colonne = colonne_position-colonne_pion;

    if (decalage_ligne==0){ //mouvement que selon la verticale
        for (int i =1; i<=abs(decalage_colonne); i++){
        if (decalage_colonne>0){
            if (grille[ligne_pion][colonne_pion+i]!=BLANC){
                printf("Erreur, un pion se trouve sur votre trajectoire\n");
                position_pion(grille, joueur);
            }}
            
        else if (decalage_colonne<0){
               if (grille[ligne_pion][colonne_pion-i]!=BLANC){
                printf("Erreur, un pion se trouve sur votre trajectoire\n");
                position_pion(grille, joueur);
                }}
        }
        if ( colonne_position == 0 || colonne_position ==4){ //si on est sur les bords
            grille[ligne_position][colonne_position]=joueur;
            grille[ligne_pion][colonne_pion]=BLANC;
            return grille;
        } 
        else if (grille[ligne_position][colonne_position+1]!=BLANC || grille[ligne_position][colonne_position-1]!=BLANC ){// on verifie la presence d'obstacle 
                grille[ligne_position][colonne_position]=joueur;
                grille[ligne_pion][colonne_pion]=BLANC;
                return grille;
            }
    }

    else if (decalage_colonne==0){ //mouvement que selon l'horizontal
        for (int i =1; i<=abs(decalage_ligne); i++){
            if (decalage_ligne>0){
            if (grille[ligne_pion+i][colonne_pion]!=BLANC){
                printf("Erreur, un pion se trouve sur votre trajectoire\n");
                position_pion(grille, joueur);
            }}
            else if (decalage_ligne<0){
               if (grille[ligne_pion-i][colonne_pion]!=BLANC){
                printf("Erreur, un pion se trouve sur votre trajectoire\n");
                position_pion(grille, joueur);
            }}
        }
        if (ligne_position == 0 || ligne_position ==4){ //si on est sur les bords
            grille[ligne_position][colonne_position]=joueur;
            grille[ligne_pion][colonne_pion]=BLANC;
            return grille;
        } 
        else if (grille[ligne_position+1][colonne_position]!=BLANC || grille[ligne_position-1][colonne_position]!=BLANC){// on verifie la presence d'obstacle 
                grille[ligne_position][colonne_position]=joueur;
                grille[ligne_pion][colonne_pion]=BLANC;
                return grille;
        }
    }

    else if (decalage_colonne == decalage_ligne){//dep en diagonale
        for (int i =1; i<=abs(decalage_colonne); i ++){
        if (decalage_colonne>0){
            if (grille[ligne_pion+i][colonne_pion+i]!=BLANC){
                printf("Erreur, un pion se trouve sur votre trajectoire\n");
                position_pion(grille, joueur);
            }}
        
        else{
        for (int i =1; i<=abs(decalage_colonne); i ++){
            if (grille[ligne_pion-i][colonne_pion-i]!=BLANC){
                printf("Erreur, un pion se trouve sur votre trajectoire\n");
                position_pion(grille, joueur);
            }
        }}}
        // les bords
        if (ligne_position == 0 || ligne_position ==4 || colonne_position == 0 || colonne_position ==4){
            grille[ligne_position][colonne_position]=joueur;
            grille[ligne_pion][colonne_pion]=BLANC;
            return grille;
        }//on verifie la présence d'obstacle juste après
        else if (grille[ligne_position+1][colonne_position+1]!=BLANC || grille[ligne_position-1][colonne_position-1]!=BLANC){
            grille[ligne_position][colonne_position]=joueur;
            grille[ligne_pion][colonne_pion]=BLANC;
            return grille;
        }
    
    }


    else{
        printf("Erreur, le déplacement n'est pas autorisé.\n");
        position_pion(grille, joueur);
    }

    return grille;
    }