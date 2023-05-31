#pragma once

void put_number(int val, int ligne, int colonne, GhostGrid Gf)
{
	for (int k = 0;k < Gf.size;++k)
	{
		if (Gf.tab[ligne][colonne][k] != val)
		{
			Gf.tab[ligne][colonne][k] = NAS;
		}
	}
}

void suite_col(int ligne, int colonne, GhostGrid Gf)
{

	if (ligne == 0)//Nous indique le sens d'écriture de la colonne
	{
		for (int k = 0;k < Gf.size;++k)
		{
			put_number(k + 1, ligne + k, colonne, Gf);
		}
	}
	else if (ligne == Gf.size)
	{
		for (int k = 0;k < Gf.size;++k)
		{
			put_number(Gf.size - k, ligne - k, colonne, Gf);
		}
	}
}

void suite_row(int ligne, int colonne, GhostGrid Gf)
{
	if (colonne == 0)//Nous indique le sens d'écriture de la colonne
	{
		for (int k = 0;k < Gf.size;++k)
		{
			put_number(k + 1, ligne, colonne - k, Gf);
		}
	}
	else if (colonne == Gf.size)
	{
		for (int k = 0;k < Gf.size;++k)
		{
			put_number(Gf.size - k, ligne, colonne - k, Gf);
		}
	}
}

