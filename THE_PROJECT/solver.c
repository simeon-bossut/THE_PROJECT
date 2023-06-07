#include "solver.h"

Grid *Crea_stock_soluce(int size) {
  Grid *stock = malloc(sizeof(Grid) * size);
  return stock;
}

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

int maj_ghost(GhostGrid gridf, Grid gridj) {
  int k = 0;
  int size = gridj.size;
  Pos *pos; // Pos storage
  int modif = 0;
  for (int value = 1; value <= gridf.size;
       value++) { // Remplissage grossier de la grille fant�me � l'aide de la
                  // grille de jeu (sans observateurs)
    pos = find_in_grid(gridj, value, &size);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < gridf.size; j++) {
        modif += fill_ghost_box(gridj, gridf, value, pos[i].row, j);
        modif += fill_ghost_box(gridj, gridf, value, j, pos[i].col);
      }
    }
    free(pos);
  }
  return modif;
}

void fill_ghost(GhostGrid gridf, Grid gridj) {
  int *pov = gridj.obv;
  maj_ghost(gridf, gridj);

  //!!!Pas besoin de l'appeler plus d'une fois !!!

  // printf
  complete_ghost(gridf, gridj); // complete partiellement la grille fantome a
                                // l'aide des observateurs
}

int check_paire_row(GhostGrid gridf, int row, int longueur) {
  int compt = 0;
  for (int i = 0; i < gridf.size; ++i) {
    if ((Length(gridf.tab[row][i], gridf.size) <= 3) &&
        (Length(gridf.tab[row][i], gridf.size) > 1)) {
      compt += (gridf.size -
                Length(gridf.tab[row][i],
                       gridf.size)); // moins de possibilté, plus de points
    }
  }
  return compt;
}

int check_paire_col(GhostGrid gridf, int col, int longueur) {
  int compt = 0;
  for (int i = 0; i < gridf.size; ++i) {
    if ((Length(gridf.tab[i][col], gridf.size) <= 3) &&
        (Length(gridf.tab[i][col], gridf.size) > 1)) {
      compt += (gridf.size -
                Length(gridf.tab[i][col],
                       gridf.size)); // moins de possibilté, plus de points
    }
  }
  return compt;
}

int find_easiest(GhostGrid grid, int *row, int *col) {
  int size = grid.size;
  int nb_pair = 0;
  int tmp;
  *col = NAS;
  *row = NAS;
  // On cherche la ligne/colonne la plus simple
  for (int i = 0; i < size; ++i) {
    tmp = check_paire_col(grid, i, size - 2);
    if (tmp > nb_pair) {
      nb_pair = tmp;
      *row = NAS;
      *col = i;
    }
    tmp = check_paire_row(grid, i, size - 2);
    if (tmp > nb_pair) {
      nb_pair = tmp;
      *col = NAS;
      *row = i;
    }
  }
  for (int i = 0; i < grid.size; ++i) {
    if (((*col != NAS) && (Length(grid.tab[i][*col], grid.size) == 2)) ||
        ((*row != NAS) && (Length(grid.tab[*row][i], grid.size) == 2))) {
      return 2;
    }
  }
  return 3;
}

GhostGrid *copy_gridf(GhostGrid *grid) {
  int size = grid->size;
  GhostGrid *gridtest = initGhostGrid(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      for (int k = 0; k < size; ++k) {
        gridtest->tab[i][j][k] = grid->tab[i][j][k];
      }
    }
  }
  return gridtest;
}

void assume_in_row(GhostGrid *gridtest, int row, int chosen,
                   int possibilities) {
  int size = gridtest->size;
  int compt = 0;
  for (int i = 0; i < size; i++) {
    if (Length(gridtest->tab[row][i], size) == possibilities) {
      for (int k = 0; k < size; ++k) {
        if (gridtest->tab[row][i][k] != NAS) {
          compt++;
        }
        if (compt == chosen) {

          put_number(k + 1, row, i, *gridtest);
          return;
        }
      }
    }
  }
}

void assume_in_col(GhostGrid *gridtest, int col, int chosen,
                   int possibilities) {
  int compt = 0;
  int val;
  int size = gridtest->size;

  for (int i = 0; i < size; i++) {
    if (Length(gridtest->tab[i][col], size) == possibilities) {
      for (int k = 0; k < size; ++k) {
        if (gridtest->tab[i][col][k] != NAS) {
          compt++;
        }
        if (compt == chosen) {

          put_number(k + 1, i, col, *gridtest);
          return;
        }
      }
    }
  }
}
Grid *copy_grid(Grid *grid) {
  int size = grid->size;
  Grid *copy = initgrid(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      copy->tab[i][j] = grid->tab[i][j];
    }
  }
  for (int i = 0; i < 4 * size; ++i) {
    copy->obv[i] = grid->obv[i];
  }
  return copy;
}

int compare_with_col(Grid *grid, int side, int pos) {
  int compt = 0;
  int max = 0;
  if (side == 0) {
    for (int i = 0; i < grid->size; ++i) {
      if (grid->tab[i][pos] > max) {
        max = grid->tab[i][pos];
        compt++;
      } else if (grid->tab[i][pos] == 0) // si la ligne n'est pas complète, elle
                                         // est considérée comme valide
      {
        return grid->obv[side * 4 + pos]; // on retourne l'observateur;
      }
    }
  } else {
    for (int i = 0; i < grid->size; ++i) {
      if (grid->tab[grid->size - 1 - i][grid->size - 1 - pos] > max) {
        max = grid->tab[grid->size - 1 - i][grid->size - 1 - pos];
        compt++;
      } else if (grid->tab[grid->size - 1 - i][grid->size - 1 - pos] == 0) {
        return grid->obv[side * 4 + pos]; // on retourne l'observateur;
      }
    }
  }
  return compt;
}

int compare_with_row(Grid *grid, int side, int pos) {
  int compt = 0;
  int max = 0;
  if (side == 1) {
    for (int i = 0; i < grid->size; ++i) {
      if (grid->tab[pos][grid->size - 1 - i] > max) {
        max = grid->tab[pos][grid->size - 1 - i];
        compt++;
      } else if (grid->tab[pos][grid->size - 1 - i] == 0) {
        return grid->obv[side * 4 + pos]; // on retourne l'observateur;
      }
    }
  } else {
    for (int i = 0; i < grid->size; ++i) {
      if (grid->tab[grid->size - 1 - pos][i] > max) {
        max = grid->tab[grid->size - 1 - pos][i];
        compt++;
      } else if (grid->tab[grid->size - 1 - pos][i] == 0) {
        return grid->obv[side * 4 + pos]; // on retourne l'observateur;
      }
    }
  }
  return compt;
}

bool compare(Grid *grid, int obv) {
  int size = grid->size;
  int side = obv / size;
  int pos = obv % size;
  int observ;
  bool valid = false;
  if (side % 2) {
    observ = compare_with_row(grid, side, pos);

  } else {
    observ = compare_with_col(grid, side, pos);
  }
  if (observ == grid->obv[obv]) {
    valid = true;
  }
  return valid;
}

bool checkup(Grid *grid) {
  int size = grid->size;
  for (int i = 0; i < 4 * size; ++i) {
    if (grid->obv[i] != 0) {
      if (compare(grid, i) == false) {
        return false;
      }
    }
  }
  return true;
}

bool err_latin_row(int row, Grid *grid) {
  int val;
  char *repertory = malloc(sizeof(char) * grid->size);
  if (repertory == NULL) {
    return true;
  }
  for (int i = 0; i < grid->size; ++i) {
    repertory[i] = '\0'; // faux avertissement
  }
  for (int i = 0; i < grid->size; ++i) {
    val = grid->tab[row][i];
    if (val != 0) {
      if ((repertory[val - 1] != 0)) {
        free(repertory);
        return true;
      }
      repertory[val - 1] = val;
    }
  }
  free(repertory);
  return false;
}

bool err_latin_col(int col, Grid *grid) {
  int val;
  char *repertory = malloc(sizeof(char) * grid->size);
  if (repertory == NULL) {
    return true;
  }
  for (int i = 0; i < grid->size; ++i) {
    repertory[i] = '\0'; // faux avertissement
  }
  for (int i = 0; i < grid->size; ++i) {
    val = grid->tab[i][col];
    if (val != 0) {
      if (repertory[val - 1] != 0) {
        free(repertory);
        return true;
      }
      repertory[val - 1] = val;
    }
  }
  free(repertory);
  return false;
}

bool check_latin(Grid *grid) {
  int err = 0;
  for (int i = 0; i < grid->size; ++i) {
    err += err_latin_row(i, grid);
    err += err_latin_col(i, grid);
    if (err != 0) {
      return false;
    }
  }
  return true;
}

int easy_resolve(GhostGrid *gridf, Grid *gridj) {
  Rule2(*gridf, *gridj);
  do {
   printgrid(gridj);
    fill_loners(gridj, *gridf);

    if (check_latin(gridj) == false) {
      return -1;
    }

  } while (maj_ghost(*gridf, *gridj) || check_loners(gridf, gridj) || Rule2(*gridf, *gridj));

  maj_ghost(*gridf, *gridj);
  fill_loners(gridj, *gridf);
  return 0;
}

int stock_soluce(
    StockSoluce *Stock,
    Grid *grid) // permet d'ajouter une solution au stock de solutions
{
  Stock->size++;
  Grid *tmp;
  if (Stock->size != 1) {
    tmp = realloc(Stock->stock, sizeof(Grid) * Stock->size);
    if (tmp == NULL) {
      return -1;
    }
    Stock->stock = tmp;
  }

  Stock->stock[Stock->size - 1] = *grid;
  free(grid);
  return 0;
}

bool hypothesis(GhostGrid *gridf, Grid *gridj, int poss, StockSoluce *Stock,
                bool first_sol,
                bool validity) // Fonction qui fait des hypotheses et teste
                               // chaque possibilite
{

  int valid = easy_resolve(gridf, gridj); // resoud le maximum possible sans
                                          // théorie printf("Ca marche ?\n\n");
  /*printgrid(gridj);
  printgrid_Ghost(gridf);*/
  if ((valid == -1) || (checkup(gridj) == false)) {
    return false;
  }
  // verif
  if (is_solved(*gridj)) {
    stock_soluce(Stock, gridj); // on stocke la soluce
    return true;
  }

  // sinon, on fait une hypothèse
  int row;
  int col;
  int size = gridf->size;

  int possibilities = find_easiest(*gridf, &row, &col); // modifie row et col

  for (int i = 0; i < possibilities; i++) {
    GhostGrid *gridftest = copy_gridf(gridf); // On copie la grille fantome
    Grid *gridjtest = copy_grid(gridj);
    if (row != NAS) {
      assume_in_row(gridftest, row, i + 1,
                    possibilities); // va permettre de a partir d'un postulat de
                                    // départ afin d'avancer
    } else if (col != NAS) {
      assume_in_col(gridftest, col, i + 1, possibilities);
    }
    int valid = (hypothesis(gridftest, gridjtest, possibilities, Stock,
                            first_sol, validity));
    if (valid == false) {
      free_grid(gridjtest);
    }
    free_ghostgrid(gridftest);
    if ((valid) && (first_sol == true)) {
      return true;
    }
    if ((valid) && (validity == true) && (Stock->size == 2)) {
      return true;
    }
  }
  return false;
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
        positions[compt].row = i; // ??? l'avertissement ?!?!
        positions[compt].col = j;
        compt++;
      }
    }
  }
  *size = compt;
  return positions;
}

int fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j) {
  int tmp = 0;
  int modif = 0;
  int k = grid.tab[i][j][tmp];
  while (grid.tab[i][j][tmp] != '\0') {
    k = grid.tab[i][j][tmp];
    if (gridj.tab[i][j] != 0) {
      if (grid.tab[i][j][tmp] != NAS) {
        modif = 1;
      }
      grid.tab[i][j][tmp] = NAS;
      tmp++;
    } else if (k != value) {

      if (grid.tab[i][j][tmp] != k) {
        modif = 1;
      }
      grid.tab[i][j][tmp] = k;

      tmp++;
    } else if (k == value || k != 0) {
      if (grid.tab[i][j][tmp] != NAS) {
        modif = 1;
      }
      grid.tab[i][j][tmp] = NAS;
      tmp++;
    }
  }
  return modif;
}

int analyse2_col(int side, int pos, GhostGrid gridf, Grid gridj) {
  int size = gridf.size;
  int modif = 0;
  if (side == 0) // de haut en bas
  {

    if (gridf.tab[1][pos][size - 2] !=
        NAS) // si obs=2 , alors n-1 ne peut être en deuxième position
    {
      gridf.tab[1][pos][size - 2] = NAS;
      modif = 1;
    }

    int val1 = gridj.tab[0][pos]; // valeur en première position
    if (val1 == 0) {
      return 0;
    }

    for (int i = 0; i < size - 1 - val1;
         ++i) // si la première case vaut 0, elle est suivie de dim
    {
      if (gridf.tab[size - 1 - i][pos][size - 1] != NAS) {
        gridf.tab[size - 1 - i][pos][size - 1] =
            NAS; // on interdit n en fin de ligne
        modif = 1;
      }
    }

  } else // de bas en haut side = 2, dernière ligne
  {
    if (gridf.tab[size - 2][size - 1 - pos][size - 2] !=
        NAS) // si obs=2 , alors n-1 ne peut être en deuxième position
    {
      if (gridf.tab[size - 2][size - 1 - pos][size - 2] != NAS) {
        gridf.tab[size - 2][size - 1 - pos][size - 2] = NAS;
        modif = 1;
      }
    }

    int val1 = gridj.tab[size - 1][pos]; // valeur en première positionc
    if (val1 == 0) {
      return 0;
    }

    for (int i = 0; i < size - 1 - val1;
         ++i) // si la première case vaut 0, elle est suivie de dim
    {
      if (gridf.tab[i][size - 1 - pos][size - 1] != NAS) {
        gridf.tab[i][size - 1 - pos][size - 1] =
            NAS; // on interdit n en fin de ligne
        modif = 1;
      }
    }
  }
  return modif;
}

int analyse2_row(int side, int pos, GhostGrid gridf, Grid gridj) {
  int modif = 0;
  int size = gridf.size;
  if (side == 1) // de droite à gauche
  {
    if (gridf.tab[pos][size - 2][size - 2] != NAS) {
      gridf.tab[pos][size - 2][size - 2] = NAS;
      modif = 1;
    }
    // si obs=2 , alors n-1 ne peut être en deuxième position

    int val1 = gridj.tab[pos][size - 1]; // valeur en première position
    if (val1 == 0) {
      return 0;
    }

    for (int i = 0; i < size - 1 - val1;
         ++i) // si la première case vaut 0, elle est suivie de dim
    {
      if (gridf.tab[pos][i][size - 1] != NAS) {
        gridf.tab[pos][i][size - 1] = NAS; // on interdit n en fin de ligne
        modif = 1;
      }
    }

  } else // de gauche à droite side = 3, dernière ligne
  {
    if (gridf.tab[size - 1 - pos][1][size - 2] !=
        NAS) // si obs=2 , alors n-1 ne peut être en deuxième position
    {
      gridf.tab[size - 1 - pos][1][size - 2] = NAS;
      modif = 1;
    }

    int val1 = gridj.tab[size - 1 - pos][0]; // valeur en première position
    if (val1 == 0) {
      return 0;
    }
    for (int i = 0; i < size - 1 - val1;
         ++i) // si la première case vaut 0, elle est suivie de dim
    {
      if (gridf.tab[size - 1 - pos][size - 1 - i][size - 1] != NAS) {
        gridf.tab[size - 1 - pos][size - 1 - i][size - 1] =
            NAS; // on interdit n en fin de ligne
        modif = 1;
      }
    }
  }
  return modif;
}

int change2(int side, int pos, GhostGrid gridf, Grid gridj) {
  int modif = 0;
  if (side % 2) { // on travaille sur les cotes gauche et droit .On regardera
                  // donc des lignes

    modif = analyse2_row(side, pos, gridf, gridj);
  } else // on travaille sur les cotes haut et bas .On regardera donc des
         // colonne
  {
    modif = analyse2_col(side, pos, gridf, gridj);
  }
  return modif;
}

int Rule2(GhostGrid gridf, Grid gridj) // proprietes des obs[]=2
{
  int modif = 0;
  int size = gridj.size;
  for (int i = 0; i < 4 * gridj.size; ++i) // parcourt du tableau d'observateurs
  {
    if (gridj.obv[i] == 2) {
      int side = i / size;
      int pos = i % size;
      modif += change2(side, pos, gridf, gridj);
    }
  }
  return modif;
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
        gridf.tab[i][j][tmp - 1] = NAS;
      }
      sum = 0;
    }
  }
  return res;
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

void free_tab_3(char ***tab, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; j++) {
      free(tab[i][j]);
    }
    free(tab[i]);
  }
  free(tab);
}

void print_Stock(StockSoluce *Stock) {
  for (int i = 0; i < Stock->size; ++i) {
    printf("Solution numero %d:\n\n", i + 1);
    printgrid(Stock->stock + i);
  }
}

int subcrate_solver(Grid *gridj, bool first_sol, bool validity) //
{
  GhostGrid *gridf = initGhostGrid(gridj->size);
  fill_ghost(*gridf, *gridj);
  StockSoluce *Stock = malloc(sizeof(StockSoluce));
  if (Stock == NULL) {
    return 0;
  }
  Stock->stock = malloc(sizeof(Grid));
  Stock->size = 0;
  hypothesis(gridf, gridj, 0, Stock, first_sol, validity);

    int sol = Stock->size;
    if (Stock->size == 1)
    {
        *gridj = Stock->stock[0];
    }
    for (int i = 1; i < Stock->size; ++i)
    {
        free_grid(Stock->stock+i);
    }
    free(Stock->stock);
    free(Stock);

  return sol;
}

int crate_solver(Grid *gridj) { // 1 si l'on s'arrete à la premiere solution
                                // renvoie le snombre de solutions

  return subcrate_solver(gridj, true, false);
}

bool unique_solution(
    Grid *grid) // version du solveur qui ne récupère pas la solution
{
    Grid* copy = copy_grid(grid);
    int sol=subcrate_solver(copy,false,true);//On s'arrête à la deuxième solution si elle existe
    
    free(copy->obv);
    free_tab(copy->tab,copy->size);

    if (sol == 1)
    {
        return true;
    }
     
    
    return false;
}

void indice(Grid* grid,int nb_hints)
{
    int size = grid->size;
    Grid* sol = initgrid(size);
    subcrate_solver(sol, true, false);
    int random;
    for(int i=0;i<nb_hints;++i)
    { 
        do {
            random = rand() % (size * size);
        } while (grid->tab[random / size][random % size] == sol->tab[random / size][random % size]);
        grid->tab[random] = sol->tab[random];
    }
    free_grid(sol);
}