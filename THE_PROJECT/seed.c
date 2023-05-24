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

int col_analyze(int**tab,int size,int col,bool way)//way = 0 if up to down 
{
    int max = 0;
    int value = 0;
    for (int i = 0;i < size;++i)
    {
        if ((!way)&&(tab[i][col] > max))
        {
            max = tab[i][col];
            value++;
        }
        else if((way)&&(tab[size-1-i][col] > max))
        {
            max = tab[size-1-i][col];
            value++;
        }
    }
    return value;
}

int row_analyze(int** tab,int size, int row, bool way)//way=0 if left to right
{
    int max = 0;
    int value = 0;
    for (int i = 0;i < size;++i)
    {
        if ((!way) && (tab[row][i] > max))
        {
            max = tab[row][i];
            value++;
        }
        else if ((way) && (tab[row][size-1-i] > max))
        {
            max = tab[row][size-1-i];
            value++;
        }
    }
    return value;
}






void calcul_obs(Grid* grid)//remplit le tableau d'observateur
{
    int dim = grid->size;
    for (int a = 0;a < 2*dim;++a)
    {
        if (a < dim)//travail colonnes
        {
            grid->obv[a] = col_analyze(grid->tab, dim, a, 0);
            grid->obv[3*dim-1-a] = col_analyze(grid->tab, dim,a, 1);
        }
        else//travail lignes
        {
            grid->obv[a] = row_analyze(grid->tab, dim, a-dim, 1);
            grid->obv[5 * dim - 1 - a] = row_analyze(grid->tab, dim, a-dim, 0);
        }
    }
}

int line_to_id(int *line, int dim) {
  // Il faut idéalement mettre un char ne contenant que des chiffres
  // différent(ligne d'un carré latin)
  int val = 0; // Ce char va être transformé à la fin en char grace to itoa
  int factor = factorial(dim - 1);
  val += ((line[0]) - 1) * factor +
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
    int tab[5] = {0};
    int compt = 0;
    for (int i = 0; i < dim; ++i) {
      if ((i + 1) != line[0]) {
        tab[compt] = (i + 1);
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
char* tab = malloc(
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
        }
        else if (line[1 + val % 2] == 0) {
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
            }
            else if (line[2 + val % 2] == 0) {
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
            }
            else if (line[3 + val % 2] == 0) {
                line[3 + val % 2] = tab[i];
            }
        }
    }
}
return line;
}


void intoa(int value, char* buffer, int size)
{
    for (int i = size - 1;i >= 0;--i)
    {
        buffer[i] = value % 10 + 48;
        value /= 10;
    }
    buffer[size] = '\0';
}

int booltab_to_int(bool* tab, int dim)
{
    int value = 0b0;
    for (int i = 0; i < dim * dim; ++i) {
        value += tab[i];
        value = value << 1;
    }
    return value;
}

Grid* crea_cach(Grid*grid,bool*cache) 
{
    int size = grid->size;
    Grid* tmp=initgrid(size);
    int random = 0;
    if (tmp == NULL) { return 0;}

    do
    {
        random = rand() % (size * (4 + size));
        cache[random] = 1;//On ajoute un 1 au cache(il se peut qu'il y ait déjà un 1 à cet emplacement mais cela ne pose pas vraiment de problème

        if (random < size * size)//travail sur le cache de la grille(int**)
        {
            tmp->tab[random / size][random % size] = grid->tab[random / size][random % size];
        }
        else if (random < size * (size + 4))//travail sur les observateurs(int *)
        {
            tmp->obv[random - (size * size)] = grid->obv[random - (size * size)];
        }
    } while (1);//tant que solveur ne marche pas : (!solveur(tmp))

    //Si le solveur marche, on a fini !
    
    return tmp;
}

Grid* generate_level(int dim,int difficulty)
{
    Grid* grid = initgrid(dim);
    Grid* tmp = initgrid(dim);
    if (grid == NULL||tmp==NULL) { return NULL; }
   
    if (generateGrid(grid) == -1)//remplissage aléatoire de grid->tab et de grid->obv
    {
        return NULL;
    }
    int size_cache = dim * (dim + 4);
    bool* cache = malloc(sizeof(bool) * size_cache);
    if (cache == NULL) {
        return NULL;
    }
    if (difficulty == 1) {
        for (int i = 0; i < size_cache; ++i) {
            cache[i] = i / (dim * dim);// Tableau facile , tous les observateurs sont visibles et tout le jeu caché
            if (i < dim * dim)
            {
                tmp->tab[i / (dim)][i % (dim)]=grid->tab[i / (dim)][i % (dim )]*cache[i];
            }
            else if (i < size_cache)
            {
                tmp->obv[i-dim * dim]= grid->obv[i-dim*dim]*cache[i];
            }
        }



    }
    //else {
    //    int random = 0;
    //    for (int i = 0; i < size_cache; ++i) {
    //        cache[i] = 0;// intit du tableau à 0
    //    }
    //    tmp=crea_cach(grid, cache);
    //    if (difficulty == 2)//Pour la difficulté 2, on ajoute une info en plus(pour l'instant), par la suite peut-être dim-2 info en plus
    //    {
    //        do
    //        {
    //            random = rand() % size_cache;
    //        } while (cache[random]);//tant que la case contient un 1, on reessaye
    //        cache[random] = 1;
    //    }
    //}
    free(cache);
    free(grid->obv);
    free_tab(grid->tab, grid->size);
    free(grid);


    return tmp;
}

char *create_seed(int difficulty, int dim) {
  int size;
  if (dim == 3) {
    size = 12;
  } else if (dim == 4) {
    size = 20;
  } else if (dim == 5) {
    size = 32;
  } else {
    return NULL;
  }
  char *SEED = malloc(sizeof(char) * size);

  int* line = malloc(sizeof(int) * dim);//utile pour la transcription de la grid en seed
  if (SEED == NULL||line==NULL) {
    return NULL;
  }
  SEED[0] = dim + 48;//premier char désigne la dimension
  Grid* grid = generate_level(dim,difficulty);//génère un niveau complet
  
  for (int i = 0;i < dim;++i)
  {
      for (int j = 0;j < dim;++j)
      {
          line[j] = grid->tab[i][j];
      }
  }

  
 
	
    return SEED;
}

void getLeftCases(char *string, int i, int j, int **tab, int size) {
  int compt = 0;
  for (int a = 0; a < size; ++a) {

    if (!found_in_col(tab, size, j, a + 1) &&
        !found_in_row(tab, size, i, a + 1)) {
      string[compt] = (a + 1) + 48;
      compt++;
    }
  }
  string[compt] = '\0';
}

int generateGrid(Grid *grid) {
  int size = grid->size;
  char *leftCases = malloc(sizeof(char) * (size + 1));
  int **tab = creatab(grid->size);
  if (leftCases == NULL || tab == NULL ||(genGrid_tab(tab, leftCases, size) == -1)) {
    return -1;
  }
  free(leftCases);
  free_tab(grid->tab, size); // On libère de la place
  grid->tab = tab;

  calcul_obs(grid);
}

int genGrid_tab( int **tab, char *leftCases, int size) // Génère un tableau de dimension "size".Cette fonction est un sous-fonction appellée par "generateGrid"
{
  int compt = 0;

  int random;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {

      getLeftCases(leftCases, i, j, tab, size);

      if (strlen(leftCases) == 0) {
        compt++;
        if (compt > 300) {
          compt = 0;
          return -1; // error
        }
        // Si il y a eu un échec, on vide le tableau et on réessaye
        initab(tab, size);
        return genGrid_tab(tab, leftCases, size);
      }
      random = rand() % strlen(leftCases);
      tab[i][j] = leftCases[random] - 48;
    }
  }

  return 0;
}

int *Dec2Bin(int n, int dim) {
  int size = dim * dim;
  if (4 > dim) {
    size = dim * 4;
  }
  int *binaryNum = malloc(sizeof(int) * size);
  if (!binaryNum)
    return NULL;

  /*if (n > (pow(2,size) - 1))
  {
      return NULL;
  }*/

  int i = 0;
  while (n > 0) {
    binaryNum[i] = n % 2;
    n = n >> 1;
    i++;
  }
  return binaryNum;
}

int *get_cache_tab(int dim, char *Seed, int len) {
  int size_cache;
  int *cache_tab = malloc(sizeof(int) * dim * dim);
 
  char *tmp_cache_tab = malloc(sizeof(char) * dim);
  if (cache_tab == NULL||tmp_cache_tab==NULL) {
      return NULL;
  }
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

void read_seed_v2(Grid *grid, int dim, char *Seed, int len) {
  
  int *cache_tab, *cache_obv, id;
  char *buffer, *line;

  buffer = (char *)malloc(sizeof(char) * (dim - 1));
  if (buffer == NULL) {
    return;
  }

  for (int i = 0; i < dim; i++) {
    //strncpy(buffer, Seed + i * (dim - 2) + 1, dim - 2);
    buffer[dim - 2] = '\0';
    id = atoi(buffer);
    printf("%d\n", id);
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
}

Grid *read_seed(char *Seed) {
  int lenSeed = strlen(Seed);
  int dim = Seed[0] - 48;
  Grid *grid = initgrid(dim);

  read_seed_v2(grid, dim, Seed, lenSeed);
  return grid;
}

void push_to_php(Grid* grid)
{
    int size = grid->size;
    printf("%d\n", size);
    for (int i = 0;i < size*size;++i)
    {
        printf("%d",grid->tab[i/size][i%size]);
        if (i != size * size - 1)
        {
            printf(",");
        }
        else
        {
            printf("\n");
        }
    }
    for (int i = 0;i < size*4;++i)
    {
        printf("%d",grid->obv[i]);
        if (i != size *4-1 )
        {
            printf(",");
        }
        else
        {
            printf("\n");
        }
    }
}