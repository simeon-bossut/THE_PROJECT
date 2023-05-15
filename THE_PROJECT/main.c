#include "game.h"

int main() {
	Grid *grid= initgrid(3);
	if (grid == NULL)
	{
		return 0;
	}
	printgrid(grid);
	return;
}