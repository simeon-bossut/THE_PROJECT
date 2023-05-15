#include "game.h"
#include "solver.h"

int main(int argc, char **argv) {
  int size = argv[1] ? atoi(argv[1]) : 3;

  Grid *grid = initgrid(size);
  if (grid == NULL) {
    return 0;
  }
  printgrid(grid);
  return 1;
}