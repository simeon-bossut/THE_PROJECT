#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void fill_ghosts(GhostGrid gridf, Grid gridj) {
	for (int i = 0; i < gridf.size; i++) {
		for (int j = 0; j < gridf.size; j++) {
			if (gridj.tab[i][j] != NULL)
			{
				;
			}
		}
	}
}

Pos * find_in_grid(Grid grid,int val)
{
	Pos* positions;
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
	return positions;
}

