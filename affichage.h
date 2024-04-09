#ifndef GRILLE_H
#define GRILLE_H

#include <stdio.h>
#include <stdlib.h>
#include "case.h"

CouleurPion** creer_grille(int lignes, int colonnes);
void afficher(CouleurPion** grille);
void afficher2(CouleurPion** grille);

#endif /* GRILLE_H */