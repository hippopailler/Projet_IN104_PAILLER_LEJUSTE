#ifndef MCTS_H
#define MCTS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"
#include <time.h>
#include <stdbool.h>
#include "ordi_alea.h"
#include <limits.h>

CouleurPion** mcts(CouleurPion** initial_state, int iterations);

#endif /* MCTS_H */