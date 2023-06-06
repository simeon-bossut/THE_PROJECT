#include "game.h"
#include "seed.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  srand(time(NULL));
  setlocale(LC_ALL, "fr_FR.UTF-8");

  // argv contient l'ensemble des arguments passes separes par des espaces
  // il affiche en 1 le premier argument

  if (strcmp(argv[argc - 1], "-help") == 0) {
    printf("Usage: ./main [dim] [action] [difficulty] [seed]\n dim: dimension "
           "of the grid\n action: 1 for a grid with missing elements, 2 for a "
           "clue, 3 for a complete grid, 4 for confirmation that a grid is "
           "possible\n difficulty: 0 for very easy, 1 for easy, 2 for medium, "
           "3 for hard\n "
           "seed: seed of the grid\n");
    return 0;
  }

  int dim = atoi(argv[1]);
  // int dim = 3;

  int action = atoi(argv[2]);
  // int action = 1;

  Grid *grid;

  // Get a grid with missing elements
  if (action == 1) {
    int difficulty = atoi(argv[3]);
    // int difficulty = 2;
    char *seed_;
    seed_ = create_seed(difficulty, dim);
    grid = read_seed(seed_);
    push_to_php(grid);
  }

  // Get a clue
  else if (action == 2) {
    grid = read_grid("221122312213100002000", dim);
    if (is_grid_correct(grid)) {
      hint(grid);
    }
    push_to_php(grid);
  }

  // Get a complete grid
  else if (action == 3) {
    grid = read_grid(argv[4], dim);
    crate_solver(grid);
    push_to_php(grid);
  }

  // Get confirmation that a grid is possible
  else if (action == 4) {
    grid = read_grid(argv[4], dim);
    is_solved(*grid);
  }

  /*

  srand(time(NULL));
  setlocale(LC_ALL, "fr_FR.UTF-8");

  int size = argv[1] ? atoi(argv[1]) : 3;
  */

  // Grid* grid;
  // char*Seed=create_seed(4, 3);
  // printf("%s\n\n", Seed);
  // grid = read_seed(Seed);
  // printgrid(grid);
  // printf("%s", level_to_seed(grid));

  // fillgrid(grid);
  // grid_completion(grid);

  // fillgrid(grid);

  // generateGrid(grid);

  /*grid->tab[0][0] = 0;  grid->tab[0][1] = 0;  grid->tab[0][2] = 0;
  grid->tab[0][3] = 0; grid->tab[1][0] = 0;  grid->tab[1][1] = 0;
  grid->tab[1][2] = 0;  grid->tab[1][3] = 0; grid->tab[2][0] = 0;
  grid->tab[2][1] = 0;  grid->tab[2][2] = 0;  grid->tab[2][3] = 0;
  grid->tab[3][0] = 0;  grid->tab[3][1] = 0;  grid->tab[3][2] = 0;
  grid->tab[3][3] = 0;

  grid->obv[0] = 1;  grid->obv[1] = 4;  grid->obv[2] = 2;  grid->obv[3] = 3;
  grid->obv[4] = 3;  grid->obv[5] = 2;  grid->obv[6] = 1;  grid->obv[7] = 3;
  grid->obv[8] = 2;  grid->obv[9] = 2;  grid->obv[10] = 1; grid->obv[11] = 2;
  grid->obv[12] = 2; grid->obv[13] = 3; grid->obv[14] = 3; grid->obv[15] = 1;*/

  /*fill_ghost(*gridf, *grid);
  printgrid(grid);
  crate_solver(grid);
  printf("\n");*/
  // hypothesis(gridf, grid);
  // check_loners(gridf,grid);
  // maj_ghost(*gridf, *grid);

  /*printgrid_Ghost(gridf);
  printgrid(grid);
  //printf("%d\n", gridf->size);
  //Guess *guesses = fill_guess(*gridf,*grid);
  free(grid);
  free(gridf);
  //grid->tab[2][2] = 0;*/

  /* printgrid(grid,pov);
   printf("\n");
   fill_ghost(*gridf, *grid, pov);
   printgrid_Ghost(gridf);
   free(grid); free(gridf);
   printf("\n");*/

  //

  // char *Seed3dim = "32635114095";
  // char *Seed4dim = "4012418066553565535";
  // char *Seed5dim = "5001120060112099335544311048575";
  // grid = read_seed(Seed3dim);
  // printgrid(grid);

  // grid = read_seed(Seed4dim);
  // printgrid(grid);

  // grid = read_seed(Seed5dim);
  // int tab[5] = { 5,2,3,4,1 };
  // int val=line_to_id(tab,5);
  ////char*buffer=malloc()
  // printf("%d", val);

  // Grid* grid;

  //*int difficulty = 1;
  // grid = generate_level(4, &difficulty);
  // push_to_php(grid);*/

  // char*SEED=create_seed(1,4);
  // printf("%s", SEED);
  // grid =read_seed(SEED);
  // printgrid(grid);

  // grid = read_grid("221122312213100002000", size);
  // Grid* copy = read_grid("221122312213100002000", size);
  // Grid* copy = grid;
  // Grid* hint(grid);
  // hint(grid);

  return EXIT_SUCCESS;
}