#include "game.h"
#include <stdio.h>

int **creatab(int size) {
  int *tab_c = (int *)malloc(sizeof(int) * size);
  if (tab_c == NULL) {
    exit(EXIT_SUCCESS);
  }
  int **tab = (int **)malloc(sizeof(int *) * size);
  if (tab == NULL) {
    exit(EXIT_SUCCESS);
  }
  for (int i = 0; i < size; i++) {
    *(tab + i) = tab_c;
    tab_c = (int *)malloc(sizeof(int) * size);
    if (tab_c == NULL) {
      exit(EXIT_SUCCESS);
    }
  }
  return tab;
}

void free_tab(int** tab,int size)
{
    for (int i = 0;i < size;++i)
    {
        free(tab[i]);
    }
    free(tab);
}

void initab(int** tab, int size)
{
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
    *(pov + i) = i + 1;
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
bool found_in_row(int** tab, int size, int row, int val) {
  for (int j = 0; j < size; ++j) {
    if (tab[row][j] == val) {
      return true;
    }
  }
  return false;
}

bool found_in_col(int** tab, int size, int col, int val) {
  for (int i = 0; i < size; ++i) {
    if (tab[i][col] == val) {
      return true;
    }
  }
  return false;
}

