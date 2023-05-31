#include"solver.h"

void put_number(int val, int ligne, int colonne, GhostGrid Gf) {
    for (int k = 0; k < Gf.size; ++k) {
        if (Gf.tab[ligne][colonne][k] != val) {
            Gf.tab[ligne][colonne][k] = NAS;
        }
    }
}

void suite_col(int ligne, int colonne, GhostGrid Gf) {

    if (ligne == 0) // Nous indique le sens d'écriture de la colonne
    {
        for (int k = 0; k < Gf.size; ++k) {
            put_number(k + 1, ligne + k, colonne, Gf);
        }
    }
    else if (ligne == Gf.size) {
        for (int k = 0; k < Gf.size; ++k) {
            put_number(Gf.size - k, ligne - k, colonne, Gf);
        }
    }
}

void suite_row(int ligne, int colonne, GhostGrid Gf) {
    if (colonne == 0) // Nous indique le sens d'écriture de la colonne
    {
        for (int k = 0; k < Gf.size; ++k) {
            put_number(k + 1, ligne, colonne - k, Gf);
        }
    }
    else if (colonne == Gf.size) {
        for (int k = 0; k < Gf.size; ++k) {
            put_number(Gf.size - k, ligne, colonne - k, Gf);
        }
    }
}

int Length(char* string, int size) {
    int number = 0;
    for (int i = 0; i < size; i++) {
        if (string[i] != NAS) {
            number++;
        }
    }
    return number;
}


int modif_box(int i, int j, GhostGrid gridf, Grid gridj) {
    int size = gridj.size;
    int modif = 0;
    int obv_1 = NAS;
    int obv_2 = NAS;
    if (i == 0) {
        obv_1 = j;
    }
    else if (i == size - 1) {
        obv_1 = 3 * size - 1 - j;
    }
    if (j == 0) {
        obv_2 = 4 * size - 1 - i;
    }
    else if (j == size - 1) {
        obv_2 = size + i;
    }
    if (gridj.obv[obv_1] == 1 ||
        gridj.obv[obv_2] == 1) // cas le plus simple, on met n (size)
    {
        put_number(size, i, j, gridf);
        modif = 1;
    }

    if (gridj.obv[obv_1] == 1)//Cas suite de 1 à n sur toute la colonne
    {
        suite_col(i, j, gridf);
        modif = 1;
    }
    if (gridj.obv[obv_2] == 1)//Cas suite de 1 à n sur toute la colonne
    {
        suite_row(i, j, gridf);
        modif = 1;
    }
    if ((obv_1 == NAS && obv_2 == NAS))//On s'arrête aussi si les observateurs sont inexistants
    {
        return modif;
    }
    if (gridj.obv[obv_1] == 0)
    {
        obv_1 = NAS;
    }
    if (gridj.obv[obv_2] == 0)
    {
        obv_2 = NAS;
    }
    for (int k = 0;k < gridf.size;++k)
    {
        if (obv_1 != NAS)
        {
            if (k + 1 > size + 1 - gridj.obv[obv_1])//condition pour suppression
            {
                if (gridf.tab[i][j][k] == k + 1)
                {
                    gridf.tab[i][j][k] = NAS;
                    //if ()
                        modif = 1;
                }
            }
        }
        if (obv_2 != NAS)
        {
            if (k + 1 > size + 1 - gridj.obv[obv_2])//condition pour suppression
            {
                if (gridf.tab[i][j][k] == k + 1)
                {
                    gridf.tab[i][j][k] = NAS;
                    modif = 1;
                }
            }
        }
    }
    return modif;
}

int complete_ghost(GhostGrid gridf, Grid gridj) {
    int modif = 0;
    int size = gridj.size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            modif = modif_box(i, j, gridf, gridj);
        }
    }
    return modif;
}










int check_row(int val, GhostGrid* gridf, int row, int* pos) {
    char*** tab = gridf->tab;
    int compt = 0;
    for (int i = 0; i < gridf->size; ++i) {
        if ((tab[row][i][val - 1] == val) &&
            (Length(tab[row][i], gridf->size) != 1)) {
            compt++;
            *pos = i;
        }
    }
    return compt;
}

int check_col(int val, GhostGrid* gridf, int col, int* pos) {
    char*** tab = gridf->tab;
    int compt = 0;
    for (int i = 0; i < gridf->size; ++i) {
        if ((tab[i][col][val - 1] == val) &&
            (Length(tab[i][col], gridf->size) != 1)) {
            compt++;
            *pos = i;
            if (compt > 1) {
                return compt;
            }
        }
    }
    return compt;
}


int check_loners(GhostGrid* gridf, Grid* gridj) {
    maj_ghost(*gridf, *gridj);
    int modif = 0;
    int size = gridf->size;
    int pos = NAS;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            if (check_row(j + 1, gridf, i, &pos) == 1) {
                modif = 1;
                put_number(j + 1, i, pos, *gridf);
            }
            if (check_col(j + 1, gridf, i, &pos) == 1) {
                modif = 1;
                put_number(j + 1, pos, i, *gridf);
            }
        }
    }
    if (modif) // Si il y a eu modification on recommence tout,pour ne rien rater
    {
        check_loners(gridf, gridj);
    }
    return modif;
}