#include "seed.h"
#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int factorial(int n) {
  if (n == 0)
    return 1;
  else
    return n * factorial(n - 1);
}
int line_to_id(char *line, int dim) {
  // Il faut idéalement mettre un char ne contenant que des chiffres
  // différent(ligne d'un carré latin)
  int val = 0; // Ce char va être transformé à la fin en char grace to itoa
  int factor = factorial(dim - 1);
  val += ((line[0] - 48) - 1) * factor +
         1; // Le 6 vient du fait de 3! possibilités une fois le char[0] fixé
  if (dim == 3) {
    if (line[1] > line[2]) {
      val += 1;
    }
  } else if (dim == 4) {
    if (line[1] > line[2]) // C des trucs que j'ai trouvé, demandez si vous
                           // voulez comprendre
    {
      val += 2;
    }
    if (line[2] > line[3]) {
      val += 1;
    }
    if (line[1] > line[3]) // trust the process
    {
      val += 2;
    }
  } else if (dim == 5) {
    char tab[6] = {0};
    int compt = 0;
    for (int i = 0; i < dim; ++i) {
      if ((i + 1) + 48 != line[0]) {
        tab[compt] = (i + 1) + 48;
        compt++;
      }
    }
    for (int i = 0; i < dim - 1; ++i) {
      if (tab[i] == line[1]) {
        val += i * 6;
      }
    }
    if (line[3] > line[4]) {
      val += 1;
    }
    if (line[2] > line[3]) {
      val += 2;
    }
    if (line[2] > line[4]) {
      val += 2;
    }
  }
  // C fini ! Plutôt simple dans ce sens...
  char Id[4] = {0}; // 3 chiffres max + \0
  return val;
}
char *id_to_line(int val, int dim) // Uniquement en 4*4 pour l'instant
{                                  // Parti pour la galère
  val = val % (factorial(dim));
  if (val == 0) {
    val = factorial(dim);
  }
  char *line = malloc(
      sizeof(char) * (dim + 1)); // pour l'intant 4 (+\0)car taille de la ligne,
                                 // par le futur malloc car taille variable
  if (line == NULL) {
    return NULL;
  }
  for (int i = 0; i < dim + 1; ++i) {
    line[i] = 0;
  }
  line[0] = ((val - 1) / factorial(dim - 1) + 1) +
            48; // N'hésitez pas à poser des questions
  char *tab = malloc(
      sizeof(char) *
      (dim)); // tableau contenant tous les chiffres sauf celui dans line[0]
  if (tab == NULL) {
    return NULL;
  }
  tab[dim - 1] = 0;
  int compt = 0;
  for (int i = 0; i < dim; ++i) {
    if ((i + 1) + 48 != line[0]) {
      tab[compt] = (i + 1) + 48;
      compt++;
    }
  }
  if (dim == 3) {
    for (int i = 0; i < dim - 1; ++i) {
      if (line[2 - val % 2] == 0) // Si cette case déja remplie déja remplie
      {
        line[2 - val % 2] = tab[i];
      } else if (line[1 + val % 2] == 0) {
        line[1 + val % 2] = tab[i];
      }
    }
    return line;
  }
  if (dim == 4) {
    line[1] =
        tab[((val - 1) % 6 / 2)]; // Chiant à expliquer en commentaires(étude de
                                  // la ligne de longueur 6)
  }
  if (dim == 5) {
    line[1] = tab[((val - 1) % 24 / 6)];
    for (int i = ((val - 1) % 24 / 6); i < dim - 1;
         i++) // suppresion de line[1] dans tab et décalage adapté
    {
      tab[i] = tab[i + 1];
    }
    tab[dim - 2] = '\0';
  }
  if (dim == 4) {
    for (int i = 0; i < dim - 1; ++i) {
      if (tab[i] != line[1]) // Si le chiffre est encore dispo
      {
        if (line[3 - val % 2] == 0) // Si cette case déja remplie déja remplie
        {
          line[3 - val % 2] = tab[i];
        } else if (line[2 + val % 2] == 0) {
          line[2 + val % 2] = tab[i];
        }
      }
    }
  }
  if (dim == 5) {
    line[2] = tab[(val - 1) % 6 / 2];
    for (int i = 0; i < dim - 1; ++i) {
      if (tab[i] != line[2]) // Si le chiffre est encore dispo
      {
        if (line[4 - val % 2] == 0) // Si cette case déja remplie déja remplie
        {
          line[4 - val % 2] = tab[i];
        } else if (line[3 + val % 2] == 0) {
          line[3 + val % 2] = tab[i];
        }
      }
    }
  }
  return line;
}

// char *create_seed(int difficulty, int dim) {
//   int size;
//   if (dim == 3) {
//     size = 12;
//   } else if (dim == 4) {
//     size = 20;
//   } else if (dim == 5) {
//     size = 32;
//   } else {
//     return NULL;
//   }
//   char *SEED = malloc(sizeof(char) * size);
//   if (SEED == NULL) {
//     return NULL;
//   }
//   SEED[0] = dim + 48;
//   int *tab; // tableau contenant toutes les lignes déja présentes dans le
//   // tableau
//   for (int i = 0; i < dim; i++) // Création du tableau
//   {
//     ;
//   }

//   int size_cache = dim * (dim + 4);
//   bool *cache = malloc(sizeof(bool) * size_cache);
//   if (cache == NULL) {
//     return NULL;
//   }
//   if (difficulty == 1) {
//     for (int i = 0; i < size_cache; ++i) {
//       cache[i] = i / (dim * dim); // Tableau facile , tous les observateurs
//       sont
//                                   // visibles et tout le jeu caché
//     }
//   } else {
//     do {

//     } while (solver()); // Tant que le solveur marche
//   }
//   int value = 0b0;
//   for (int i = 0; i < dim * dim; ++i) {
//     value += cache[i];
//     value = value << 1;
//   }
//   _itoa_s(
//       value, SEED + 1, dim * dim,
//       10); // Dans le futur à décaler de quelques cases car le tableau
//       précède

//   return; // cache_tab;
// }

void getLeftCases(char *tab, int i, int j, Grid *grid, int size) {
  int compt = 0;
  for (int i = 0; i < size; ++i) {
    if (!found_in_col(i + 1, grid, j) && !found_in_row(i + 1, grid, i)) {
      tab[compt] = (i + 1) + 48;
      compt++;
    }
  }
  tab[compt] = '\0';
}

void generateGrid(Grid *grid, char *leftCases) {

  int compt = 0;
  int size = grid->size;
  int random;
  /*for (int i = 0; i < size; i++)
  {
      leftCases[i] = i + 1;
  }*/

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {

      getLeftCases(leftCases, i, j, grid, size);

      if (strlen(leftCases) == 0) {
        compt++;
        if (compt > 3000) {
          compt = 0;
          return; // error
        }

        generateGrid(grid, leftCases);
      }
      random = rand() % strlen(leftCases);
      grid->tab[i][j] = leftCases[random] - 48;
      printf("%d |", grid->tab[i][j]);
    }
  }
  compt = 0;

  return;
}

int *Dec2Bin(int n, int dim) {
  int *binaryNum = malloc(sizeof(int) * dim * dim);
  int i = 0;
  while (n > 0) {
    binaryNum[i] = n % 2;
    n = n / 2;
    i++;
  }
  return binaryNum;
}

int *get_cache_tab(int dim, char *Seed, int len) {
  int size_cache;
  int *cache_tab = malloc(sizeof(int) * dim * dim);
  if (cache_tab == NULL) {
    return NULL;
  }
  char *tmp_cache_tab = malloc(sizeof(char) * dim);
  switch (dim) {
  case 3:
    size_cache = 3;
    break;
  case 4:
    size_cache = 5;
    break;
  case 5:
    size_cache = 8;
    break;
  }
  memcpy(tmp_cache_tab, Seed + (dim * (dim - 2)) + 1, size_cache);
  printf("%s\n", tmp_cache_tab);

  int int_cache_tab = atoi(tmp_cache_tab);
  cache_tab = Dec2Bin(int_cache_tab, dim);
  return cache_tab;
}

int *get_cache_obv(int dim, char *Seed, int len) {
  int size_cache, size_obv;
  int *cache_tab = malloc(sizeof(int) * dim * dim * 4);
  if (cache_tab == NULL) {
    return NULL;
  }

  switch (dim) {
  case 3:
    size_cache = 3;
    size_obv = 4;
    break;
  case 4:
    size_cache = 5;
    size_obv = 5;
    break;
  case 5:
    size_cache = 8;
    size_obv = 7;
    break;
  }
  char *tmp_cache_tab = malloc(sizeof(char) * dim * dim * 4);
  memcpy(tmp_cache_tab, Seed + (dim * (dim - 2)) + size_cache + 1, size_obv);
  printf("%s\n", tmp_cache_tab);

  int int_cache_tab = atoi(tmp_cache_tab);
  cache_tab = Dec2Bin(int_cache_tab, dim * 4);
  return cache_tab;
}

Grid *read_seed_v2(Grid *grid, int dim, char *Seed, int len) {
  int *cache_tab, *cache_obv, id;
  char *buffer, *line;

  buffer = (char *)malloc(sizeof(char) * (dim - 2));

  for (int i = 0; i < dim; i++) {
    strncpy(buffer, Seed + i * (dim - 2) + 1, dim - 2);
    id = atoi(buffer);
    line = id_to_line(id, dim);
    for (int j = 0; j < dim; j++) {
      grid->tab[i][j] = line[j] - 48;
    }
  }

  cache_tab = get_cache_tab(dim, Seed, len);

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (cache_tab[i + j] == 0)
        grid->tab[i][j] = 0;
    }
  }

  cache_obv = get_cache_obv(dim, Seed, len);
  for (int i = 0; i < dim * 4; i++) {
    if (cache_obv[i] == 0)
      grid->obv[i] = 0;
  }

  return grid;
}

Grid *read_seed(char *Seed) {
  int lenSeed = strlen(Seed);
  int dim = Seed[0] - 48;
  Grid *grid = initgrid(dim);

  grid = read_seed_v2(grid, dim, Seed, lenSeed);
  return grid;
}