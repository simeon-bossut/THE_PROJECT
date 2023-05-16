#include "solver.h"

GhostGrid* initGhostGrid(int dim) {
	GhostGrid* grid = (GhostGrid*)malloc(sizeof(GhostGrid));
	int k = 0;
	if (!grid) {
		return NULL;
	}
	grid->size = dim;
	char*** tmp1 = (char***)malloc(sizeof(char**)*dim);
	if (tmp1 == NULL) {
		return 0;
	}
	char** tmp2 = (char**)malloc(sizeof(char*)*dim);
	if (tmp2 == NULL) {
		return 0;
	}
	char* tmp3 = (char*)(malloc(sizeof(char)*dim));
	if (tmp3 == NULL) {
		return 0;
	}
	while(k < dim) {
		tmp3[k] = k+1;
		k++;
	}
	tmp3[k] = '\0';
	for (int i = 0; i < dim; i++) {
		tmp1[i] = tmp2;
	}

	grid->tab = tmp1;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			grid->tab[i][j] = tmp3;
		}
	}
	grid->size = dim;
	return grid;
}

void fill_ghost(GhostGrid gridf, Grid gridj, int* around) {
	int tmp; 
	int k = 0;
	Pos* pos = (Pos*)malloc(gridj.size*sizeof(Pos)); // Pos storage

	int size;
	for (int i = 0; i < gridf.size; i++)
	{
		pos = find_in_grid(gridj, i,&size);

    for (int j = 0; j < gridf.size; j++) {
      for (int k = 0; k < gridf.size; k++) {
        fill_ghost_box(gridf, i, pos[j].row, k);
        fill_ghost_box(gridf, i, k, pos[j].col);
      }
    }
  }
}

Pos *find_in_grid(Grid grid, int val,
                  int *size) // attention grid.size diff de size
{
  Pos *positions = malloc(grid.size * sizeof(Pos));
  if (positions == NULL) {
    exit(EXIT_SUCCESS);
  }
  int compt = 0;
  for (int i = 0; i < grid.size; ++i) {
    for (int j = 0; j < grid.size; ++j) {
      if (grid.tab[i][j] == val) {
        positions[compt].row = i;
        positions[compt].col = j;
      }
    }
  }
  *size = compt;
  return positions;
}

void fill_ghost_box(GhostGrid grid,int value, int i, int j) {
	int tmp = 0;
	for (int k = 0; k < grid.size; k++)
	{
		if (k != value) {
			grid.tab[i][j][tmp] = k;
		}
		else
		{
			k++;
			grid.tab[i][j][tmp] = k;
		}
		tmp++;
	}
	grid.tab[i][j][tmp] = '\0';
}

void printgrid_Ghost(GhostGrid *grid) {
	int k;
	for (int i = 0; i < grid->size; i++)
	{
		for (int j = 0; j < grid->size; j++) {
			k = 0;
			printf(" | "); printf("[");
			while (grid->tab[i][j][k])
			{
				printf(" %1d ", grid->tab[i][j][k]);
				k++;
			}
			printf("]"); 
		}
		printf(" | ");  printf("\n");
	}
	
}