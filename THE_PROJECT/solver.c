#include "solver.h"
#define NAS 99 // Non available spaces
GhostGrid* initGhostGrid(int dim) {
	GhostGrid* grid = (GhostGrid*)malloc(sizeof(GhostGrid));
	int k = 0;
	if (!grid) {
		return NULL;
	}
	grid->size = dim;
	char*** tmp1 = (char***)malloc(sizeof(char**) * dim);
	if (tmp1 == NULL) {
		exit(EXIT_FAILURE);
	}
	char** tmp2 = (char**)malloc(sizeof(char*) * dim);
	if (tmp2 == NULL) {
		exit(EXIT_FAILURE);
	}
	char* tmp3 = (char*)(malloc(sizeof(char) * dim + 1));
	if (tmp3 == NULL) {
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < grid->size; i++)
	{
		for (int j = 0; j < grid->size; j++) {
			while (k < dim) {
				*(tmp3 + k) = k + 1;
				k++;
			}
			*(tmp3 + k) = '\0';
			tmp2[j] = tmp3;
			tmp3 = (char*)(malloc(sizeof(char) * dim + 1));
			if (tmp3 == NULL) {
				exit(EXIT_FAILURE);
			}
			k = 0;
		}
		tmp1[i] = tmp2;
		tmp2 = (char**)malloc(sizeof(char*) * dim);
		if (tmp2 == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	grid->tab = tmp1;
	grid->size = dim;
	return grid;
}

void fill_ghost(GhostGrid gridf, Grid gridj, int* pov) {
	int tmp; 
	int k = 0;
	Pos* pos = (Pos*)malloc(gridj.size *sizeof(Pos)); // Pos storage

	int size;
	for (int value = 1; value <= gridf.size; value++)
	{
		pos = find_in_grid(gridj, value,&size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < gridf.size; j++)
			{
				fill_ghost_box(gridj, gridf, value, pos[i].row, j);
				fill_ghost_box(gridj, gridf, value, j, pos[i].col);
			}
		}
		
    }
  
}

Pos *find_in_grid(Grid grid, int val,int *size) // attention grid.size diff de size
{
  Pos *positions = malloc(grid.size * sizeof(Pos));
  if (positions == NULL) {
    exit(EXIT_SUCCESS);
  }
  int compt = 0;
  for (int i = 0; i < grid.size; ++i) {
    for (int j = 0; j < grid.size; ++j) {
      if (grid.tab[i][j] == val) {
		if (compt>=grid.size)
		{
			return NULL;
		}
        positions[compt].row = i;
        positions[compt].col = j;
		compt++;
		
      }
    }
  }
  *size = compt;
  return positions;
}

void fill_ghost_box(Grid gridj,GhostGrid grid,int value, int i, int j) {
	int tmp = 0;
	int k = grid.tab[i][j][tmp];
	while(grid.tab[i][j][tmp] != '\0')
	{
		k = grid.tab[i][j][tmp];
		if (gridj.tab[i][j] != 0) {
			grid.tab[i][j][tmp] = NAS;
			tmp++;
		}
		else if (k != value) {
			grid.tab[i][j][tmp] = k;
			tmp++;
		}
		else if(k == value || k != 0)
		{
			grid.tab[i][j][tmp] = NAS;
			tmp++;
		}
	}
	
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

char** guess(GhostGrid grid,int * pov) {
	char* tmp = (char*)malloc(sizeof(char) * grid.size);
	char** res = (char**)malloc(sizeof(char*) * grid.size);
	int sum = 0;
	int j;
	for (int i = 0; i < grid.size; i++) {
		for (j = 0; j < grid.size; j++){
			for (int k = 0; k < grid.size; k++) {
				if (grid.tab[i][j][k] == NAS) {
					sum++;
				}
			}
		}
		if (sum == grid.size)
		{
			tmp = grid.tab[i];
			res[i] = tmp;
		}
	}
	return tmp;
}