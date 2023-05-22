#ifndef seed
#define seed

#include "game.h"

char *id_to_line(int val, int dim);

int line_to_id(char *line, int dim);

int factorial(int n);

char *create_seed(int difficulty, int dim);

Grid *read_seed(char *Seed);

void generateGrid(Grid* grid, char* leftCases);


#endif // !seed