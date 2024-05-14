#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <time.h>
#include <stdbool.h>
#include "ordi_alea.h"
#include <limits.h>

#define MAX_MOVE 25 //nombre de simulations max pour chaque configuration --> valeur à nuancer selon le temps de calcul


//On va parcourir l'arbre des simulations de jeu, on garde en mémoire l'état de jeu
typedef struct Noeud {
    CouleurPion** etat;
    struct Node* children[MAX_MOVE]; //profondeur max
    int simul; //nombre de simulations découlant de ce noeud
    int victoire; //recense le nombre de victoire depuis cette simulation
}Noeud;

Noeud* crea_node(CouleurPion** etat) {
    Noeud* noeud = malloc(sizeof(Noeud));
    noeud->etat = etat;
    noeud->simul = 0; //initilement noeud en bout d'arbre
    noeud->victoire = 0;
    for (int i = 0; i < MAX_MOVE; i++) {
        noeud->children[i] = NULL;
    }
    return noeud;
}


// Calcul de l'ucb permettant de choisir l'ordre d'exploration des noeuds avec la fonction qui suit
int ucb(Noeud* parent, Noeud* child) {
    // Upper Confidence Bound calculation --> cf formule sur wikipédia

    if (child->simul == 0) {
        return 200; // encourage la visite des noeuds non visités
    }
    double exploitation = child->victoire / (double)child->simul;
    double exploration = sqrt(log(parent->simul) / (double)child->simul);
    return exploitation + 2 * exploration; // UCB1 formula
}

Noeud* select_noeud(Noeud* root) {
    // Sélection d'un noeud enfant selon le max d'UCB
    Noeud* selected = NULL;
    int max_ucb = 0;
    for (int i = 0; i < MAX_MOVE; i++) {
        if (root->children[i] != NULL) {
            int current_ucb = ucb(root, root->children[i]);
            if (current_ucb > max_ucb) {
                max_ucb = current_ucb;
                selected = root->children[i];
            }
        }
    }
    return selected;
}


Noeud* expansion(Noeud* parent) {
    // Etend le parent en ajoutant des enfants pou les différents coups
    for (int i = 0; i < MAX_MOVE; i++) {
        if (parent->children[i] == NULL) {
            //on va créer un nouvel état en faisant un coup aléatoire --> risque de répétition d'état / voir comment gérer la différence des joueurs
            CouleurPion** new_state = position_bobai_alea (parent->etat); //pour l'instant ou le fait déjà pour le position du bobail 
            parent->children[i] = create_node(new_state);
            return parent->children[i];
        }
    }
    return NULL;
}
// il faut réfléchir à comment gérer le fait qu'il nous faut à la fois une position idéale pour le bobail et le déplacement des pions 
// En soit on peut dupliquer cette méthode pour ne pas se mélanger les pinceaux --> risque de complexité temporel
// Pour la mise en place je vais me concentrer sur le bobail

//Les fonctions qu'il reste à coder : 

// simulation de partie : à l'aide des fonctions de ordi alea et calcul de victoire
int simu_jeu(CouleurPion** grille){
    CouleurPion IA;
    CouleurPion joueur;
    CouleurPion victory;
    int nombre_tour = 0;
    victory = BLANC;
    IA = BLEU;
    joueur = ROUGE;
    CouleurPion** grille_reelle = grille; //on stocke la première grille - correspond à la grille du jeu en cours

//1er tour full au pif
//cette fonction est lancée qu'après le coup d'un joueur

    while (victory == BLANC){

        position_bobai_alea(grille);
        victory=victoire(grille,IA);
                    
        if (victory == joueur){
                simu_jeu(grille_reelle);} // on relance la simulation car on veut que l'IA gagne

        else if (victory == IA){
            //il faut stocker le premier mouvement avec des structs ?
            break;
                    }

            position_pion_alea (grille, IA);
            victory=victoire(grille,IA);
                    
        if (victory == joueur){
            simu_jeu(grille_reelle);
            }
        else if (victory == IA){
            //il faut stocker le premier mouvement
            break;
                    }

        position_bobai_alea(grille);
        victory=victoire(grille, joueur);
        if (victory == joueur){
            simu_jeu(grille_reelle);
                }
        else if (victory == IA){
                //il faut stocker le premier mouvement
                break;
                    }
                

        position_pion_alea(grille,joueur);

        victory=victoire(grille,joueur);
        if (victory == joueur){
            simu_jeu(grille_reelle);
                }
        else if (victory == IA){
                //il faut stocker le premier mouvement
                break;
                    }

        nombre_tour ++;         
    }
    return nombre_tour; //je sais pas trop si grille_reelle est stockée qqpart (c'est un pointeur non ?)

}
/*
- remonter l'arbre : mettre à jour les parents selon le nombre de simulations faites après et comptabiliser les victoires en plus bas 
- fonction d'ensemble qui gère l'architecture générale
*/