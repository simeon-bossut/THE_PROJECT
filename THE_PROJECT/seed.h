#ifndef seed
#define seed

#include "game.h"

char *id_to_line(int val, int dim);  //lit un Id et renvoie sa ligne correspondante

int line_to_id(int *line, int dim);//recoit une ligne et donne L'Id corresdpondant

int factorial(int n);//factorielle

char *create_seed(int difficulty, int dim);//Cree un niveau et renvoie sa seed

Grid *read_seed(char *Seed);//lit une seed et renvoie le tableau correspondant

int generateGrid(Grid *grid);//genere une grille remplie(tableau+observateurs)

int genGrid_tab(int **tab, char *leftCases, int size);//genere une grille avec un tableau rempli suivant la regle du carre latin

void intoa(int value, char *buffer, int size);//transforme un entier en une chaine de caractere 

void calcul_obs(Grid* grid);//calcule les observateurs d'une grille avec un tableau rempli

bool* generate_level_cache(Grid*grid, int difficulty,int sub_difficulty);//genere un cache qui rend le niveau faisable

void push_to_php(Grid* grid);//affiche une grille sous une certaine forme dans le but d'etre recupere par le php/JS

char* level_to_seed(Grid* grid);//transforme un niveau en seed

char* sub_level_to_seed(Grid* grid, bool* cache);//sous-fonction de "level_to_seed", qui va modifier le cache




#endif // !seed