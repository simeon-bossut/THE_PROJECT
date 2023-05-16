#include "game.h"
#include "solver.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int **creatab_2d(int size) {
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
  int **tmp = creatab_2d(dim);
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

bool found_in_row(int val, Grid *grid, int row) {
  for (int j = 0; j < grid->size; ++j) {
    if (grid->tab[row][j] == val) {
      return true;
    }
  }
  return false;
}

bool found_in_col(int val, Grid *grid, int col) {
  for (int i = 0; i < grid->size; ++i) {
    if (grid->tab[i][col] == val) {
      return true;
    }
  }
  return false;
}

void grid_completion(Grid *grid) {
  int num;
  for (int i = 0; i < grid->size; i++) {
    for (int j = 0; j < grid->size; j++) {
      do {
        num = (rand() % grid->size) + 1; // Entre 1 et n

      } while (found_in_col(num, grid, j) || found_in_row(num, grid, i));
      grid->tab[i][j] = num;
    }
  }
}

void printgrid(Grid *grid, int *pov) {

  printf("      ");

  for (int i = 0; i < grid->size; i++) {
    printf("| %2d |", pov[i]);
  }

  printf("     \n");

  for (int i = 0; i < grid->size; ++i) {

    printf("| %2d |", pov[grid->size * 4 - i - 1]);

    for (int j = 0; j < grid->size; ++j) {
      printf("| %2d |", grid->tab[i][j]);
    }

    printf("| %2d |\n", pov[grid->size + i]);
  }

  printf("      ");

  for (int i = 0; i < grid->size; i++) {
    printf("| %2d |", pov[grid->size * 3 - i - 1]);
  }
  printf("     \n");
}