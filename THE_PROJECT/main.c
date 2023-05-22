#include "game.h"
#include "seed.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  srand(time(NULL));
  setlocale(LC_ALL, "fr_FR.UTF-8");

  // int size = argv[1] ? atoi(argv[1]) : 3;

  // int *pov;
  // pov = initpov(size);

  // Grid *grid = initgrid(size);
  // GhostGrid* gridf = initGhostGrid(size);
  // if (grid == NULL) {
  //   return 0;
  // }

  //// fillgrid(grid);
  ////  grid_completion(grid);

  // fillgrid(grid);
  /*grid->tab[0][0] = 1;
  grid->tab[1][0] = 2;
  grid->tab[2][0] = 3;
  grid->tab[0][1] = 0;
  grid->tab[1][1] = 0;
  grid->tab[2][1] = 0;
  grid->tab[0][2] = 0;
  grid->tab[1][2] = 0;
  grid->tab[2][2] = 0;*/


  /* printgrid(grid,pov);
   printf("\n");
   fill_ghost(*gridf, *grid, pov);
   printgrid_Ghost(gridf);
   free(grid); free(gridf);
   printf("\n");*/

  Grid* grid = initgrid(3);
  if(grid==NULL)
  {
	  return NULL;
  }
  for (int i = 0;i < grid->size;++i)
  {
	  for (int j = 0;j < grid->size;++j)
	  {
		  printf("%d -");
	  }
	  printf("\n");
  }
  
  return EXIT_SUCCESS;
}