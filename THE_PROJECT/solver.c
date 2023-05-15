#include "game.h"
#include "solver.h"
#include <stdio.h>
#include <stdlib.h>

void fill_ghost(GhostGrid gridf, Grid gridj,int * around) {
	if (gridj.tab[0][0] != NULL) {
		for (int i = 0;i<gridj.size; i++) {
			for (int j = 0; j < gridj.size; i++) {
				gridf.tab[i][j] = "1234";
			}
		}
	}
	else if (){
		
	}
}