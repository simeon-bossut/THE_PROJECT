#ifndef game
#define game

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif // !game