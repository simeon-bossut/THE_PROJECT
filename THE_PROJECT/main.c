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
  grid->tab[0][0] = 0;  grid->tab[0][1] = 0;  grid->tab[0][2] = 0;  grid->tab[0][3] = 0;
  grid->tab[1][0] = 0;  grid->tab[1][1] = 0;  grid->tab[1][2] = 0;  grid->tab[1][3] = 0;
  grid->tab[2][0] = 0;  grid->tab[2][1] = 0;  grid->tab[2][2] = 0;  grid->tab[2][3] = 0;
  grid->tab[3][0] = 0;  grid->tab[3][1] = 0;  grid->tab[3][2] = 0;  grid->tab[3][3] = 0;

  grid->obv[0] = 0;  grid->obv[1] = 0;  grid->obv[2] = 3;  grid->obv[3] = 3;  
  grid->obv[4] = 3;  grid->obv[5] = 3;  grid->obv[6] = 0;  grid->obv[7] = 0; 
  grid->obv[8] = 0;  grid->obv[9] = 0;  grid->obv[10] = 2; grid->obv[11] = 0;
  grid->obv[12] = 0; grid->obv[13] = 0; grid->obv[14] = 0; grid->obv[15] = 0;


  printgrid(grid);
  //crate_solver(grid);
  printf("Fill ghost\n");
  fill_ghost(*gridf, *grid);
  printgrid_Ghost(gridf);
  printf("\n\n\n");
  check_loners(gridf, grid);
  printf("Loners\n\n");
  printgrid_Ghost(gridf);

  printf("MAJ_1\n\n");
  fill_loners(grid, *gridf);
  maj_ghost(*gridf, *grid);
  printgrid_Ghost(gridf);
  
  printgrid(grid);
  printf("Rule\n");
  Rule2(*gridf, *grid);
  check_loners(gridf, grid);
  printgrid_Ghost(gridf);

  printf("MAJ_2\n\n");
  fill_loners(grid, *gridf);
  maj_ghost(*gridf, *grid);
  printgrid_Ghost(gridf);

  printgrid(grid);

  hypothesis(gridf, grid);
  //maj_ghost(*gridf, *grid);
  //printf("%d\n", gridf->size);
  //Guess *guesses = fill_guess(*gridf,*grid);
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

  //*int difficulty = 1;
  //grid = generate_level(4, &difficulty); 
  //push_to_php(grid);*/

  //char*SEED=create_seed(1,4);
  //printf("%s", SEED);
  //grid =read_seed(SEED);
  //printgrid(grid);

  return EXIT_SUCCESS;
}