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
  //printf("%d\n", gridf->size);
  printf("%d", 1);
  Guess *guesses = fill_guess(*gridf,*grid);
  printf("%d", 2);
  free(grid);
  free(gridf);
  //grid->tab[2][2] = 0;

  /* printgrid(grid,pov);
   printf("\n");
   fill_ghost(*gridf, *grid, pov);
   printgrid_Ghost(gridf);
   free(grid); free(gridf);
   printf("\n");*/

  //

  //char *Seed3dim = "32635114095";
  //char *Seed4dim = "4012418066553565535";
  //char *Seed5dim = "5001120060112099335544311048575";
  //grid = read_seed(Seed3dim);
  //printgrid(grid);

  //grid = read_seed(Seed4dim);
  //printgrid(grid);

  //grid = read_seed(Seed5dim);
  //int tab[5] = { 5,2,3,4,1 };
  //int val=line_to_id(tab,5);
  ////char*buffer=malloc()
  //printf("%d", val);


  //Grid* grid;

  ///*int difficulty = 1;
  //grid = generate_level(4, &difficulty); 
  //push_to_php(grid);*/

  //char*SEED=create_seed(1,4);
  //printf("%s", SEED);
  //grid =read_seed(SEED);
  //printgrid(grid);

  printf("%d", 3);
  return EXIT_SUCCESS;
}