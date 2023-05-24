#include "game.h"
#include "seed.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  srand(time(NULL));
  setlocale(LC_ALL, "fr_FR.UTF-8");

  int size = argv[1] ? atoi(argv[1]) : 4;

  Grid* grid = initgrid(size);
  GhostGrid *gridf = initGhostGrid(size);
  if (grid == NULL) {
    return 0;
  }

  // fillgrid(grid);
  //  grid_completion(grid);

  //fillgrid(grid);
  grid->tab[0][0] = 3;  grid->tab[0][1] = 2;  grid->tab[0][2] = 4;  grid->tab[0][3] = 1;
  grid->tab[1][0] = 0;  grid->tab[1][1] = 0;  grid->tab[1][2] = 0;  grid->tab[1][3] = 0;
  grid->tab[2][0] = 1;  grid->tab[2][1] = 3;  grid->tab[2][2] = 2;  grid->tab[2][3] = 4;
  grid->tab[3][0] = 0;  grid->tab[3][1] = 0;  grid->tab[3][2] = 0;  grid->tab[3][3] = 0;

  printgrid(grid);
  printf("\n");
  fill_ghost(*gridf, *grid, grid->obv);
  printgrid_Ghost(gridf);

  return EXIT_SUCCESS;
}