#include "game.h"
#include "seed.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  srand(time(NULL));

  //int size = argv[1] ? atoi(argv[1]) : 3;

  //int *pov;
  //pov = initpov(size);

  //Grid *grid = initgrid(size);
  //GhostGrid* gridf = initGhostGrid(size);
  //if (grid == NULL) {
  //  return 0;
  //}

  //// fillgrid(grid);
  ////  grid_completion(grid);

  //fillgrid(grid);
  /*grid->tab[0][0] = 1;
  grid->tab[1][0] = 2;
  grid->tab[2][0] = 3;
  grid->tab[0][1] = 0;
  grid->tab[1][1] = 0;
  grid->tab[2][1] = 0;
  grid->tab[0][2] = 0;
  grid->tab[1][2] = 0;
  grid->tab[2][2] = 0;*/


	//test seed
	//char *line;

	//line = id_to_line(id,5);
	char line[6] = "312\0";

	int ID;//= line_to_id(line, 3);

	char* line_2;

	int lim = factorial(5);
	int id;

	for (int i = 0;i<lim ;i++)
	{
		line_2 = id_to_line(i+1, 5);
		printf("la ligne associ� � l'id %d est %s    ",i+1, line_2);
		id = line_to_id(line_2, 5);
		printf("l'id retrouv� est %d  \n\n", id);
	}
	



	

 /* printgrid(grid,pov);
  printf("\n");
  fill_ghost(*gridf, *grid, pov);
  printgrid_Ghost(gridf);
  free(grid); free(gridf);
  printf("\n");*/
  return EXIT_SUCCESS;
}