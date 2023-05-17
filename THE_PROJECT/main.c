#include "game.h"
#include "solver.h"
#include "seed.h"
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

  //printgrid(grid, pov);


	//test seed
	int val = 15;
	char id[3] = "7";
	//char *line;

	//line = id_to_line(id,5);
	char line[6] = "43521\0";

	int ID = line_to_id(line, 5);

	char *line_2;
		
	line_2=id_to_line(ID,5);

	printf("la ligne est %s \n", line);

	printf("l'ID associé est %d\n", ID);

	printf("la ligne retrouvée est %s", line_2);


	

  return EXIT_SUCCESS;
}