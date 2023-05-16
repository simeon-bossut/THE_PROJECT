#ifndef solver
#define solver

typedef struct GhostGrid{
	char*** tab;
	int size;
}GhostGrid;

void fill_ghost(GhostGrid gridf, Grid gridj, int* around);

Pos* find_in_grid(Grid grid, int val, int* size);

#endif // !solver
