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

// Init start
typedef struct GhostGrid {
  char ***tab;
  int size;
} GhostGrid;

typedef struct Guesses {
  char **tab;
  int id;
  int direction;
  int size;
} Guess;

GhostGrid *initGhostGrid(int dim);
// Init end



//Debug start
void print_tab_3(char*** tab, int size, Grid grid);
void printgrid_Ghost(GhostGrid* grid);
//End start



//SubFunction Start

//SubFunction End
void fill_ghost(GhostGrid gridf, Grid gridj);

Pos *find_in_grid(Grid grid, int val, int *size);

void fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j);


Guess *find_guess(GhostGrid grid, int *found, int *guess_size);
int fill_guess(GhostGrid grid, Grid gridj);

int fill_loners(Grid *gridj, GhostGrid gridf);
char*** create_guess_tab(Guess* guess_list, Grid grid);
int find_number_to_guess(char*** tab, int id);
void fill_guess_boxes(char*** tab, int size, int id_number, Grid grid, int i, int j);

void free_tab_3(int*** tab, int size);
void fill_sub_guess(int*** tab, int guess_size, Grid grid, int id);



int hypothesis(GhostGrid *gridf,Grid *gridj);//MES FONCTIONS
int check_loners(GhostGrid* gridf,Grid *gridj);


bool crate_solver(Grid* adgridj);
//Solver
void maj_ghost(GhostGrid gridf, Grid gridj);
//Solver
#endif // !solver