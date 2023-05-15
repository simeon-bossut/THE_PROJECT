#include "game.h"
#include "solver.h"

int main() {
	Grid *grid= initgrid(4);
	if (grid == NULL)
	{
		return 0;
	}
	printgrid(grid);
	return;
}