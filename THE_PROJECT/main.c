#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int size = argv[1] ? atoi(argv[1]) : 5;

  int *pov;
  pov = initpov(size);

  Grid *grid = initgrid(size);
  if (grid == NULL) {
    return 0;
  }

  fillgrid(grid);
  // grid_completion(grid);

  printgrid(grid, pov);
  return EXIT_SUCCESS;
}