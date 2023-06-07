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
typedef struct StockSoluce {
	Grid* stock;
	int size;
} StockSoluce;

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
int fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j);
Pos* find_in_grid(Grid grid, int val, int* size);
void put_number(int val, int ligne, int colonne, GhostGrid Gf);
void suite_col(int ligne, int colonne, GhostGrid Gf);
void suite_row(int ligne, int colonne, GhostGrid Gf);
int Length(char* string, int size);
int complete_ghost(GhostGrid gridf, Grid gridj);
int modif_box(int i, int j, GhostGrid gridf, Grid gridj);
void print_Stock(StockSoluce*Stock);
//SubFunction End


//Solver start
int crate_solver(Grid* adgridj);//renvoie le nombre de solutions
void fill_ghost(GhostGrid gridf, Grid gridj);
int maj_ghost(GhostGrid gridf, Grid gridj);
int fill_loners(Grid* gridj, GhostGrid gridf);
bool hypothesis(GhostGrid* gridf, Grid* gridj, int poss,StockSoluce*Stock, bool first_sol,bool validity);
int Rule2(GhostGrid gridf, Grid gridj);
int check_loners(GhostGrid* gridf, Grid* gridj);
bool unique_solution(Grid* grid);
int subcrate_solver(Grid* gridj, bool first_sol, bool validity);
//Solver end

void indice(Grid* grid, int nb_hints);

//Free start
void free_tab_3(char*** tab, int size);
void free_grid(Grid* grid);
void free_ghostgrid(GhostGrid* gridf);
//Free end
#endif // !solver