#include "solver.h"

void fill_ghost(GhostGrid gridf, Grid gridj, int *around) {
  int tmp;

  Pos *pos = (Pos *)malloc(gridj.size * sizeof(Pos)); // Pos storage
  if (gridj.tab[0][0] !=
      0) { // Filling ghost grid with all possibilities if it's empty
    for (int i = 0; i < gridj.size; i++) {
      for (int j = 0; j < gridj.size; i++) {
        gridf.tab[i][j] = "1234";
      }
    }
  }
  int size;
  for (int i = 0; i < gridf.size; i++) {
    pos = find_in_grid(gridj, i, &size);

    for (int j = 0; j < gridf.size; j++) {
      for (int k = 0; k < gridf.size; k++) {
        fill_ghost_box(gridf, i, pos[j].row, k);
        fill_ghost_box(gridf, i, k, pos[j].col);
      }
    }
  }
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
        positions[compt].row = i;
        positions[compt].col = j;
      }
    }
  }
  *size = compt;
  return positions;
}

char *fill_ghost_box(GhostGrid grid, int value, int i, int j) {
  int tmp = 0;
  for (int k = 0; k < grid.size; k++) {
    if (k != value) {
      grid.tab[i][j][tmp] = k;
    } else {
      k++;
      grid.tab[i][j][tmp] = k;
    }
    tmp++;
  }
  grid.tab[i][j][tmp] = '\0';
}