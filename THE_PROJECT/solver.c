#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void fill_ghost(GhostGrid gridf, Grid gridj, int* around) {
	int row, col,tmp;
	if (gridj.tab[0][0] != NULL) {
		for (int i = 0; i < gridj.size; i++) {
			for (int j = 0; j < gridj.size; i++) {
				gridf.tab[i][j] = "1234";
			}
		}
	}
	for (int i = 0; i < gridj.size; i++)
	{
		row = find_in_grid(gridj, i)->row;
		col = find_in_grid(gridj, i)->col;
		for (int j = 0; j < gridj.size; j++)
		{
			for (int k = 0; k < gridj.size; k++) {
				if (k + 1 != i) {
					gridf.tab[j][col][k] = (char)(k + 1);
					gridf.tab[row][j][k] = (char)(k + 1);
					tmp = k;
				}
				else {
					k++;
					gridf.tab[j][col][k] = (char)(k + 1);
					gridf.tab[row][j][k] = (char)(k + 1);
					tmp = k;
				}
			}
			gridf.tab[j][col][tmp] = '\0';
			gridf.tab[row][j][tmp] = '\0';
		}
	}

}

Pos * find_in_grid(Grid grid,int val)
{
	Pos* positions=malloc(grid.size*sizeof(Pos));
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

