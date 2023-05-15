#include "game.h"
#include <stdio.h>
#include <stdlib.h>

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

Box initBox(int value) {

  Box tmp;
  tmp.value = value;
  return tmp;
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

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      grid->tab[i][j] = 0;
    }
  }
  return grid;
}

int *initpov(int size) {
  int *pov = (int *)malloc(sizeof(int) * size * 4);
  if (!pov) {
    return NULL;
  }
  for (int i = 0; i < size * 4; i++) {
    pov[i] = i + 1;
  }
  return pov;
}

void printgrid(Grid *grid, int *pov) {

  printf("     ");

  for (int i = 0; i < grid->size; i++) {
    printf("| %d |", pov[i]);
  }

  printf("     \n");

  for (int i = 0; i < grid->size; ++i) {

    printf("| %d |", pov[grid->size * 4 - i - 1]);

    for (int j = 0; j < grid->size; ++j) {
      printf("| %d |", grid->tab[i][j]);
    }

    printf("| %d |\n", pov[grid->size + i]);
  }

  printf("     ");

  for (int i = 0; i < grid->size; i++) {
    printf("| %d |", pov[grid->size * 3 - i - 1]);
  }

  printf("     \n");
}