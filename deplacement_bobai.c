#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>



int** position_bobai (int** grille){
    int choix=0;
    printf("Joueur 1 : choix de position\n");
    scanf("%d",&choix);
    if (choix == 1 || choix == 2 || choix == 3 || choix == 4 || choix == 5 || choix == 6 || choix == 7 || choix == 8){  
    for (int i =0; i<6; i++){
        for (int j= 0; j<6; j++){ //changement de position
            if (grille[i][j]==3){
                grille[i][j]=0;// le bobai n'est plus là

                if (choix == 1) { 
                    if (i>0 && j>0){
                    grille[i-1][j-1]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);}
                    return grille;}

                if (choix == 2) { 
                    if (i<6){
                    grille[i-1][j]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);}
                    return grille;}

                if (choix == 3) { 
                    if (i>0 && j<6){
                    grille[i-1][j+1]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);}
                    return grille;}

                if (choix == 4) { 
                    if (i<6){
                    grille[i][j+1]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);}
                    return grille;}

                if (choix == 5) { 
                    if (i<6 && j<6){
                    grille[i+1][j+1]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);}
                    return grille;}

                if (choix == 6) { 
                    if (i<6){
                    grille[i+1][j]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);}
                    return grille;}

                if (choix == 7) { 
                    if (i<6 && j>0){
                    grille[i+1][j-1]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);}
                    return grille;}

                if (choix == 8) {
                    if (j>0){
                    grille[i][j-1]=3;}
                    else{
                    printf("Erreur hors grille\n");
                    grille[i][j]=3;
                    position_bobai(grille);} 
                    return grille;}
        }
    }}}
    else {
        printf("Erreur recommencer avec les données attendues\n");
        position_bobai(grille);}
        return grille;}
// message derreur quand deja un pion qur la case 
int main(){
    int lignes = 5;
    int colonnes = 5;

    // Créer la grille
    int** grille = creer_grille(lignes, colonnes);

    //position bobai
    position_bobai(grille);

    afficher(grille);

    // Libérer la mémoire allouée pour chaque ligne
    for (int i = 0; i < lignes; i++) {
        free(grille[i]);
    }

    // Libérer la mémoire allouée pour le tableau de pointeurs
    free(grille);

    return 0;
}