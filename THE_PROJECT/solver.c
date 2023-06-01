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
  char **tmp2;
  char *tmp3;

  for (int i = 0; i < grid->size; i++) {
    tmp2 = (char **)malloc(sizeof(char *) * dim);
    if (tmp2 == NULL) {
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < grid->size; j++) {
      tmp3 = (char *)(malloc(sizeof(char) * dim + 1));
      if (tmp3 == NULL) {
        exit(EXIT_FAILURE);
      }
      while (k < dim) {
        *(tmp3 + k) = k + 1;
        k++;
      }
      *(tmp3 + k) = '\0';

      tmp2[j] = tmp3;

      k = 0;
    }
    tmp1[i] = tmp2;
  }
  grid->tab = tmp1;
  grid->size = dim;
  return grid;
}





void maj_ghost(GhostGrid gridf, Grid gridj) {
  int k = 0;
  int size = gridj.size;
  Pos *pos; // Pos storage

  for (int value = 1; value <= gridf.size;value++) { // Remplissage grossier de la grille fant�me � l'aide de la
                  // grille de jeu (sans observateurs)
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

void fill_ghost(GhostGrid gridf, Grid gridj) {
  int* pov = gridj.obv;
  maj_ghost(gridf, gridj);

  //!!!Pas besoin de l'appeler plus d'une fois !!!

  complete_ghost(gridf, gridj); // complete partiellement la grille fantome a
                                // l'aide des observateurs
}


int check_paire_row(GhostGrid gridf, int row, int longueur) {
  int compt=0;
  for (int i = 0; i < gridf.size; ++i) {
      if (Length(gridf.tab[row][i], gridf.size) <= 2)
      {
          compt++;
      }
  }
  return compt;
}

int check_paire_col(GhostGrid gridf, int col, int longueur) {
  int compt=0;
  for (int i = 0; i < gridf.size; ++i) {
      if (Length(gridf.tab[i][col], gridf.size) <= 2)
      {
          compt++;
      }
  }
  return compt;
}

void find_easiest(GhostGrid grid,int *row,int*col)
{
    int size = grid.size;
    int nb_pair = 0;
    int tmp;
    *col = NAS;
    *row = NAS;
   //On cherche la ligne/colonne la plus simple
        for (int i = 0; i < size; ++i) {
            tmp = check_paire_col(grid, i, size - 2);
            if (tmp > nb_pair)
            {
                nb_pair = tmp;
                *row = NAS;
                *col = i;
            }
            tmp = check_paire_row(grid, i, size - 2);
            if (tmp > nb_pair)
            {
                nb_pair = tmp;
                *col = NAS;
                *row = i;
            }
        }
}

GhostGrid* copy_gridf(GhostGrid *grid)
{
    int size = grid->size;
    GhostGrid* gridtest = initGhostGrid(size);
    for (int i = 0;i < size;++i)
    {
        for (int j = 0;j < size;++j)
        {
            for (int k = 0;k < size;++k)
            {
                gridtest->tab[i][j][k] = grid->tab[i][j][k];
            }
        }
    }
    return gridtest;
}

void assume_in_row(GhostGrid *gridtest, int row)
{
    int size = gridtest->size;
    for (int i = 0;i < size;i++)
    {
        if(Length(gridtest->tab[row][i],size)==2)
        { 
            int k = 0;
            while(gridtest->tab[row][i][k]==NAS)
            {
                k++;
            }
            put_number(k + 1, row, i, *gridtest);
            return;
        }
    }
}

void assume_in_col(GhostGrid *gridtest,int col)
{

    int size = gridtest->size;
    for (int i = 0;i < size;i++)
    {
        if (Length(gridtest->tab[i][col], size) == 2)
        {
            int k = 0;
            while (gridtest->tab[i][col][k] == NAS)
            {
                k++;
            }
            put_number(k + 1, i, col, *gridtest);
            return;
        }
    }
}

int hypothesis(GhostGrid *gridf,Grid *gridj) // Fonction qui fait des hypoth�ses et teste chaque possibilit�
{
    int row;
    int col;
    int size = gridf->size;
    GhostGrid* gridtest = copy_gridf(gridf);//On copie la grille fantome
    find_easiest(*gridtest, &row,&col);//modifie row et col
    if (row != NAS)
    {
        assume_in_row(gridtest,row);//va permettre de aprtir d'un postulat de départ afin d'avancer
    }
    else if (col != NAS)
    {
        assume_in_col(gridtest,col);
    }

    printf("THEORIE \n\n");

    fill_loners(gridj, *gridtest);
    maj_ghost(*gridtest, *gridj);
    fill_ghost(*gridtest, *gridj);
    printgrid_Ghost(gridtest);
    printf("\n\n\n");
    check_loners(gridtest, gridj);
    printf("Loners\n\n");
    printgrid_Ghost(gridtest);

    printf("MAJ_1\n\n");
    fill_loners(gridj, *gridtest);
    maj_ghost(*gridtest, *gridj);
    printgrid_Ghost(gridtest);

    printgrid(gridj);
    printf("Rule\n");
    Rule2(*gridtest, *gridj);
    check_loners(gridtest, gridj);
    printgrid_Ghost(gridtest);
  
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




int analyse2_col(int side, int pos,GhostGrid gridf, Grid gridj)
{
    int size = gridf.size;
    if (side == 0)//de haut en bas
    {

        gridf.tab[1][pos][size - 2] = NAS;//si obs=2 , alors n-1 ne peut être en deuxième position

        int val1 = gridj.tab[0][pos];//valeur en première position
        if (val1 == 0)
        {
            return 0;
        }

        for (int i = 0;i < size - 1 - val1;++i)// si la première case vaut 0, elle est suivie de dim
        {
            gridf.tab[size - 1 - i][pos][size - 1] = NAS;//on interdit n en fin de ligne
        }


    }
    else// de bas en haut side = 2, dernière ligne
    {
        gridf.tab[size - 2][size - 1 - pos][size - 2] = NAS;//si obs=2 , alors n-1 ne peut être en deuxième position


        int val1 = gridj.tab[size-1][pos];//valeur en première positionc
        if (val1 == 0)
        {
            return 0;
        }

        for (int i = 0;i < size - 1 - val1;++i)// si la première case vaut 0, elle est suivie de dim
        {
            gridf.tab[i][size - 1 - pos][size - 1] = NAS;//on interdit n en fin de ligne
        }

    }
}


int analyse2_row(int side, int pos, GhostGrid gridf, Grid gridj)
{
    int size = gridf.size;
    if (side == 1)//de droite à gauche
    {

        gridf.tab[pos][size-2][size - 2] = NAS;//si obs=2 , alors n-1 ne peut être en deuxième position

        int val1 = gridj.tab[pos][size-1];//valeur en première position
        if (val1 == 0)
        {
            return 0;
        }
        
        for (int i = 0;i < size - 1 - val1;++i)// si la première case vaut 0, elle est suivie de dim
        {
            gridf.tab[pos][i][size - 1] = NAS;//on interdit n en fin de ligne
            return 1;
        }

       
    }
    else// de gauche à droite side = 3, dernière ligne
    {
        gridf.tab[size-1-pos][1][size - 2] = NAS;//si obs=2 , alors n-1 ne peut être en deuxième position


        int val1 = gridj.tab[size-1-pos][0];//valeur en première position
        if (val1 == 0)
        {
            return 0;
        }
        for (int i = 0;i < size - 1 - val1;++i)// si la première case vaut 0, elle est suivie de dim
        {
            gridf.tab[size - 1 - pos][size-1-i][size - 1] = NAS;//on interdit n en fin de ligne
            return 1;
        }
       
    }
    return 0;
}


int change2(int side,int pos,GhostGrid gridf,Grid gridj)
{
    
    if((side + 1) / 2) { //on travaille sur les cotes haut et bas .On regardera donc des colonne
        
        analyse2_col(side, pos, gridf, gridj);
    }
    else //on travaille sur les cotes gauche et droit .On regardera donc des lignes
    {
        analyse2_row(side, pos, gridf, gridj);
    }
}

int Rule2(GhostGrid gridf, Grid gridj)//proprietes des obs[]=2
{
    for (int i = 0;i < 4 * gridj.size;++i)//parcourt du tableau d'observateurs
    {
        if (gridj.obv[i] == 2)
        {
            int side = i / 4;
            int pos = i % 4;
            change2(side, pos, gridf, gridj);
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
Guess *find_guess(GhostGrid grid, int *found, int *guess_size) {
  int sum = 0;
  int nb = 0;
  int direction = COLLUMN;
  int size;
  *guess_size = 0;
  *found = NOT_FOUND;
  for (int i = 0; i < grid.size; i++) {
    for (int j = 0; j < grid.size; j++) {
      for (int k = 0; k < grid.size; k++) {
        if (grid.tab[i][j][k] == NAS) {
          sum++;
        }
      }
    }
    if (sum == grid.size * grid.size) {
      nb++;
      direction = ROW;
    }
    sum = 0;
  }
  for (int i = 0; i < grid.size; i++) {
    for (int j = 0; j < grid.size; j++) {
      for (int k = 0; k < grid.size; k++) {
        if (grid.tab[j][i][k] == NAS) {
          sum++;
        }
      }
    }
    if (sum == grid.size * grid.size) {
      nb++;
      direction = COLLUMN;
    }
    sum = 0;
  }

  size = grid.size - nb;
  Guess *res = (Guess *)malloc(sizeof(Guess) * size);
  bool boolean = true;
  if (res == NULL) {
    exit(EXIT_FAILURE);
  }
  char **tmp = (char **)malloc(sizeof(char *) * grid.size);
  if (tmp == NULL) {
    exit(EXIT_FAILURE);
  }
  int pos = 0;
  if (direction == ROW && size >= 1) {
    for (int i = 0; i < grid.size; i++) {
      for (int j = 0; j < grid.size; j++) {
        for (int k = 0; k < grid.size; k++) {
          if (grid.tab[i][j][k] == NAS) {
            sum++;
          }
        }
      }
      if (sum == grid.size || sum == grid.size * 2 || sum == grid.size * 3) {
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

  else if (direction == COLLUMN && size >= 1) {
    int j;
    for (int i = 0; i < grid.size; i++) {
      for (j = 0; j < grid.size; j++) {
        for (int k = 0; k < grid.size; k++) {
          if (grid.tab[j][i][k] == NAS) {
            sum++;
          }
        }
        tmp[j] = grid.tab[j][i];
      }
      if (sum == grid.size || sum == grid.size * 2 || sum == grid.size * 3) {
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

// void print_guess(Guess *guesses, int size) {
//   for (int k = 0; k < guesses[0].size; k++) {
//     for (int i = 0; i < size; i++) {
//       printf("[");
//       for (int j = 0; j < size; j++) {
//         printf(" %1d ", guesses[k].tab[i][j]);
//       }
//       printf("]");
//       printf("\n");
//     }
//     if (guesses[k].direction == COLLUMN) {
//       printf("ID : %d; Direction : Collumn", guesses[k].id);
//     } else if (guesses[k].direction == ROW) {
//       printf("ID : %d; Direction : Row", guesses[k].id);
//     }
//
//     printf("\n\n");
//   }
// }

int fill_loners(Grid *gridj, GhostGrid gridf) {
  int size = gridj->size;
  int sum = 0;
  int tmp;
  int res = NOT_FOUND;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        if (gridf.tab[i][j][k] == NAS) {
          sum++;
        }
        if (gridf.tab[i][j][k] != NAS) {
          tmp = gridf.tab[i][j][k];
        }
      }
      if (sum == size - 1) {
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
  int *pov = gridj.obv;
  int size = gridj.size;
  int guess_size;
  int **tabj = gridj.tab;
  Guess *guess_list = find_guess(gridf, &res, &guess_size);
  char ***guess_tab = create_guess_tab(guess_list, gridj);
  if (res == FOUND) {
    int *north = (int *)malloc(sizeof(int) * size);
    int *east = (int *)malloc(sizeof(int) * size);
    int *south = (int *)malloc(sizeof(int) * size);
    int *west = (int *)malloc(sizeof(int) * size);
    Guess **guess_copies = (Guess **)malloc(sizeof(Guess *) * guess_size);
    if (north == NULL || east == NULL || south == NULL ||
        west == NULL /*|| guess_copies == NULL*/) {
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size * 4; i++) {
      if (i < 1 * size) {
        *(north + i) = pov[i];
      } else if (i < 2 * size) {
        *(east + i - size) = pov[i];
      } else if (i < 3 * size) {
        *(south + i - 2 * size) = pov[i];
      } else if (i < 4 * size) {
        *(west + i - 3 * size) = pov[i];
      }
    }
    free(north);
    free(south);
    free(west);
    free(east);
    for (int id = 0; id < guess_size; id++) {
      guess_list = guess_copies[id];
      fill_sub_guess(guess_tab, guess_size, gridj, id);
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
char ***create_guess_tab(Guess *guess_list, Grid grid) {
  int size = guess_list[0].size;
  printf("create_guess_tab guess size = %d\n", guess_list->size);
  char ***tab_i = (char ***)malloc(sizeof(char **) * size);
  char **tab_j;
  if (tab_i == NULL) {
    exit(EXIT_FAILURE);
  }
  if (guess_list[0].direction == COLLUMN) {
    for (int i = 0; i < size; i++) {
      tab_i[i] = guess_list[i].tab;
    }
  } else if (guess_list[0].direction == ROW) {
    for (int i = 0; i < size; i++) {
      tab_j = (char **)malloc(sizeof(char *) * grid.size);
      if (tab_j == NULL) {
        exit(EXIT_FAILURE);
      }
      for (int j = 0; j < grid.size; j++) {
        tab_j[j] = guess_list[i].tab[j];
      }
      tab_i[i] = tab_j;

      if (tab_j == NULL) {
        exit(EXIT_FAILURE);
      }
    }
  }
  print_tab_3(tab_i, size, grid);
  return tab_i;
}

int find_number_to_guess(char ***tab, int id) {
  printf("find_number_to_guess");
  int number = 0;
  int sum = 0;
  int k = 0;
  while (!(tab[0][0][k] != NAS && sum != id)) {
    if (tab[0][0][k] == NAS) {
      sum++;
    }
    k++;
  }
  return k;
}

void fill_guess_boxes(char*** tab, int size, int id_number, Grid grid, int i,
    int j) {
    printf("fill_guess_boxes\n");
    id_number = find_number_to_guess(tab, id_number);
    int sum = 0;
    int number;
    int tmp;
    for (int k = 0; k < grid.size; k++) {
        if (tab[i][j][k] != NAS) {
            sum++;
        }
    }
    if (sum != 1) {
        number =
            tab[i][j][id_number]; // id_number s'obtient avec find_number_to_guess
        tmp = i + 1;
        while (tmp < size) {
            tab[tmp][j][id_number] = NAS;
            tmp++;
        }
        tmp = j + 1;
        while (tmp < grid.size) {
            tab[i][tmp][id_number] = NAS;
            tmp++;
        }
    }
    else {
        int k = 0;
        while (tab[i][j][k] == NAS) {
            k++;
        }
        id_number = k;
        number =
            tab[i][j][id_number]; // id_number s'obtient avec find_number_to_guess
        tmp = i + 1;
        while (tmp < size) {
            tab[tmp][j][id_number] = NAS;
            tmp++;
        }
        tmp = j + 1;
        while (tmp < grid.size) {
            tab[i][tmp][id_number] = NAS;
            tmp++;
        }
    }
    print_tab_3(tab, size, grid);

  return;
}

void print_tab_3(char ***tab, int size, Grid grid) {
  printf("print\n");
  for (int j = 0; j < grid.size; j++) {
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

void fill_sub_guess(int ***tab, int guess_size, Grid grid, int id) {
  int grid_size = grid.size;

  for (int i2 = 0; i2 < guess_size; i2++) {
    for (int j2 = 0; j2 < grid_size; j2++) {
      fill_guess_boxes(tab, guess_size, id, grid, i2, j2);
    }
  }
}

void free_tab_3(int*** tab, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; j++)
		{
			free(tab[i][j]);
		}
		free(tab[i]);
	}
	free(tab);
}



bool crate_solver(Grid * adgridj) {
	Grid gridj = *adgridj;
	GhostGrid * adgridf = initGhostGrid(gridj.size);
	GhostGrid gridf = *adgridf;
    fill_ghost(gridf, gridj);
    int modif;
	do
	{
        modif = 0;

        while (hypothesis(adgridf,adgridj) == FOUND)
        {
            maj_ghost(gridf, gridj); modif++;
        }
        while (fill_loners(adgridj, gridf) == FOUND)
        {
            maj_ghost(gridf, gridj); modif++;
        }

		printgrid(adgridj);
    } while (modif != 0 && !(is_solved(gridj)));
    if (is_solved(gridj))
    {
        return true;
    }
	return false;
}

