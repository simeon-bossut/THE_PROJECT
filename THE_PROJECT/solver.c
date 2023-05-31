#include "solver.h"

GhostGrid *initGhostGrid(int dim) {
  GhostGrid *grid = (GhostGrid *)malloc(sizeof(GhostGrid));
  int k = 0;
  if (!grid) {
    return NULL;
  }
  grid->size = dim;
  char ***tmp1 = (char ***)malloc(sizeof(char **) * dim);
  if (tmp1 == NULL) {
    exit(EXIT_FAILURE);
  }
  char **tmp2 = (char **)malloc(sizeof(char *) * dim);
  if (tmp2 == NULL) {
    exit(EXIT_FAILURE);
  }
  char *tmp3 = (char *)(malloc(sizeof(char) * dim + 1));
  if (tmp3 == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      while (k < dim) {
        *(tmp3 + k) = k + 1;
        k++;
      }
      *(tmp3 + k) = '\0';
      tmp2[j] = tmp3;
      tmp3 = (char *)(malloc(sizeof(char) * dim + 1));
      if (tmp3 == NULL) {
        exit(EXIT_FAILURE);
      }
      k = 0;
    }
    tmp1[i] = tmp2;
    tmp2 = (char **)malloc(sizeof(char *) * dim);
    if (tmp2 == NULL) {
      exit(EXIT_FAILURE);
    }
  }
  grid->tab = tmp1;
  grid->size = dim;
  return grid;
}

void put_number(int val, int ligne, int colonne,GhostGrid Gf)
{
	for (int k = 0;k < Gf.size;++k)
	{
		if (Gf.tab[ligne][colonne][k] != val)
		{
			Gf.tab[ligne][colonne][k] = NAS;
		}
	}
}

void suite_col(int ligne, int colonne, GhostGrid Gf)
{
	
		if(ligne==0)//Nous indique le sens d'écriture de la colonne
		{ 
			for (int k = 0;k < Gf.size;++k)
			{
				put_number(k+1,ligne+k,colonne,Gf);
			}
		}
		else if (ligne == Gf.size)
		{
			for (int k = 0;k < Gf.size;++k)
			{
				put_number(Gf.size-k, ligne-k, colonne, Gf);
			}
		}
}

void suite_row(int ligne, int colonne, GhostGrid Gf)
{
	if (colonne == 0)//Nous indique le sens d'écriture de la colonne
	{
		for (int k = 0;k < Gf.size;++k)
		{
			put_number(k + 1, ligne , colonne-k, Gf);
		}
	}
	else if (colonne == Gf.size)
	{
		for (int k = 0;k < Gf.size;++k)
		{
			put_number(Gf.size - k, ligne, colonne-k, Gf);
		}
	}
}



int Length(char* string, int size)
{
	int number = 0;
	for (int i = 0; i < size; i++) {
		if (string[i] != NAS)
		{
			number++;
		}

	}
	return number;
}

int modif_box(int i, int j,GhostGrid gridf,Grid gridj)
{
	int size = gridj.size;
	int modif = 0;
	int obv_1 = NAS;
	int obv_2 = NAS;
	if (i == 0)
	{
		obv_1 = j;
	}
	else if (i == size - 1)
	{
		obv_1 = 3 * size - 1 - j;
	}
	if (j == 0)
	{
		obv_2 = 4 * size - 1 - i;
	}
	else if (j == size - 1)
	{
		obv_2 = size + i;
	}
	if (gridj.obv[obv_1] == 1 || gridj.obv[obv_2] == 1)//cas le plus simple, on met n (size)
	{
		put_number(size, i, j, gridf);
		modif = 1;
	}

	if (gridj.obv[obv_1] == 1)//Cas suite de 1 à n sur toute la colonne
	{
		suite_col(i, j, gridf);
		modif = 1;
	}
	if (gridj.obv[obv_2] == 1)//Cas suite de 1 à n sur toute la colonne
	{
		suite_row(i, j, gridf);
		modif = 1;
	}
	if (Length(gridf.tab[i][j], gridf.size) == 1 || (obv_1 == NAS && obv_2 == NAS))//si la case en question a déjà une réponse, on peut s'arrêter là.On s'arrête aussi si les observateurs sont inexistants
	{
		return modif;
	}
	if (gridj.obv[obv_1]==0)
	{
		obv_1 = NAS;
	}
	if (gridj.obv[obv_2]==0)
	{
		obv_2 = NAS;
	}
	for (int k = 0;k < gridf.size;++k)
	{
		if (obv_1 != NAS)
		{
			if (k + 1 > size + 1 - gridj.obv[obv_1])//condition pour suppression
			{
				if (gridf.tab[i][j][k] == k + 1)
				{
					gridf.tab[i][j][k] = NAS;
					modif = 1;
				}
			}
		}
		if (obv_2 != NAS)
		{
			if (k + 1 > size + 1 - gridj.obv[obv_2])//condition pour suppression
			{
				if (gridf.tab[i][j][k] == k + 1)
				{
					gridf.tab[i][j][k] = NAS;
					modif = 1;
				}
			}
		}
	}
}

int complete_ghost(GhostGrid gridf, Grid gridj)
{
	int modif = 0;
	int size = gridj.size;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			
			modif = modif_box(i, j, gridf, gridj);
		}
	}
	return modif;

}



void maj_ghost(GhostGrid gridf, Grid gridj)
{
	int k = 0;
	int size = gridj.size;
	Pos* pos; // Pos storage

	for (int value = 1; value <= gridf.size; value++) {//Remplissage grossier de la grille fantôme à l'aide de la grille de jeu (sans observateurs)
		pos = find_in_grid(gridj, value, &size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < gridf.size; j++) {
				fill_ghost_box(gridj, gridf, value, pos[i].row, j);
				fill_ghost_box(gridj, gridf, value, j, pos[i].col);
			}
		}
		free(pos);
	}
	
}

void fill_ghost(GhostGrid gridf, Grid gridj, int* pov) {


	maj_ghost(gridf, gridj);

	//!!!Pas besoin de l'appeler plus d'une fois !!!

	complete_ghost(gridf, gridj);//complète partiellement la grille fantome à l'aide des observateurs 


}

int check_row(int val,GhostGrid *gridf, int row, int* pos)
{
	char*** tab = gridf->tab;
	int compt = 0;
	for (int i = 0;i < gridf->size;++i)
	{
		if ((tab[row][i][val - 1] == val) && (Length(tab[row][i], gridf->size) != 1))
		{
			compt++;
			*pos = i;
		}
	}
	return compt;
}

int check_col(int val, GhostGrid *gridf, int col, int* pos)
{
	char*** tab = gridf->tab;
	int compt = 0;
	for(int i=0;i<gridf->size;++i)
	{
		if ((tab[i][col][val - 1] == val)&&(Length(tab[i][col], gridf->size)!=1))
		{
			compt++;
			*pos = i;
			if(compt>1)
			{
				return compt;
			}
		}
	}
	return compt;
}



int check_loners(GhostGrid* gridf, Grid* gridj)
{
	maj_ghost(*gridf, *gridj);
	int modif = 0;
	int size = gridf->size;
	int pos = NAS;
	for (int i = 0; i < size; i++) {
		for (int j = 0;j < size;++j)
		{
			if (check_row(j+1,gridf, i, &pos) == 1)
			{
				modif = 1;
				put_number(j + 1, i, pos, *gridf);
			}
			if (check_col(j+1,gridf, i, &pos) == 1)
			{
				modif = 1;
				put_number(j + 1, pos, i, *gridf);
			}
		}
	}
	if (modif)//Si il y a eu modification on recommence tout,pour ne rien rater
	{
		check_loners(gridf,gridj);
	}
	return modif;
}

int check_paire_row(GhostGrid* gridf, int row,int longueur)
{
	int compt;
	for(int i = 0; i < gridf->size; ++i) {
		;
	}
}

int check_paire_col(GhostGrid* gridf, int col)
{
	int compt;
	for (int i = 0; i < gridf->size; ++i) {

	}
}


int hypothesis(GhostGrid* gridf, Grid* gridj)//Fonction qui fait des hypothèses et teste chaque possibilité
{
	int size = gridj->size;
	for (int i = size - 2; i > 0; --i) {
		for (int i = 0; i < size; ++i) {
			check_paire_col(gridf, i, size - 2);
			check_paire_row(gridf, i, size - 2);
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
        if (compt >= grid.size) {
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

void fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j) {
  int tmp = 0;
  int k = grid.tab[i][j][tmp];
  while (grid.tab[i][j][tmp] != '\0') {
    k = grid.tab[i][j][tmp];
    if (gridj.tab[i][j] != 0) {
      grid.tab[i][j][tmp] = NAS;
      tmp++;
    } else if (k != value) {
      grid.tab[i][j][tmp] = k;
      tmp++;
    } else if (k == value || k != 0) {
      grid.tab[i][j][tmp] = NAS;
      tmp++;
    }
  }
}

void printgrid_Ghost(GhostGrid *grid) {
  int k;
  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      k = 0;
      printf(" | ");
      printf("[");
      while (grid->tab[i][j][k]) {
        printf(" %2d ", grid->tab[i][j][k]);
        k++;
      }
      printf("]");
    }
    printf(" | ");
    printf("\n");
  }
}
Guess* find_guess(GhostGrid grid,int * found, int * guess_size) {
	int sum = 0;
	int nb = 0;
	int direction = COLLUMN;
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
				(*guess_size)++;
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
				(*guess_size)++;
			}
			sum = 0;
			j = 0;
		}
	}

  return res;
}

//void print_guess(Guess *guesses, int size) {
//  for (int k = 0; k < guesses[0].size; k++) {
//    for (int i = 0; i < size; i++) {
//      printf("[");
//      for (int j = 0; j < size; j++) {
//        printf(" %1d ", guesses[k].tab[i][j]);
//      }
//      printf("]");
//      printf("\n");
//    }
//    if (guesses[k].direction == COLLUMN) {
//      printf("ID : %d; Direction : Collumn", guesses[k].id);
//    } else if (guesses[k].direction == ROW) {
//      printf("ID : %d; Direction : Row", guesses[k].id);
//    }
//
//    printf("\n\n");
//  }
//}

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
	int size = guess_list[0].size;
	printf("create_guess_tab guess size = %d\n",guess_list->size);
	char*** tab_i = (char***)malloc(sizeof(char**) * size);
	char** tab_j = (char**)malloc(sizeof(char*) * grid.size);

	if (tab_i == NULL || tab_j==NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (guess_list[0].direction==COLLUMN)
	{
		for (int i = 0; i < size; i++) {
			tab_i[i] = guess_list[i].tab;
		}
	}
	else if (guess_list[0].direction == ROW)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < grid.size; j++)
			{
				tab_j[j] = guess_list[i].tab[j];
			}
			tab_i[i] = tab_j;
			
			tab_j = (char**)malloc(sizeof(char*) * grid.size);
			if (tab_j == NULL)
			{
				exit(EXIT_FAILURE);
			}
		}
	}
	print_tab_3(tab_i, size, grid);
	return tab_i;
}

int find_number_to_guess(char*** tab, int id) {
	printf("find_number_to_guess");
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

void fill_guess_boxes(char*** tab, int size, int id_number, Grid grid, int i, int j) {
	printf("fill_guess_boxes");
	int number = tab[i][j][id_number];
	int tmp = i+1;
	while (tmp < size)
	{
		tab[tmp][j][id_number] = NAS;
		tmp++;
	}
	tmp = j + 1;
	while (tmp < grid.size)
	{
		tab[i][tmp][id_number] = NAS;
		tmp++;
	}
	print_tab_3(tab, size, grid);
	return;
}

void print_tab_3(char*** tab, int size, Grid grid) {
	printf("print");
	for (int j = 0; j < grid.size; j++)
	{
		for (int i = 0; i < size; i++) {

			printf("[");
			for (int k = 0; k < grid.size; k++) {
				printf(" %2d ", tab[i][j][k]);
			}
			printf("]");
		}
		printf("\n");
	}
}