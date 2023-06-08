#ifndef seed
#define seed

#include "game.h"

char *id_to_line(int val, int dim);

int line_to_id(int *line, int dim);

int factorial(int n);

char *create_seed(int difficulty, int dim);

Grid *read_seed(char *Seed);

int generateGrid(Grid *grid);

int genGrid_tab(int **tab, char *leftCases, int size);

void intoa(int value, char *buffer, int size);

void calcul_obs(Grid* grid);

bool* generate_level_cache(Grid*grid, int difficulty,int sub_difficulty);

void push_to_php(Grid* grid);

char* level_to_seed(Grid* grid);

char* sub_level_to_seed(Grid* grid, bool* cache);




#endif // !seed