#ifndef game
#define game

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Pos {

  int row;
  int col;
} Pos;

typedef struct Box {
  int value;
} Box;

typedef struct Grid {
  int size;
  int **tab;
} Grid;

void printgrid(Grid *grid, int *pov);

int *initpov(int size);

Grid *initgrid(int dim);

Box initBox(int value);

int** creatab_2d(int size);

bool found_in_col(int val, Grid* grid, int col);

bool found_in_row(int val, Grid* grid, int row);

void grid_completion(Grid* grid);

#endif // !game