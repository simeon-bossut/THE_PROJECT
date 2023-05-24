#ifndef solver
#define solver
#define NAS 99 // Non available spaces
#define COLLUMN 1
#define ROW 2
#define FOUND 3
#define NOT_FOUND 4

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

void fill_ghost(GhostGrid gridf, Grid gridj);

Pos *find_in_grid(Grid grid, int val, int *size);

void fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j);

void printgrid_Ghost(GhostGrid* grid);
Guess* find_guess(GhostGrid grid,int * found, int * guess_size);
int fill_guess(GhostGrid grid, Grid gridj);
void print_guess(Guess *guesses, int size);

char** guess(GhostGrid grid, int* pov);
int fill_loners(Grid *gridj, GhostGrid gridf);
void fill_in_col(Guess* guess_list, int size, Grid grid);
char*** create_guess_tab(Guess* guess_list, Grid grid);
int find_number_to_guess(char*** tab, int id);
Guess* fill_guess_boxes(char*** tab, int size, int id_number, Grid grid);
#endif // !solver
