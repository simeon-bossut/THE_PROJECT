#ifndef game
#define game

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Box {
	int value;
}Box;

typedef struct Grid {
	int size;
	int** tab;
}Grid;

void printgrid(Grid *grid);

Grid* initgrid(int dim);

Box initBox(int value);

#endif // !game