#ifndef game
#define game

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Pos {

  int row;
  int col;
} Pos;

typedef struct Grid {
  int size;
  int **tab;
  int *obv;
} Grid;

int **creatab(int size);

void printgrid(Grid *grid);

int *initpov(int size);

Grid *initgrid(int dim);

void initElt(int *elt, int size);

Grid *fillgrid(Grid *grid);

bool found_in_row(int **tab, int size, int col, int val);

bool found_in_col(int **tab, int size, int col, int val);

void initab(int **tab, int size);

void free_tab(int **tab, int size);

#endif // !game