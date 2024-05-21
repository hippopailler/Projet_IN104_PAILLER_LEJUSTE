#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <stdbool.h>
#include "ordi_alea.h"  
#include <limits.h>
#include "affichage.h"
#include "victoire.h"

#define MAX_MOVE 2 // nombre de simulations max pour chaque configuration --> valeur à nuancer selon le temps de calcul

CouleurPion** copy_grille(CouleurPion** grille) {
    // Allouer de la mémoire pour le tableau de pointeurs
    CouleurPion** co_grille = (CouleurPion**)malloc(5 * sizeof(CouleurPion*));
    if (co_grille == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour co_grille\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour chaque ligne du tableau
    for (int i = 0; i < 5; i++) {
        co_grille[i] = (CouleurPion*)malloc(5 * sizeof(CouleurPion));
        if (co_grille[i] == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour co_grille[%d]\n", i);
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


// On utilise une structure de liste chainée pour parcourir l'arbre et pouvoir remonter plus facilement pour propager les scores
typedef struct Noeud {
    CouleurPion** etat;
    struct Noeud* parent;
    struct Noeud* children[MAX_MOVE];
    int simul;
    int victoire;
} Noeud;


// Cette fonction permet d'initialiser un nouveau noeud --> particulièrement utilisé dans la fonction expansion
Noeud* crea_node(CouleurPion** etat, Noeud* parent) {
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
    if (noeud == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le noeud\n");
        exit(EXIT_FAILURE);
    }
    noeud->etat = etat;
    noeud->parent = parent;
    noeud->simul = 0; //vient d'être crée donc 0 simulations découlant
    noeud->victoire = 0; // on a pas encore testé les victoires
    for (int i = 0; i < MAX_MOVE; i++) {
        noeud->children[i] = NULL;
    }
    return noeud;
}



double ucb(Noeud* parent, Noeud* enfant) {
    if (enfant->simul == 0) {
        return INFINITY; // Encourage la visite des noeuds non visités
    }
    double exploitation = (double) enfant->victoire / enfant->simul;
    double exploration = sqrt(log(parent->simul) / enfant->simul);
    return exploitation + 2 * exploration; // calcul de l'UCB1 
}

// On parcourt l'arbre depuis un noeud donné et le choix du prochain noeud est fait en fonction de la valeur de l'UCB1 associé
Noeud* select_noeud(Noeud* root) {
    Noeud* selected = NULL;
    double max_ucb = -1000;
    for (int i = 0; i < MAX_MOVE; i++) {
        if (root->children[i] != NULL) {
            double current_ucb = ucb(root, root->children[i]);
            printf("UCB pour le nœud enfant %d : %.2f\n", i, current_ucb);
            if (current_ucb > max_ucb) {
                max_ucb = current_ucb;
                selected = root->children[i];
            }
        }
    }
    return selected;
}

int expansion(Noeud* parent) {
    printf("État des nœuds enfants avant l'expansion :\n");
    for (int j = 0; j < MAX_MOVE; j++) {
        printf("Noeud enfant %d : %p\n", j, (void*)parent->children[j]);
    }

    int created_children = 0; // Variable pour compter les enfants créés

    for (int i = 0; i < MAX_MOVE; i++) {
        printf("hello world\n");
        CouleurPion** new_state = copy_grille(parent->etat);
        if (new_state == NULL) {
            fprintf(stderr, "Erreur de création du nouvel état\n");
            continue;
        }
        position_bobai_alea(new_state);
        parent->children[i] = crea_node(new_state, parent);
        printf("Nouvel état de la grille après expansion :\n");
        afficher2(new_state);

        created_children++; // Incrémente le nombre d'enfants créés
    }

    return created_children; // Retourne le nombre d'enfants créés
}

int simu_jeu(CouleurPion** grille) {
    CouleurPion IA = BLEU;
    CouleurPion joueur = ROUGE;
    CouleurPion victory = BLANC;
    int nombre_tour = 0;
    CouleurPion** grille_reelle = copy_grille(grille);

    while (victory == BLANC && nombre_tour < 100) {
        position_bobai_alea(grille);
        victory = victoire(grille, IA);

        if (victory == joueur) {
            return simu_jeu(grille_reelle);
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

    for (int i = 0; i < 5; i++) {
        free(grille[i]);
    }
    free(grille);
    return reward;
}

void backpropagate(Noeud* node, int reward) {
    while (node != NULL) { // on remonte jusqu'à la racine de l'arbre ayant pour parent le noeud null
        node->simul++;
        node->victoire += reward;
        node = node->parent;
    }
}


CouleurPion** mcts(CouleurPion** initial_state, int iterations) {
    Noeud* root = crea_node(initial_state, NULL);
    int created_children = expansion(root); // Expanse le nœud racine et récupère le nombre d'enfants créés

    // Simulation pour chaque enfant créé lors de l'expansion
    for (int i = 0; i < created_children; ++i) {
        Noeud* enfant = root->children[i];
        int reward = simu_jeu(enfant->etat);
        backpropagate(enfant, reward);
    }

    // Boucle principale des itérations MCTS
    for (int i = 0; i < iterations; i++) {
        printf("Itération %d\n", i);
        Noeud* selected = select_noeud(root);
        if (selected == NULL) {
            printf("Aucun noeud sélectionné, arrêt des itérations\n");
            break;
        }

        int created_children = expansion(selected); // Expanse le nœud sélectionné et récupère le nombre d'enfants créés

        // Simulation pour chaque enfant créé lors de l'expansion
        for (int j = 0; j < created_children; ++j) {
            Noeud* enfant = selected->children[j];
            int reward = simu_jeu(enfant->etat);
            backpropagate(enfant, reward);
        }
    }

    // Trouver le meilleur enfant
    Noeud* best_child = NULL;
    int max_simul = -1;
    for (int i = 0; i < MAX_MOVE; i++) {
        if (root->children[i] != NULL && root->children[i]->simul > max_simul) {
            max_simul = root->children[i]->simul;
            best_child = root->children[i];
        }
    }

    // Si aucun meilleur enfant trouvé, sélectionne un coup aléatoire--> filet de sécurité, ne devrait théoriquement jamais être apeller.
    if (best_child == NULL) {
        printf("Aucun meilleur enfant trouvé, sélection d'un coup aléatoire\n");
        return position_bobai_alea(initial_state);
    }

    return best_child->etat;
}