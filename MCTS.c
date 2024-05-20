#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <stdbool.h>
#include "ordi_alea.h"  
#include <limits.h>
#include "victoire.h"

#define MAX_MOVE 10 // nombre de simulations max pour chaque configuration --> valeur à nuancer selon le temps de calcul

// On va parcourir l'arbre des simulations de jeu, on garde en mémoire l'état de jeu
typedef struct Noeud {
    CouleurPion** etat;
    struct Noeud* parent;
    struct Noeud* children[MAX_MOVE]; // profondeur max
    int simul; // nombre de simulations découlant de ce noeud
    int victoire; // recense le nombre de victoire depuis cette simulation
} Noeud;

Noeud* crea_node(CouleurPion** etat, Noeud* parent) {
    Noeud* noeud = malloc(sizeof(Noeud));
    if (noeud == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le noeud\n");
        exit(EXIT_FAILURE);
    }
    noeud->etat = etat;
    noeud->parent = parent;
    noeud->simul = 0; // initialement noeud en bout d'arbre
    noeud->victoire = 0;
    for (int i = 0; i < MAX_MOVE; i++) {
        noeud->children[i] = NULL;
    }
    return noeud;
}

// Calcul de l'ucb permettant de choisir l'ordre d'exploration des noeuds avec la fonction qui suit
double ucb(Noeud* parent, Noeud* child) {
    // Upper Confidence Bound calculation --> cf formule sur wikipédia
    if (child->simul == 0) {
        return INFINITY; // encourage la visite des noeuds non visités
    }
    double exploitation = child->victoire / (double)child->simul;
    double exploration = sqrt(log(parent->simul) / (double)child->simul);
    return exploitation + 2 * exploration; // UCB1 formula
}

Noeud* select_noeud(Noeud* root) {
    // Sélection d'un noeud enfant selon le max d'UCB
    Noeud* selected = NULL;
    double max_ucb = -INFINITY;
    for (int i = 0; i < MAX_MOVE; i++) {
        if (root->children[i] != NULL) {
            double current_ucb = ucb(root, root->children[i]);
            if (current_ucb > max_ucb) {
                max_ucb = current_ucb;
                selected = root->children[i];
            }
        }
    }
    return selected;
}

Noeud* expansion(Noeud* parent) {
    // Étend le parent en ajoutant des enfants pour les différents coups
    for (int i = 0; i < MAX_MOVE; i++) {
        if (parent->children[i] == NULL) {
            // On va créer un nouvel état en faisant un coup aléatoire
            CouleurPion** new_state = position_bobai_alea(parent->etat); // pour l'instant on le fait déjà pour le position du bobail 
            if (new_state == NULL) {
                fprintf(stderr, "Erreur de création du nouvel état\n");
                continue;
            }
            parent->children[i] = crea_node(new_state, parent);
            return parent->children[i];
        }
    }
    return NULL;
}

CouleurPion** copy_grille(CouleurPion** grille) {
    // Allouer de la mémoire pour le tableau de pointeurs
    CouleurPion** co_grille = (CouleurPion**)malloc(5 * sizeof(CouleurPion*));
    // Test de l'allocation mémoire
    if (co_grille == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour chaque tableau d'entiers
    for (int i = 0; i < 5; i++) {
        co_grille[i] = (CouleurPion*)malloc(5 * sizeof(CouleurPion));
        // Nouveau test d'allocation mémoire
        if (co_grille[i] == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    // Copier l'ancien tableau
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            co_grille[i][j] = grille[i][j];
        }
    }

    return co_grille;
}

int simu_jeu(CouleurPion** grille) {
    CouleurPion IA;
    CouleurPion joueur;
    CouleurPion victory;
    int nombre_tour = 0; // filet de sécurité pour éviter les boucles infinies
    victory = BLANC;
    IA = BLEU;
    joueur = ROUGE;
    CouleurPion** grille_reelle = copy_grille(grille); // on stocke la première grille - correspond à la grille du jeu en cours

    while (victory == BLANC && nombre_tour < 1000) {
        position_bobai_alea(grille);
        victory = victoire(grille, IA);
                    
        if (victory == joueur) {
            return simu_jeu(grille_reelle); // on relance la simulation car on veut que l'IA gagne
        } else if (victory == IA) {
            break;
        }

        position_pion_alea(grille, IA);
        victory = victoire(grille, IA);
                    
        if (victory == joueur) {
            return simu_jeu(grille_reelle);
        } else if (victory == IA) {
            break;
        }

        position_bobai_alea(grille);
        victory = victoire(grille, joueur);

        if (victory == joueur) {
            return simu_jeu(grille_reelle);
        } else if (victory == IA) {
            break;
        }

        position_pion_alea(grille, joueur);
        victory = victoire(grille, joueur);

        if (victory == joueur) {
            return simu_jeu(grille_reelle);
        } else if (victory == IA) {
            break;
        }

        nombre_tour++;
    }

    int reward = (victory == IA) ? 1 : 0;

    // On libère la grille de simulation de partie 
    for (int i = 0; i < 5; i++) {
        free(grille[i]);
    }
    free(grille);
    return reward;
}

void backpropagate(Noeud* node, int reward) {
    while (node != NULL) {
        node->simul++;
        node->victoire += reward;
        node = node->parent;
    }
}

CouleurPion** mcts(CouleurPion** initial_state, int iterations) {
    Noeud* root = crea_node(initial_state, NULL);

    for (int i = 0; i < iterations; i++) {
        Noeud* selected = select_noeud(root);
        if (selected == NULL) break;

        Noeud* expanded = expansion(selected);
        if (expanded == NULL) continue;

        int reward = simu_jeu(expanded->etat);
        backpropagate(expanded, reward);
    }

    Noeud* best_child = NULL;
    int max_simul = -1;
    for (int i = 0; i < MAX_MOVE; i++) {
        if (root->children[i] != NULL && root->children[i]->simul > max_simul) {
            max_simul = root->children[i]->simul;
            best_child = root->children[i];
        }
    }

    if (best_child == NULL) {
        // Sélection d'un coup aléatoire parmi les mouvements possibles
        /*
        int random_move;
        do {
            random_move = rand() % MAX_MOVE;
        } while (root->children[random_move] == NULL);

        return root->children[random_move]->etat;*/
        printf("aléa ");
        CouleurPion** finale = position_bobai_alea(initial_state);
        return finale;

        
    }

    return best_child->etat;
}



/*
int main() {
    srand(time(NULL));

    CouleurPion** initial_state = initialiser_grille(); // Fonction pour initialiser la grille du jeu
    int iterations = 1000; // Ajuster le nombre d'itérations selon les besoins

    CouleurPion** final_state = mcts(initial_state, iterations);

    afficher_grille(final_state); // Fonction pour afficher la grille du jeu

    free_grille(initial_state); // Libérer la mémoire
    free_grille(final_state); // Libérer la mémoire
    return 0;
}
*/
