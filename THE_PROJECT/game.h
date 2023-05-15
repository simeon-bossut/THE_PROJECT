#ifndef game
#define game

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Case {
	int value;
}Case;

typedef struct Grid {
	int size;
	Case** tab;
}Grid;

void printgrid(Grid grid);

Grid* initgrid(int dim);

Case initCase(int value);

#endif // !game