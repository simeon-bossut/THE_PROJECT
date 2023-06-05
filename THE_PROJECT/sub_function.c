#include "solver.h"

void put_number(int val, int ligne, int colonne, GhostGrid Gf) {
  for (int k = 0; k < Gf.size; ++k) {
    if (Gf.tab[ligne][colonne][k] != val) {
      Gf.tab[ligne][colonne][k] = NAS;
    }
  }
}

void suite_col(int ligne, int colonne, GhostGrid Gf) {

  if (ligne == 0) // Nous indique le sens d'�criture de la colonne
  {
    for (int k = 0; k < Gf.size; ++k) {
      put_number(k + 1, ligne + k, colonne, Gf);
    }
  } else if (ligne == Gf.size - 1) {
    for (int k = 0; k < Gf.size; ++k) {
      put_number(k + 1, ligne - k, colonne, Gf);
    }
  }
}

void suite_row(int ligne, int colonne, GhostGrid Gf) {
  if (colonne == 0) // Nous indique le sens d'�criture de la ligne
  {
    for (int k = 0; k < Gf.size; ++k) {
      put_number(k + 1, ligne, colonne + k, Gf);
    }
  } else if (colonne == Gf.size - 1) {
    for (int k = 0; k < Gf.size; ++k) {
      put_number(k + 1, ligne, colonne - k, Gf);
    }
  }
}

int Length(char *string, int size) {
  int number = 0;
  for (int i = 0; i < size; i++) {
    if (string[i] != NAS) {
      number++;
    }
  }
  return number;
}

void reduce_col(int row, int col, int valmin, GhostGrid grid) {
  int val = valmin;
  if (row == 0) // Nous indique le sens d'�criture de la colonne
  {
    for (int k = 0; k <= grid.size - val; ++k) { // d�placement dans la colonne
      for (int l = valmin; l <= grid.size; ++l) // valeur � enlever dans la case
      {
        grid.tab[k][col][l - 1] = NAS;
      }
      valmin++;
    }
  } else if (row == grid.size - 1) {
    for (int k = 0; k <= grid.size - val; ++k) {
      for (int l = valmin; l <= grid.size; ++l) // valeur � enlever dans la case
      {
        grid.tab[grid.size - 1 - k][col][l - 1] = NAS;
      }
      valmin++;
    }
  }
}

void reduce_row(int row, int col, int valmin, GhostGrid grid) {
  int val = valmin;
  if (col == 0) // Nous indique le sens d'�criture de la ligne
  {
    for (int k = 0; k <= grid.size - val; ++k) {
      for (int l = valmin; l <= grid.size; ++l) // valeur � enlever dans la case
      {
        grid.tab[row][k][l - 1] = NAS;
      }
      valmin++;
    }
  } else if (col == grid.size - 1) {
    for (int k = 0; k <= grid.size - val; ++k) {
      for (int l = valmin; l <= grid.size; ++l) // valeur � enlever dans la case
      {
        grid.tab[row][grid.size - 1 - k][l - 1] = NAS;
      }
      valmin++;
    }
  }
}

int modif_box(int i, int j, GhostGrid gridf, Grid gridj) {
  int size = gridj.size;
  int modif = NOT_FOUND;
  int obv_1 = NAS;
  int obv_2 = NAS;
  int val1 = 0;
  int val2 = 0;

  if (i == 0) {
    obv_1 = j;
    val1 = gridj.obv[obv_1];
  } else if (i == size - 1) {
    obv_1 = 3 * size - 1 - j;
    val1 = gridj.obv[obv_1];
  }
  if (j == 0) {
    obv_2 = 4 * size - 1 - i;
    val2 = gridj.obv[obv_2];
  } else if (j == size - 1) {
    obv_2 = size + i;
    val2 = gridj.obv[obv_2];
  }

  if ((obv_1 == NAS && obv_2 == NAS) || (val1 == 0 && obv_2 == NAS) ||
      (obv_1 == NAS && val2 == 0) ||
      (val1 == 0 && val2 == 0)) // On s'arr�te aussi si les observateurs sont
                                // inexistants ou vides
  {
    return modif;
  }

  if (gridj.obv[obv_1] == 0) {
    obv_1 = NAS;
  }
  if (gridj.obv[obv_2] == 0) {
    obv_2 = NAS;
  }

  if (val1 == gridf.size) // Cas suite de 1 � n sur toute la colonne
  {
    suite_col(i, j, gridf);
    modif = FOUND;
  } else if (val2 == gridj.size) // Cas suite de 1 � n sur toute la colonne
  {
    suite_row(i, j, gridf);
    modif = FOUND;
  } else if (val1 == 1 || val2 == 1) // cas le plus simple, on met n (size)
  {
    put_number(size, i, j, gridf);
    modif = FOUND;
  }

  if (obv_1 != NAS) {

    int least = size - gridj.obv[obv_1] +
                2; // valeur la plus petite a bannir dans la case [i][j]

    if (least <= gridf.size) {
      reduce_col(i, j, least, gridf);
    }
  }
  if (obv_2 != NAS) {
    int least = size - gridj.obv[obv_2] +
                2; // valeur la plus petite a bannir dans la case [i][j]
    if (least <= gridf.size) {
      reduce_row(i, j, least, gridf);
    }
  }

  return modif;
}

int complete_ghost(GhostGrid gridf, Grid gridj) {
  int modif = NOT_FOUND;
  int size = gridj.size;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {

      modif = modif_box(i, j, gridf, gridj);
    }
  }
  return modif;
}

int check_row(int val, GhostGrid *gridf, Grid *gridj, int row, int *pos) {
  char ***tabf = gridf->tab;
  int **tabj = gridj->tab;
  int compt = 0;
  for (int i = 0; i < gridf->size; ++i) {
    if (tabf[row][i][val - 1] == val) {
      compt++;
      *pos = i;
      if (Length(tabf[row][i], gridj->size) ==
          1) // si la case a d�j� �t� isol�e, pas besoin de le refaire
      {
        return 0;
      } else if (compt > 1) {
        return compt;
      }
    }
  }
  return compt;
}

int check_col(int val, GhostGrid *gridf, Grid *gridj, int col, int *pos) {
  char ***tabf = gridf->tab;
  int **tabj = gridj->tab;
  int compt = 0;
  for (int i = 0; i < gridf->size; ++i) {
    if (tabf[i][col][val - 1] == val) {
      compt++;
      *pos = i;
      if (Length(tabf[i][col], gridj->size) ==
          1) // si la case a d�j� �t� isol�e, pas besoin de le refaire
      {
        return 0;
      } else if (compt > 1) {
        return compt;
      }
    }
  }
  return compt;
}

int check_loners(GhostGrid *gridf, Grid *gridj) {

  maj_ghost(*gridf, *gridj);
  int modif = 0;
  int size = gridf->size;
  int pos = NAS;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; ++j) {
      if (check_row(j + 1, gridf, gridj, i, &pos) == 1) {
        modif = 1;
        put_number(j + 1, i, pos, *gridf);
      }
      if (check_col(j + 1, gridf, gridj, i, &pos) == 1) {
        modif = 1;
        put_number(j + 1, pos, i, *gridf);
      }
    }
  }
  return modif;
}

int **pov_separation(Grid grid) {
  int size = grid.size;
  int *pov = grid.obv;
  int *north = (int *)malloc(sizeof(int) * size);
  int *east = (int *)malloc(sizeof(int) * size);
  int *south = (int *)malloc(sizeof(int) * size);
  int *west = (int *)malloc(sizeof(int) * size);
  int **tab = (int **)malloc(sizeof(int *) * 4);
  if (north == NULL || east == NULL || south == NULL || west == NULL ||
      tab == NULL) {
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
  tab[0] = north;
  tab[1] = east;
  tab[2] = south;
  tab[3] = west;
  return tab;
}

int resolve_obv_1(Grid grid, GhostGrid gridf) {
  int **directions = pov_separation(grid);
  int *north = directions[0];
  int *east = directions[1];
  int *south = directions[2];
  int *west = directions[3];
  free(directions);
  int res = NOT_FOUND;
  int size = grid.size;
  for (int i = 0; i < size; i++) {
    if (north[i] == size) {
      fill_ghost_box(grid, gridf, size, i, 0);
      res = FOUND;
    }
    if (east[i] == size) {
      fill_ghost_box(grid, gridf, size, size - 1, i);
      res = FOUND;
    }
    if (south[i] == size) {
      fill_ghost_box(grid, gridf, size, i, size - 1);
      res = FOUND;
    }
    if (west[i] == size) {
      fill_ghost_box(grid, gridf, size, 0, i);
      res = FOUND;
    }
  }
  return res;
}