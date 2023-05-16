#include "game.h"
#include "solver.h"
#include "seed.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  srand(time(NULL));

  int size = argv[1] ? atoi(argv[1]) : 3;

  int *pov;
  pov = initpov(size);

  Grid *grid = initgrid(size);
  if (grid == NULL) {
    return 0;
  }

  // fillgrid(grid);
  //  grid_completion(grid);

  printgrid(grid, pov);


	//test seed
	/*int val = 15;
	char id[3] = "7";
	char *line;
	line = id_to_line(id);

	printf("%s ", line);*/
	

  return EXIT_SUCCESS;
}