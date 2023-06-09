#ifndef solver
#define solver
#define NAS 99 // Non available spaces
#define COLLUMN 1
#define ROW 2
#define FOUND 3
#define NOT_FOUND 4

#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// Init start
typedef struct StockSoluce {
	Grid* stock;
	int size;
} StockSoluce;

typedef struct GhostGrid {
  char ***tab;
  int size;
} GhostGrid;

typedef struct Guesses {
  char **tab;
  int id;
  int direction;
  int size;
} Guess;

GhostGrid *initGhostGrid(int dim);//fait les mallocs necessaire pour la creation d'une grille de possibilites 
// Init end



//Debug start
void printgrid_Ghost(GhostGrid* grid);//affiche une grille fantome
//End start


//SubFunction Start
int fill_ghost_box(Grid gridj, GhostGrid grid, int value, int i, int j);
Pos* find_in_grid(Grid grid, int val, int* size);//renvoie un tableau de de couple de coordonnees qui decrivent les positions d'une certaine valeur dans une grille
void put_number(int val, int ligne, int colonne, GhostGrid Gf);//ne laisse dans une case precise de la grille de possibilite qu'une possibilite(val)
void suite_col(int ligne, int colonne, GhostGrid Gf);//sous-fonctions utilise dans la partie simple du solveur 
void suite_row(int ligne, int colonne, GhostGrid Gf);//sous-fonctions utilise dans la partie simple du solveur 
int Length(char* string, int size);//calcule le nombre de possibilites dans une case 
int complete_ghost(GhostGrid gridf, Grid gridj);//complete la grille de possibilite en fonction des observateurs
int modif_box(int i, int j, GhostGrid gridf, Grid gridj);
void print_Stock(StockSoluce*Stock);//affiche toutes les solutions
//SubFunction End


//Solver start
int crate_solver(Grid* adgridj);//revoie la	 première solution (a appeler si on est sur de la validite de la grille)
void fill_ghost(GhostGrid gridf, Grid gridj);//rempli initailement la grille de possibilte(un seul appel)
int maj_ghost(GhostGrid gridf, Grid gridj);//rempli la grille de possibilites(grille fantome) en fonction de la grille de jeu(appel frequent)
int fill_loners(Grid* gridj, GhostGrid gridf);//place dans la grille de jeu les possibilite uniques presentes dans la grille de posssibilite
int hypothesis(GhostGrid* gridf, Grid* gridj, int poss,StockSoluce*Stock, bool first_sol,bool validity);//essaye de résoudre de facon facile la grille puis fait une hypothese dans une case ou il y a 2 possibilité et s'appelle elle-meme (recursif) 
int Rule2(GhostGrid gridf, Grid gridj);//une des regles qui permet de resoudre "facilement " une grille
int check_loners(GhostGrid* gridf, Grid* gridj);//si une possibilite est presente unqiement une fois dans sa ligne ou sa colonne ,on peut affirmer que cette possibilite est la bonne
bool unique_solution(Grid* grid);//verifie si la	 grille a bien une seule solution (utilisee dans le generateur de niveau automatique ou manuelle)
int subcrate_solver(Grid* gridj, bool first_sol, bool validity);// sous-fonction du solveur permettant l'initialisation de plusieurs variables
//Solver end

bool indice(Grid* grid, int nb_hints);//renvoie le tabmeau avec un indice en plus
Grid* copy_grid(Grid* grid);//copie une grille en creant une veritable copie (avec des mallocs)

//Free start
void free_tab_3(char*** tab, int size);//free un tableau a 3 dimensions
void free_grid(Grid* grid);//free une grille et tout son contenu
void free_ghostgrid(GhostGrid* gridf);//free une gtille de possibilité
//Free end
#endif // !solver