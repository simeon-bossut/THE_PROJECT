#ifndef solver
#define solver
#define NAS 99 // Non available spaces
#define COLLUMN 1
#define ROW 2

#include "game.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct GhostGrid {
  char ***tab;
  int size;
} GhostGrid;

typedef struct Guesses {
	char** tab;
	int id;
	int direction;
	int size;
}Guess;
GhostGrid* initGhostGrid(int dim);

void fill_ghost(GhostGrid gridf, Grid gridj, int* pov);

Pos *find_in_grid(Grid grid, int val, int *size);

void fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j);
void printgrid_Ghost(GhostGrid* grid);
char** sort_guessing(GhostGrid grid);
Guess* fill_guess(GhostGrid grid);
void print_guess(Guess *guesses, int size);
#endif // !solver
