#ifndef solver
#define solver

typedef struct GhostGrid{
	char*** tab;
	int size;
}GhostGrid;

void fill_ghosts(GhostGrid gridf,Grid gridj);

#endif // !solver
