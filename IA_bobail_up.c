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

int simu_jeu(CouleurPion** grille) {
    printf("Début de simu_jeu\n"); // Ajouté pour le débogage
    CouleurPion IA = BLEU;
    CouleurPion joueur = ROUGE;
    CouleurPion victory = BLANC;
    int nombre_tour = 0;
    int defaite_ia = -1;
    int victoire_ia = 1;
    int non_concluant = 0;

    CouleurPion** grille_sim = copy_grille(grille);
    printf("Grille copiée\n"); // Ajouté pour le débogage

    while (victory == BLANC && nombre_tour < 400) {
        position_bobai_alea(grille_sim);
        victory = victoire(grille_sim, IA);
        printf("Tour %d: vérification après position_bobai_alea\n", nombre_tour); // Ajouté pour le débogage

        if (victory == joueur) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Défaite de l'IA\n"); // Ajouté pour le débogage
            return defaite_ia;
        } else if (victory == IA) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Victoire de l'IA\n"); // Ajouté pour le débogage
            return victoire_ia;
        }

        position_pion_alea(grille_sim, IA);
        victory = victoire(grille_sim, IA);
        printf("Tour %d: vérification après position_pion_alea pour IA\n", nombre_tour); // Ajouté pour le débogage

        if (victory == joueur) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Défaite de l'IA\n"); // Ajouté pour le débogage
            return defaite_ia;
        } else if (victory == IA) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Victoire de l'IA\n"); // Ajouté pour le débogage
            return victoire_ia;
        }

        position_bobai_alea(grille_sim);
        victory = victoire(grille_sim, joueur);
        printf("Tour %d: vérification après position_bobai_alea pour joueur\n", nombre_tour); // Ajouté pour le débogage

        if (victory == joueur) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Défaite de l'IA\n"); // Ajouté pour le débogage
            return defaite_ia;
        } else if (victory == IA) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Victoire de l'IA\n"); // Ajouté pour le débogage
            return victoire_ia;
        }

        position_pion_alea(grille_sim, joueur);
        victory = victoire(grille_sim, joueur);
        printf("Tour %d: vérification après position_pion_alea pour joueur\n", nombre_tour); // Ajouté pour le débogage

        if (victory == joueur) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Défaite de l'IA\n"); // Ajouté pour le débogage
            return defaite_ia;
        } else if (victory == IA) {
            for (int i = 0; i < 5; i++) {
                free(grille_sim[i]);
            }
            free(grille_sim);
            printf("Victoire de l'IA\n"); // Ajouté pour le débogage
            return victoire_ia;
        }

        nombre_tour++;
    }

    for (int i = 0; i < 5; i++) {
        free(grille_sim[i]);
    }
    free(grille_sim);

    printf("Simulation non concluante\n"); // Ajouté pour le débogage
    return non_concluant;
}

CouleurPion** ia_bobail_up(CouleurPion** grille_depart){
    // on va créer 10 copies de la grille de départ
    CouleurPion*** liste_test = (CouleurPion***)malloc(10 * sizeof(CouleurPion**));
    // Ajoutez des états au tableau
    for (int i = 0; i < 10; i++) {
        CouleurPion** etat = copy_grille(grille_depart);
        position_bobai_alea(etat);
        liste_test[i]=etat;
    }

    // Affichez les états dans le tableau pour la vérification
    
    for (int i = 0; i < 10; i++) {
        afficher2(liste_test[i]);
    }

    //on va simuler une centaine de parties pour chaque configuration et regarder qui à le taux de victoire le plus élevé

    int max=0;
    /*
    for (int j = 0; j < 10; j++) {
        printf("test0\n");
        max += simu_jeu(liste_test[1]);
    }
    */
    printf("max= %d",simu_jeu(liste_test[1]));

    /*
    for (int i=0; i<10;++i){
        CouleurPion** simul= copy_grille(liste_test->data[i]);
        printf("test1");
        int total=0;

        for (int j = 0; j < 100; j++) {
        printf("test2");
        CouleurPion** grille_simul = copy_grille(simul);
        total += simu_jeu(grille_simul);
        // Libérer la mémoire de la grille simulée
        for (int k = 0; k < 5; k++) {
            free(grille_simul[k]);
        }
        free(grille_simul);
        }
        printf("test3");
        for (int i = 0; i < 5; i++) {
            free(simul[i]);
            }
            free(simul);
        //win_rates[i]=total;
    }
    */
    /*
    printf("Taux de victoire pour chaque configuration :\n");
    for (int i = 0; i < 10; i++) {
        printf("Configuration %d : %d%%\n", i, win_rates[i]);
    }
    */
    
    // Libérez le tableau dynamique
    
    return grille_depart;
}

