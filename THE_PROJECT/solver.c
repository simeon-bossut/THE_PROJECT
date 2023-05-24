#include "solver.h"

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

void fill_ghost(GhostGrid gridf, Grid gridj) {
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
				printf(" %2d ", grid->tab[i][j][k]);
				k++;
			}
			printf("]"); 
		}
		printf(" | ");  printf("\n");
	}
	
}
Guess* find_guess(GhostGrid grid,int * found, int * guess_size) {
	int sum = 0;
	int nb = 0;
	int direction;
	int size;
	*guess_size = 0;
	*found = NOT_FOUND;
	for (int i = 0; i < grid.size; i++)
	{
		for (int j = 0; j < grid.size; j++) {
			for (int k = 0; k < grid.size; k++)
			{
				if (grid.tab[i][j][k] == NAS) {
					sum++;
				}
			}
		}
		if (sum == grid.size * grid.size)
		{
			nb++;
			direction = ROW;
		}
		sum = 0;
	}
	for (int i = 0; i < grid.size; i++)
	{
		for (int j = 0; j < grid.size; j++) {
			for (int k = 0; k < grid.size; k++)
			{
				if (grid.tab[j][i][k] == NAS) {
					sum++;
				}
			}
		}
		if (sum == grid.size * grid.size)
		{
			nb++;
			direction = COLLUMN;
		}
		sum = 0;
	}
	size = grid.size - nb;
	Guess* res = (Guess*)malloc(sizeof(Guess) * size);
	bool boolean = true;
	if (res == NULL)
	{
		exit(EXIT_FAILURE);
	}
	char** tmp = (char**)malloc(sizeof(char*) * grid.size);
	if (tmp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	int pos = 0;
	if (direction == ROW && size >= 1)
	{
		for (int i = 0; i < grid.size; i++)
		{
			for (int j = 0; j < grid.size; j++) {
				for (int k = 0; k < grid.size; k++)
				{
					if (grid.tab[i][j][k] == NAS) {
						sum++;
					}
				}
			}
			if (sum == grid.size || sum == grid.size * 2 || sum == grid.size * 3)
			{
				res[pos].tab = grid.tab[i];
				res[pos].id = i;
				res[pos].direction = ROW;
				res[pos].size = size;
				pos++;
				*found = FOUND;
				*guess_size++;
			}
			sum = 0;
		}
		
	}
	
	else if (direction == COLLUMN && size >= 1)
	{
		int j;
		for (int i = 0; i < grid.size; i++)
		{
			for (j = 0; j < grid.size; j++) {
				for (int k = 0; k < grid.size; k++)
				{
					if (grid.tab[j][i][k] == NAS) {
						sum++;
					}
				}
				tmp[j] = grid.tab[j][i];
			}
			if (sum == grid.size || sum == grid.size *2 || sum == grid.size * 3)
			{
				res[pos].tab = tmp;
				res[pos].id = i;
				res[pos].direction = COLLUMN;
				res[pos].size = size;
				pos++;
				*found = FOUND;
				*guess_size++;
			}
			sum = 0;
			j = 0;
		}
	}

	return res;
}

void print_guess(Guess* guesses, int size) {
	for (int k = 0; k <guesses->size ; k++)
	{
		for (int i = 0; i < size; i++)
		{
			printf("[");
			for (int j = 0; j < size; j++) {
				printf(" %1d ", guesses[k].tab[i][j]);
			}
			printf("]");
			printf("\n");
		}
		if (guesses[k].direction == COLLUMN)
		{
			printf("ID : %d; Direction : Collumn", guesses[k].id);
		}
		else if (guesses[k].direction == ROW)
		{
			printf("ID : %d; Direction : Row", guesses[k].id);
		}
		
		printf("\n\n");
	}


}

int fill_loners(Grid* gridj, GhostGrid gridf) {
	int size = gridj->size;
	int sum = 0;
	int tmp;
	int res = NOT_FOUND;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++) 
			{
				if (gridf.tab[i][j][k] == NAS) {
					sum++;
				}
				if (gridf.tab[i][j][k] != NAS)
				{
					tmp = gridf.tab[i][j][k];
				}
			}
			if (sum == size-1)
			{
				gridj->tab[i][j] = tmp;
				res = FOUND;
			}
			sum = 0;
		}
	}
	return res;
}

int fill_guess(GhostGrid gridf, Grid gridj) {
	int res = NOT_FOUND;
	int* pov = gridj.obv;
	int size = gridj.size;
	int guess_size;
	int** tabj = gridj.tab;
	int tmp;
	Guess* guess_list = find_guess(gridf,&res,&guess_size);
	char*** guess_tab = create_guess_tab(guess_list, gridj);
	if (res == FOUND) {
		int* north = (int*)malloc(sizeof(int) * size);
		int* east = (int*)malloc(sizeof(int) * size);
		int* south = (int*)malloc(sizeof(int) * size);
		int* west = (int*)malloc(sizeof(int) * size);
		Guess** guess_copies = (Guess**)malloc(sizeof(Guess*)*guess_size);
		if (north == NULL || east == NULL || south == NULL || west == NULL || guess_copies == NULL)
		{
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < guess_size; i++)
		{
			for (int j = 0; j < guess_size; j++)
			{
				guess_copies[i][j] = guess_list[j];
			}
		}

		for (int i = 0; i < size*4; i++)
		{
			if (i < 1*size) {
				*(north + i) = pov[i];
			}
			else if (i < 2*size) {
				*(east + i) = pov[i];
			}
			else if (i < 3*size) {
				*(south+ i) = pov[i];
			}
			else if (i < 4*size) {
				*(west + i) = pov[i];
			}
		}


		/*int j = 0;
		if (guess_list[0].direction == COLLUMN)
		{
			for (int i = 0; i < guess_size; i++)
			{
				while(guess_list[i].tab[j] != NAS)
				{

				}
			}
		}
		else if(guess_list[0].direction == ROW)
		{

		}*/
	}
	return res;
}
char*** create_guess_tab(Guess* guess_list,Grid grid) {
	char*** tab_i = (char***)malloc(sizeof(char**) * guess_list[0].size);
	char** tab_j = (char**)malloc(sizeof(char*) * grid.size); 
	if (tab_i == NULL || tab_j==NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (guess_list[0].direction==COLLUMN)
	{
		for (int i = 0; i < guess_list[0].size; i++) {
			tab_i[i] = guess_list[i].tab;
		}
	}
	else if (guess_list[0].direction == ROW)
	{
		for (int i = 0; i < guess_list[0].size; i++)
		{
			for (int j = 0; j < grid.size; j++)
			{
				tab_j[j] = guess_list[i].tab[j];
			}
			tab_i[i] = tab_j;
		}
	}
	//Affichage debug
	for (int j = 0; j < grid.size; j++)
	{
		for (int i = 0; i < guess_list[0].size; i++) {
			
			printf("[");
			for (int k = 0; k < grid.size; k++) {
				printf(" %2d ", tab_i[i][j][k]);
			}
			printf("]");
		}
		printf("\n");
	}
	// Affichage debug fin */
	return tab_i;
}

int find_number_to_guess(char*** tab, int id) {
	int number = 0;
	int sum = 0;
	int k = 0;
	while (tab[0][0][k] == NAS || sum != id) {
		if (tab[0][0][k] == NAS)
		{
			sum++;
		}
		k++;
	}
	return k;
}
Guess* fill_guess_boxes(char*** tab, int size, int id_number, Grid grid) {
	int number = tab[0][0][id_number];
}