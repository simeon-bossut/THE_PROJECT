#include "game.h"
#include "solver.h"
#include <stdio.h>

int **creatab(int size) {
    int* tab_c; 
  int **tab = (int **)malloc(sizeof(int *) * size);
  if (tab == NULL) {
    exit(EXIT_SUCCESS);
  }
  for (int i = 0; i < size; i++) {
      tab_c = (int*)malloc(sizeof(int) * size);
      if (tab_c == NULL) {
          exit(EXIT_SUCCESS);
      }
    *(tab + i) = tab_c;
    
  }
  return tab;
}

void free_tab(int **tab, int size) {
  for (int i = 0; i < size; ++i) {
    free(tab[i]);
  }
  free(tab);
}


void initab(int **tab, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tab[i][j] = 0;
    }
  }
}

Grid *initgrid(int dim) // init the grid size at 0 all case = 0
{
  Grid *grid = (Grid *)malloc(sizeof(Grid));
  if (!grid) {
    return NULL;
  }
  grid->size = dim;
  int **tmp = creatab(dim);
  if (tmp == NULL) {
    return 0;
  }
  grid->tab = tmp;

  initab(grid->tab, grid->size);

  grid->obv = initpov(dim);
  return grid;
}

int *initpov(int size) {
  int *pov = (int *)malloc(sizeof(int) * size * 4);
  if (!pov) {
    return NULL;
  }
  for (int i = 0; i < size * 4; i++) {
    *(pov + i) = 0;
  }
  return pov;
}

void printgrid(Grid *grid) {

  printf("     ");

  for (int i = 0; i < grid->size; i++) {
    printf("| %d |", grid->obv[i]);
  }

  printf("     \n");

  for (int i = 0; i < grid->size; ++i) {

    printf("| %d |", grid->obv[grid->size * 4 - i - 1]);

    for (int j = 0; j < grid->size; ++j) {
      printf("| %d |", grid->tab[i][j]);
    }

    printf("| %d |\n", grid->obv[grid->size + i]);
  }

  printf("     ");

  for (int i = 0; i < grid->size; i++) {
    printf("| %d |", grid->obv[grid->size * 3 - i - 1]);
  }

  printf("     \n");
  printf("\n");
}

void initElt(int *elt, int size) {
  for (int i = 0; i < size; i++) {
    elt[i] = i + 1;
  }
}

Grid *fillgrid(Grid *grid) {
  int size = grid->size;
  int *elt = (int *)malloc(sizeof(int) * size);
  if (elt == NULL) {
    return NULL;
  }
  for (int i = 0; i < size; i++) {
    initElt(elt, size);
    for (int j = 0; j < size; j++) {
      if (i == 0) {
        int r = rand() % (size - j);
        grid->tab[i][j] = elt[r];
        elt[r] = elt[size - j - 1];
      }
      if (i > 0) {
        int r = rand() % (size - j);
        int k = 0;
        while (k < i) {
          if (grid->tab[k][j] == elt[r]) {
            r = rand() % (size - j);
            k = 0;
          } else {
            k++;
          }
        }
        grid->tab[i][j] = elt[r];
        elt[r] = elt[size - j - 1];
      }
    }
  }

  return grid;
}
bool found_in_row(int **tab, int size, int row, int val) {
  for (int j = 0; j < size; ++j) {
    if (tab[row][j] == val) {
      return true;
    }
  }
  return false;
}

bool found_in_col(int **tab, int size, int col, int val) {
  for (int i = 0; i < size; ++i) {
    if (tab[i][col] == val) {
      return true;
    }
  }
  return false;
}

bool is_solved(Grid gridj) {
    for (int i = 0; i < gridj.size; i++)
    {
        for (int j = 0; j < gridj.size; j++)
        {
            if (gridj.tab[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}


Grid* read_grid(char* grid_string, int size) {
    int tmp;
    int id;
    int i = 0;
    Grid* grid = initgrid(size);
    for (id = 0; id < size * 4; id++)
    {
        tmp = grid_string[id] - 48;
        grid->obv[id] = tmp;
    }

    for (id = 0; id - size * 4 < size * size; id++)
    {
        if ((id - size * 4) >= (size * (i + 1))) {
            i++;
        }
        tmp = grid_string[id] - 48;
        grid->tab[i][(id - size * 4) % size] = tmp;
    }
    return grid;
}

int nb_hint(Grid* grid) {
    int nb_hints = 0;
    int tmp;
    int i = 0;
    for (int id = 0; id < grid->size * grid->size; id++)
    {
        if (id >= grid->size * (i + 1))
        {
            i++;
        }
        tmp = grid->tab[i][id % grid->size];
        if (tmp != 0)
        {
            nb_hints++;
        }
    }
    return nb_hints;
}
int * tab_hints(Grid * grid) {
    int nb_hints = nb_hint(grid);
    int tmp;
    int i = 0; int j = 0;
    int* tab_id;
    tab_id = (int*)malloc(sizeof(int) * nb_hints);
    if (tab_id == NULL)
    {
        exit(EXIT_FAILURE);
    }
    i = 0;
    for (int id = 0; id < grid->size * grid->size; id++)
    {
        if (id >= grid->size * (i + 1))
        {
            i++;
        }
        tmp = grid->tab[i][id % grid->size];
        if (tmp != 0)
        {
            tab_id[j] = id;
            j++;
        }
    }
    return tab_id;
}

Grid* copying_grid(Grid* grid) {
    Grid* copy = initgrid(grid->size);
    for (int i = 0; i < copy->size; i++)
    {
        for (int j = 0; j < copy->size; j++) {
            copy->tab[i][j] = grid->tab[i][j];
        }
    }
    for (int i = 0; i < copy->size*4; i++)
    {
        copy->obv[i] = grid->obv[i];
    }
    return copy;
}

Grid* hint(Grid* grid) {
    Grid * copy = copying_grid(grid);
    printgrid(copy);
    crate_solver(copy);
    int* tab_id = tab_hints(grid);
    int random = rand() % (grid->size*grid->size);
    int same = true;
    int nb_hints = nb_hint(grid);
    int id = 0;
    while (same)
    {
        same = false;
        while (id < nb_hints)
        {
            if (random == tab_id[id])
            {
                same = true;
                srand(time(NULL));
                random = rand() % (grid->size*grid->size);
            }
            id++;
        }
    }

    grid->tab[random / grid->size][random % grid->size] = copy->tab[random / grid->size][random % grid->size];
    printf("Grid \n");
    printgrid(grid);
    printf("copy \n");
    printgrid(copy);

  return copy;
}

bool is_grid_correct(Grid* grid) {
    Grid * copy = copying_grid(grid);
    int sol = crate_solver(copy);
    if (sol == 0)
    {
        return false;
    }
    return true;
}