#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  srand(time(NULL));

  int size = argv[1] ? atoi(argv[1]) : 3;

  int *pov;
  pov = initpov(size);

  Grid *grid = initgrid(size);
  GhostGrid* gridf = initGhostGrid(size);
  if (grid == NULL) {
    return 0;
  }

  // fillgrid(grid);
  //  grid_completion(grid);

  printgrid(grid, pov);
  printf("\n");
  printgrid_Ghost(gridf);
  free(grid); free(gridf);
  return EXIT_SUCCESS;
}