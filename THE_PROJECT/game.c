#include "game.h"
#include <stdio.h>
#include <stdlib.h>
 
void creatab(int size)
{
    int* tab_c = (int*)malloc(sizeof(int) * size);
    if (tab_c == NULL) {
        exit(EXIT_SUCCESS);
    }
    int** tab = (int**)malloc(sizeof(int*) * size);
    if (tab == NULL) {
        exit(EXIT_SUCCESS);
    }
    for (int i = 0; i < size; i++) {
        tab[i] = tab_c;
        tab_c = (int*)malloc(sizeof(int) * size);
        if (tab_c == NULL) {
            exit(EXIT_SUCCESS);
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 4; j++) {
            tab[i][j] = i + j;
        }
    }
   
    return EXIT_SUCCESS;
}

void affichetab(int size,int **tab)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("|%d|", tab[i][j]);
        }
        printf("\n");
    }
}

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

