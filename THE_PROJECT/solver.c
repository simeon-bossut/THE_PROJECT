#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void fill_ghost(GhostGrid gridf, Grid gridj, int* around) {
	int tmp; int l = 0;
	int* cols; int* rows; // Pos of searched numbers
	Pos* pos = (Pos*)malloc(gridj.size*sizeof(Pos)); // Pos storage
	if (gridj.tab[0][0] != 0) { // Filling ghost grid with all possibilities if it's empty
		for (int i = 0; i < gridj.size; i++) {
			for (int j = 0; j < gridj.size; i++) {
				gridf.tab[i][j] = "1234";
			}
		}
	}
	int size;
	for (int i = 0; i < gridj.size; i++)
	{
		pos = find_in_grid(gridj, i,&size);
		cols = (int*)malloc(sizeof(int) * size); rows = (int*)malloc(sizeof(int) * size);
		for (int j = 0; j < size; j++)
		{
			rows[j] = pos[j].row;
			cols[j] = pos[j].col;
		}

	}

}

Pos * find_in_grid(Grid grid,int val,int*size)//attention grid.size diff de size
{
	Pos* positions=malloc(grid.size*sizeof(Pos));
	if (positions == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	int compt = 0;
	for (int i = 0;i < grid.size;++i)
	{
		for (int  j= 0;j < grid.size;++j)
		{
			if (grid.tab[i][j] == val)
			{
				positions[compt].row = i;
				positions[compt].col = j;
			}
            
		}
	}
	*size = compt;
	return positions;
}

char* fill_ghost_box(GhostGrid grid,int value, int i, int j) {
	int tmp;
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
}