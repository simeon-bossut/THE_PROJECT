#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void fill_ghost(GhostGrid gridf, Grid gridj, int* around) {
	int tmp,l = 0;
	int* cols = (int*)malloc(sizeof(int) * gridj.size); int* rows = (int*)malloc(sizeof(int) * gridj.size);
	Pos* pos = (Pos*)malloc(gridj.size*sizeof(Pos));
	if (gridj.tab[0][0] != NULL) {
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
		for (int j = 0; j < size; j++)
		{
			rows[j] = pos[j].row;
			cols[j] = pos[j].col;
		}
		for (int j = 0; j < gridj.size; j++)
		{
			for (int k = 0; k < gridj.size; k++) {
				if (k + 1 != i) {
					gridf.tab[j][rows[j]][k] = (char)(k + 1);
					gridf.tab[cols[j]][j][k] = (char)(k + 1);
					tmp = k;
				}
				else {
					k++;
					gridf.tab[j][rows[j]][k] = (char)(k + 1);
					gridf.tab[cols[j]][j][k] = (char)(k + 1);
					tmp = k;
				}
			}
			gridf.tab[cols[j]][j][tmp] = '\0';
			gridf.tab[j][rows[j]][tmp] = '\0';
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

