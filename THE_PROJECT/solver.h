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
void fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j);
Pos* find_in_grid(Grid grid, int val, int* size);
void put_number(int val, int ligne, int colonne, GhostGrid Gf);
void suite_col(int ligne, int colonne, GhostGrid Gf);
void suite_row(int ligne, int colonne, GhostGrid Gf);
int Length(char* string, int size);
int modif_box(int i, int j, GhostGrid gridf, Grid gridj);
int complete_ghost(GhostGrid gridf, Grid gridj);
//SubFunction End


//Solver start
bool crate_solver(Grid* adgridj);
void fill_ghost(GhostGrid gridf, Grid gridj);
void maj_ghost(GhostGrid gridf, Grid gridj);
int fill_loners(Grid* gridj, GhostGrid gridf);
int hypothesis(GhostGrid* gridf, Grid* gridj);
//Solver end


//Unused start
int check_loners(GhostGrid* gridf, Grid* gridj);
Guess* find_guess(GhostGrid grid, int* found, int* guess_size);
int fill_guess(GhostGrid grid, Grid gridj);
char*** create_guess_tab(Guess* guess_list, Grid grid);
int find_number_to_guess(char*** tab, int id);
void fill_guess_boxes(char*** tab, int size, int id_number, Grid grid, int i, int j);
void fill_sub_guess(int*** tab, int guess_size, Grid grid, int id);
//Unused end


//Free start
void free_tab_3(int*** tab, int size);
//Free end
#endif // !solver