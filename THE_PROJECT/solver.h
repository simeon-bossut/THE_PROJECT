#ifndef solver
#define solver

typedef struct GhostGrid{
	char*** tab;
	int size;
}GhostGrid;

void fill_ghost(GhostGrid gridf, Grid gridj, int* around);

Pos* find_in_grid(Grid grid, int val, int* size);

char* fill_ghost_box(GhostGrid grid, int value, int i, int j);
#endif // !solver
