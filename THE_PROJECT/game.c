#include "game.h"

Case initCase(int value) {

	Case tmp;
	tmp.value = value;
	return tmp;
}
Grid* initgrid(int dim)//init the grid size 0 all case = 0
{
	Grid* grid = (Grid*)malloc(sizeof(Grid));
	if (!grid) { return 0; }
	grid->size = dim*dim;
	grid->tab = (Case*)malloc(sizeof(Case) * dim * dim);
	if (grid->tab) {
		for (int i = 0;i < dim*dim;++i)
		{
			grid->tab[i] = initCase(i);
		}
		return grid;
	}
	return NULL;
}

void printgrid(Grid grid)
{
	for (int i = 0;i < grid.size*grid.size;++i)
	{
		printf("| %d |", grid.tab[i].value);
		if (!i % grid.size)
		{
			printf("\n");
		}
	}


}

