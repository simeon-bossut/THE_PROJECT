#ifndef game
#define game

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Pos {

  int row;
  int col;
} Pos;

typedef struct Grid {
  int size;
  int **tab;
  int *obv;
} Grid;

int **creatab(int size);//cree un tableau a deux dimensions(et tous les mallocsq qui vont avec).Initialise egalement le tableau 

void printgrid(Grid *grid);//affiche une grille (tableau + observateurs)

int *initpov(int size);//permet d'initialiser les observateurs à 0)

Grid *initgrid(int dim);//cree une grille de dimension variable en appellant "creatab" et "initpov". Tous les mallocs sont donc faits et la grille initialisée

void initElt(int *elt, int size);//permet d'initaialiser une case de grille fantome (qui est en realite un tableau de int)

bool found_in_row(int **tab, int size, int row, int val);//informe si une valeur a été trouvée dans une ligne

bool found_in_col(int** tab, int size, int col, int val);//informe si une valeur a été trouvée dans une collonne

void initab(int **tab, int size);//initialise un tableau

void free_tab(int **tab, int size);//free un tableau à deux dimensions

bool is_solved(Grid gridj);//explicite

bool is_grid_correct(Grid* grid);//verifie la coherence de la grille

Grid* read_grid(char* grid_string, int size);//lit une grille envoyee par le php et la trnasforme en, vrai grille
#endif // !game